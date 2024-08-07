#include "mainwin.h"
#include "ui_mainwin.h"
#include <algorithm>

const QJsonObject arr_si = {
    {" ", "e+0"},
    {"к", "e+3"},
    {"М", "e+6"},
    {"Г" ,"e+9"}};
const QString arr_sparamet[4] = {"S11", "S21", "S12", "S22"};



MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
    , _validatorFreq(QRegExp("^[1-9]{1,1}[0-9]*[.]{,1}[0-9]{1,3}[кМГ]{,1}$"))
{
    ui->setupUi(this);
    this->createActions();
    qRegisterMetaType<QVector<double>>("QVector<double>");
    ui->statusbar->showMessage(set_win.statusfileconfig());
    link->moveToThread(thread);
    ui->Plot->setChart(chrt);
    chrt->setTitle("График S-Параметра");
    chrt->addSeries(series);
    chrt->addAxis(axisX, Qt::AlignBottom);
    chrt->addAxis(axisY, Qt::AlignLeft);
  //  chrt->createDefaultAxes();
    ui->le_freqstop->setValidator(&_validatorFreq);
    ui->le_freqstart->setValidator(&_validatorFreq);
    ui->le_boundfreq->setValidator(&_validatorFreq);
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::createActions()
{
    connect(ui->ac_help, SIGNAL(aboutToShow()), this, SLOT(show_about()));

    connect(thread, &QThread::finished, link, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::started, [=]() {
        link->connectToHost(set_win.ip_adress, set_win.port);
    });

    connect(this, SIGNAL(changeHost(QString, quint16)), link, SLOT(connectToHost(QString, quint16)));
    connect(this, SIGNAL(disconnect_()), link, SLOT(onDisconnectedFromHost()));
    connect(link, &LinkHandler::sendReciveData, &_dataaccept, &Datahandler::acceptDate);
    connect(link, SIGNAL(FinishedResult()), this, SLOT(updatePlot()));
    connect(link, SIGNAL(StatusConnected(quint16)), this, SLOT(connect_sts(quint16)));
    connect(this, SIGNAL(onSendSettings(QJsonObject)), link, SLOT(sendSettigns(QJsonObject)));
    connect(this, SIGNAL(onSendNumberForChekerFreqBand(QString)), link, SLOT(sendValidatorFreqBand(QString)));

    connect(&_dataaccept, SIGNAL(sendStatusBar(QString)), ui->statusbar, SLOT(showMessage(QString)));
    connect(&_dataaccept, SIGNAL(sendBasisSettings(QJsonObject)), this, SLOT(acceptBasisSetting(QJsonObject)));
    connect(&_dataaccept, SIGNAL(sendValidorFreqBound(double)), this, SLOT(onSetValidatorFreqBand(double)));
}
void MainWin::on_ac_setnet_triggered()
{
    set_win.show();
}

void MainWin::show_about()
{
    about_win.show();
}

void MainWin::on_pb_connect_clicked()
{

    if (ui->pb_connect->text()== "Подключиться"){
        ui->statusbar->showMessage("Попытка подключение...");
        ui->pb_connect->setEnabled(false);
        if (!thread->isRunning()){
            thread->start();
        } else {
            emit changeHost(set_win.ip_adress, set_win.port);
        }
    }else{
        QMetaObject::invokeMethod(link, "onDisconnectedFromHost");

    }
}


void MainWin::connect_sts(quint16 status)
{
    ui->statusbar->showMessage(enumtoString(status));
    switch (status) {
    case LinkHandler::eConnected:
        ui->pb_connect->setText("Отключиться");
        break;
    case LinkHandler::eDisconnected:
        ui->pb_connect->setText("Подключиться");
        ui->pb_result->setEnabled(true);
        break;
    case LinkHandler::eDisconnectedFromHost:
        ui->pb_connect->setText("Подключиться");
        ui->pb_result->setEnabled(true);
        break;
    case LinkHandler::eErrorConnected:
        ui->pb_connect->setText("Подключиться");
        break;
    case LinkHandler::eErrorReciveData:
        ui->pb_result->setEnabled(true);
        break;
    case LinkHandler::eErrorSendCommand:
        ui->pb_result->setEnabled(true);
        break;
    }
    ui->pb_connect->setEnabled(true);
}

void MainWin::on_pb_result_clicked()
{
    if (thread->isRunning()){
        _arrSettingsForSend.insert("F_STAR", ui->le_freqstart->text().remove(QRegExp("[кМГ]")) +
                                   arr_si.value(QString(ui->le_freqstart->text().back())).toString());

        _arrSettingsForSend.insert("F_STOP", ui->le_freqstop->text().remove(QRegExp("[кМГ]")) +
                                   arr_si.value(QString(ui->le_freqstop->text().back())).toString());

        _arrSettingsForSend.insert("S_BAND", ui->le_boundfreq->text().remove(QRegExp("[кМГ]")) +
                                   arr_si.value(QString(ui->le_boundfreq->text().back())).toString());

        _arrSettingsForSend.insert("S_POIN" , QString::number(ui->sb_freqpoint->value()));
        _arrSettingsForSend.insert("S_POW", QString::number(ui->sb_power->value()));
        _arrSettingsForSend.insert("C_DEF", arr_sparamet[ui->cm_sparamet->currentIndex()]);
        ui->pb_result->setEnabled(false);
        emit onSendSettings(_arrSettingsForSend);
        ui->statusbar->showMessage("Ожидание результата...");
        chrt->removeSeries(series);
        this->series->clear();
        QMetaObject::invokeMethod(link, "requestResult");
    }else{
        ui->statusbar->showMessage("Не подключен!");
    }
}

void MainWin::updatePlot()
{
    QVector<double> arryAxis_X = _dataaccept.get_axisx();
    QVector<double> arryAxis_Y = _dataaccept.get_axisyReal();
    double max_AxisX = *std::max_element(arryAxis_X.constBegin(), arryAxis_X.constEnd());
    double min_AxisX = *std::min_element(arryAxis_X.constBegin(), arryAxis_X.constEnd());
    double max_AxisY = *std::max_element(arryAxis_Y.constBegin(), arryAxis_Y.constEnd());
    double min_AxisY = *std::min_element(arryAxis_Y.constBegin(), arryAxis_Y.constEnd());
    if (arryAxis_X.size() == arryAxis_Y.size()){
        axisX->setRange(min_AxisX, max_AxisX);
        axisY->setRange(min_AxisY, max_AxisY);
        axisX->setLabelFormat("%g");
        axisY->setLabelFormat("%g");
        for(int i=0; i<arryAxis_X.size(); i++){
            this->series->append(arryAxis_X[i],arryAxis_Y[i]);
        }
        chrt->addSeries(series);
//        chrt->addAxis(axisX, Qt::AlignBottom);
//        chrt->addAxis(axisY, Qt::AlignLeft);
        //chrt->createDefaultAxes();
        chrt->axes(Qt::Horizontal).back()->setTitleText("Частота, Гц");
        chrt->axes(Qt::Vertical).back()->setTitleText("Мощность, дБ");
        ui->statusbar->showMessage("Результат получен!");
        ui->pb_result->setEnabled(true);
    }
}

void MainWin::acceptBasisSetting(QJsonObject arrSettings)
{
    ui->sb_freqpoint->setMaximum((arrSettings.value("SERV:SWE:POIN?").toInt()));
    ui->sb_power->setRange(arrSettings.value("SERV:SWE:POW:MIN?").toInt(), arrSettings.value("SERV:SWE:POW:MAX?").toInt());
    _arrRangeFreqStartStop.insert("FREQMIN", arrSettings.value("SERV:SWE:FREQ:MIN?"));
    _arrRangeFreqStartStop.insert("FREQMAX", arrSettings.value("SERV:SWE:FREQ:MAX?"));

    ui->le_freqstop->setText(convertoSiString(_arrRangeFreqStartStop.value("FREQMAX").toDouble()));
    ui->le_freqstart->setText(convertoSiString(_arrRangeFreqStartStop.value("FREQMIN").toDouble()));
}

QString MainWin::enumtoString(quint16 number)
{
    switch (number) {
    case LinkHandler::eConnected:
        return "Успешное подключение к серверу";
    case LinkHandler::eConnectedReady:
        return "Отключение от сервера";
    case LinkHandler::eDisconnected:
        return "Потеряна связь";
    case LinkHandler::eDisconnectedFromHost:
        return "Отключение от сервера";
    case LinkHandler::eErrorConnected:
        return "Не удалось подключиться";
    case LinkHandler::eErrorReciveData:
        return "Ошибка в получение данных";
    case LinkHandler::eErrorSendCommand:
        return "Ошибка в отправки команды";
    default:
        return "Не известное состояние";
    }
}

QString MainWin::convertoSiString(double number)
{
    if (number/1e3 < 1e3) {
        return QString::number(number/1e3)+"к";
    }else if (number/1e6 < 1e3 ){
        return QString::number(number/1e6)+"М";
    }else {
        return QString::number(number/1e9)+"Г";
    }
}

void MainWin::on_le_freqstart_editingFinished()
{
    double res = (ui->le_freqstart->text().remove(QRegExp("[кМГ]")) +
                  arr_si.value(QString(ui->le_freqstart->text().back())).toString()).toDouble();
    double res_second = (ui->le_freqstop->text().remove(QRegExp("[кМГ]")) +
                         arr_si.value(QString(ui->le_freqstop->text().back())).toString()).toDouble();

    if (res >= res_second) {
        ui->le_freqstart->setText(QString::number(ui->le_freqstop->text().remove(QRegExp("[кМГ]")).toDouble()-1) + ui->le_freqstart->text().back());
    }
    if (res < _arrRangeFreqStartStop.value("FREQMIN").toDouble()){
        ui->le_freqstart->setText(convertoSiString(_arrRangeFreqStartStop.value("FREQMIN").toDouble()));
    }
    if (res > _arrRangeFreqStartStop.value("FREQMAX").toDouble()){
        ui->le_freqstart->setText(convertoSiString(_arrRangeFreqStartStop.value("FREQMAX").toDouble()));
    }
}

void MainWin::on_le_freqstop_editingFinished()
{
    double res = (ui->le_freqstop->text().remove(QRegExp("[кМГ]"))
                  + arr_si.value(QString(ui->le_freqstop->text().back())).toString()).toDouble();
    double res_second = (ui->le_freqstart->text().remove(QRegExp("[кМГ]")) +
                         arr_si.value(QString(ui->le_freqstart->text().back())).toString()).toDouble();

    if (res <= res_second) {
        ui->le_freqstop->setText(QString::number(ui->le_freqstart->text().remove(QRegExp("[кМГ]")).toDouble()+1)
                                 + ui->le_freqstart->text().back());
    }
    if (res > _arrRangeFreqStartStop.value("FREQMAX").toDouble()){
        ui->le_freqstop->setText(convertoSiString(_arrRangeFreqStartStop.value("FREQMAX").toDouble()));
    }
    if (res < _arrRangeFreqStartStop.value("FREQMIN").toDouble()){
        ui->le_freqstop->setText(convertoSiString(_arrRangeFreqStartStop.value("FREQMIN").toDouble()));
    }
}

void MainWin::on_le_boundfreq_editingFinished()
{
   emit onSendNumberForChekerFreqBand(ui->le_boundfreq->text().remove(QRegExp("[кМГ]")) +
            arr_si.value(QString(ui->le_boundfreq->text().back())).toString());
}

void MainWin::onSetValidatorFreqBand(double num)
{
    ui->le_boundfreq->setText(convertoSiString(num));
}

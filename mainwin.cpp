#include "mainwin.h"
#include "ui_mainwin.h"

const QString arr_si[4] = {"", "E+3", "E+6", "E+9"};
const QString arr_sparamet[4] = {"S11", "S21", "S12", "S22"};

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    ui->setupUi(this);
    this->createActions();
    qRegisterMetaType<QVector<double>>("QVector<double>");
    ui->statusbar->showMessage(set_win.statusfileconfig());
    link->moveToThread(thread);
    ui->Plot->setChart(chrt);
    chrt->setTitle("График S-Параметра");
    chrt->addSeries(series);
    chrt->createDefaultAxes();

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
    connect(this, SIGNAL(sendquerty(QString)), link, SLOT(onSendCommand(QString)));
    connect(this, SIGNAL(changeHost(QString, quint16)), link, SLOT(connectToHost(QString, quint16)));
    connect(this, SIGNAL(disconnect_()), link, SLOT(onDisconnectedFromHost()));

    connect(link, &LinkHandler::sendReciveData, &_dataaccept, &Datahandler::acceptDate);
    connect(&_dataaccept, SIGNAL(sendStatusBar(QString)), ui->statusbar, SLOT(showMessage(QString)));
    connect(link, SIGNAL(FinishedResult()), this, SLOT(updatePlot()));

    connect(link, SIGNAL(StatusConnected(quint16)), this, SLOT(connect_sts(quint16)));
    connect(this, SIGNAL(onSendSettings(QJsonObject)), link, SLOT(sendSettigns(QJsonObject)));

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
        ui->pb_connect->setText("Отключится");
        if (!thread->isRunning()){
            thread->start();
        } else {
            emit changeHost(set_win.ip_adress, set_win.port);
            qDebug()<<set_win.ip_adress;
        }
    }else{
       QMetaObject::invokeMethod(link, "onDisconnectedFromHost");
       ui->statusbar->showMessage("Устройство отключено");
       ui->pb_connect->setText("Подключиться");
    }
}

void MainWin::on_cb_freqstart_currentIndexChanged(int index)
{
    if(index > ui->cb_freqstop->currentIndex()){
        ui->cb_freqstart->setCurrentIndex(ui->cb_freqstop->currentIndex());
        index = ui->cb_freqstop->currentIndex();
    }
    if(index == 0){
     ui->dsb_freqstart->setRange(100,999.9);
     ui->dsb_freqstart->setSingleStep(20);
    } else if(index == 1){
        ui->dsb_freqstart->setRange(1,999.9);
        ui->dsb_freqstart->setSingleStep(2);
    }
    else if(index == 2){
        ui->dsb_freqstart->setRange(1,9);
        ui->dsb_freqstart->setSingleStep(0.2);
    }
}

void MainWin::on_cb_freqstop_currentIndexChanged(int index)
{
    if(index < ui->cb_freqstart->currentIndex()){
        ui->cb_freqstop->setCurrentIndex(ui->cb_freqstart->currentIndex());
        index = ui->cb_freqstart->currentIndex();
    }
    if(index == 0){
     ui->dsb_freqstop->setRange(100,999.9);
     ui->dsb_freqstop->setSingleStep(20);
    } else if(index == 1){
        ui->dsb_freqstop->setRange(1,999.9);
        ui->dsb_freqstop->setSingleStep(2);
    }
    else if(index == 2){
        ui->dsb_freqstop->setRange(1,9);
        ui->dsb_freqstop->setSingleStep(0.2);
    }
}

void MainWin::connect_sts(quint16 status)
{
        ui->statusbar->showMessage(enumtoString(status));
}

void MainWin::on_pb_result_clicked()
{
     _arrSettingsForSend.insert("F_STAR", QString::number(ui->dsb_freqstart->value())+ arr_si[ui->cb_freqstart->currentIndex()+1]);
     _arrSettingsForSend.insert("F_STOP", QString::number(ui->dsb_freqstop->value())+ arr_si[ui->cb_freqstop->currentIndex()+1]);
     _arrSettingsForSend.insert("S_BAND", QString::number(ui->sb_filterbound->value())+ arr_si[ui->cb_filter->currentIndex()]);
     _arrSettingsForSend.insert("S_POIN" , QString::number(ui->sb_freqpoint->value()));
     _arrSettingsForSend.insert("S_POW", QString::number(ui->sb_power->value()));
     _arrSettingsForSend.insert("C_DEF", arr_sparamet[ui->cm_sparamet->currentIndex()]);
     qDebug()<<_arrSettingsForSend;

     if (thread->isRunning()){
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
    qDebug()<< _dataaccept.get_axisx();
    qDebug()<< _dataaccept.get_axisyReal();
    QVector<double> axis_X = _dataaccept.get_axisx();
    QVector<double> axis_Y = _dataaccept.get_axisyReal();
    if (axis_X.size() == axis_Y.size()){
        for(int i=0; i<axis_X.size(); i++){
            this->series->append(axis_X[i],axis_Y[i]);
        }
        chrt->addSeries(series);
        chrt->createDefaultAxes();
        chrt->axes(Qt::Horizontal).back()->setTitleText("Частота, Гц");
        chrt->axes(Qt::Vertical).back()->setTitleText("Мощность, дБ");
        ui->statusbar->showMessage("Результат получен!");
        ui->pb_result->setEnabled(true);
    }
}

void MainWin::on_pushButton_clicked()
{
    emit sendquerty( ui->lineEdit1->text());
}

void MainWin::on_dsb_freqstart_valueChanged(double arg1)
{
    if ((ui->cb_freqstop->currentIndex() == ui->cb_freqstart->currentIndex()) && (arg1 >= ui->dsb_freqstop->value())) {
            ui->dsb_freqstart->setValue(ui->dsb_freqstop->value() - ui->dsb_freqstart->singleStep());
        }
}

void MainWin::on_dsb_freqstop_valueChanged(double arg1)
{
    if ((ui->cb_freqstop->currentIndex() == ui->cb_freqstart->currentIndex()) && (arg1 <= ui->dsb_freqstart->value())) {
        ui->dsb_freqstop->setValue(ui->dsb_freqstart->value()+ ui->dsb_freqstop->singleStep());
    }
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

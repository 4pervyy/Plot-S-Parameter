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
   // chrt = new QChart;
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

    connect(this, SIGNAL(sendquerty(QString, bool)), link, SLOT(send(QString, bool)));
    connect(this, SIGNAL(sendquertyDataplot(bool, quint16)), link, SLOT(Dataforplot(bool, quint16)));
    connect(this, SIGNAL(changeHost(QString, quint16)), link, SLOT(connectToHost(QString, quint16)));
    connect(this, SIGNAL(disconnect_()), link, SLOT(Disconnected()));

    connect(link, SIGNAL(StatusConnected(QString)), this, SLOT(connect_sts(QString)));
    connect(link, SIGNAL(sendDataForPlot(QVector<double>, bool)), this, SLOT(recivedataplot(QVector<double>, bool)));

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
        ui->pb_connect->setEnabled(false);
        ui->statusbar->showMessage("Попытка подключение...");
        ui->pb_connect->setText("Отключится");
        if (!thread->isRunning()){
            thread->start();
        } else {
            emit changeHost(set_win.ip_adress, set_win.port);
            qDebug()<<set_win.ip_adress;
        }
    }else{
       QMetaObject::invokeMethod(link, "Disconnected");
       ui->statusbar->showMessage("Устройство отключено");
       ui->pb_connect->setText("Подключиться");
    }
}

//Смена диапазона для начальной частоты
void MainWin::on_cb_freqstart_currentIndexChanged(int index)
{
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

//Смена диапазона для конечной частоты
void MainWin::on_cb_freqstop_currentIndexChanged(int index)
{
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
//Слот получение статусов сервера
void MainWin::connect_sts(QString status)
{
        ui->statusbar->showMessage(status);
        if (status == "Не удалось подключиться!"){
            ui->pb_connect->setText("Подключиться");
        }else if(status == "Команда не отправлена!"){
            ui->pb_result->setEnabled(true);
        }else if(status == "Устройство отключено"){
            ui->pb_result->setEnabled(true);
            ui->pb_connect->setText("Подключиться");
        }
        if(!ui->pb_connect->isEnabled()){
            ui->pb_connect->setEnabled(true);
        }

}
//Кнопка измерение
void MainWin::on_pb_result_clicked()
{
    if (thread->isRunning()){
        ui->statusbar->showMessage("Ожидание результата...");
        ui->pb_result->setEnabled(false);
        chrt->removeSeries(series);
        this->series->clear();
        //Отправка команд
        emit sendquerty("SENS:FREQ:STAR " + QString::number(ui->dsb_freqstart->value())+ arr_si[ui->cb_freqstart->currentIndex()+1], false);
        emit sendquerty("SENS:FREQ:STOP " + QString::number(ui->dsb_freqstop->value())+ arr_si[ui->cb_freqstop->currentIndex()+1], false);
        emit sendquerty("SENS:BAND "+ QString::number(ui->sb_filterbound->value())+ arr_si[ui->cb_filter->currentIndex()], false);
        emit sendquerty("SENS:SWE:POIN " + QString::number(ui->sb_freqpoint->value()),false);
        emit sendquerty("SOUR:POW " + QString::number(ui->sb_power->value()),false); //7777
        emit sendquerty("CALC:PAR:DEF " + arr_sparamet[ui->cm_sparamet->currentIndex()],false);
        //Получение результатов
        emit sendquertyDataplot(true, ui->sb_freqpoint->value());
        emit sendquertyDataplot(false);
    }else{
        ui->statusbar->showMessage("Не подключен!");
    }
}

//Передача результата в график
void MainWin::recivedataplot(QVector<double> data, bool axis)
{
    if(axis){
        this->buffer_y = data;
     }else{
        for(int i=0; i<data.size(); i++){
            this->series->append(data[i],this->buffer_y[i]);
        }
        chrt->addSeries(series);
        chrt->createDefaultAxes();
        chrt->axes(Qt::Horizontal).back()->setTitleText("Частота, Гц");
        chrt->axes(Qt::Vertical).back()->setTitleText("Мощность, дБ");
        ui->statusbar->showMessage("Результат получен!");
        ui->pb_result->setEnabled(true);
    }
}

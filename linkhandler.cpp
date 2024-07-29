// socket_handler.cpp

#include "linkhandler.h"
#include <QHostAddress>
#include <QDebug>

LinkHandler::LinkHandler(){
    link = new QTcpSocket(this);

    connect(link, &QTcpSocket::connected, this, &LinkHandler::onConnected);
    connect(link, &QTcpSocket::disconnected, this, &LinkHandler::onDisconnected);
}

LinkHandler::~LinkHandler() {
    link->close();
}

//Проверяем соединения и подключаемся с серверу
void LinkHandler::connectToHost(const QString &host, quint16 port){
    if (link->state() == QAbstractSocket::UnconnectedState) {
         link->connectToHost(host, port);
        if(!link->waitForConnected()){
            emit StatusConnected("Не удалось подключиться!");
        }
    }else{
         emit StatusConnected("Устройство уже подключено!");
    }
}
//QTcpSocket::connected обработка сигнала и отправка сигнала о успешному подключению
void LinkHandler::onConnected() {
    link->write("*idn?\n");
    if (link->waitForReadyRead()){
        emit StatusConnected("Устройство подключено: " + QString(link->readAll()).remove("\n"));}
}
//QTcpSocket::disconnected обработка сигнала и отправка сигнала о отключение
void LinkHandler::onDisconnected() {
    emit StatusConnected("Устройство отключено");
    qDebug() << "Disconnected from host";
}
//Принимает команду и определяет это является команда(\n) или запрос(?\n)
void LinkHandler::send(QString command,bool readdata)
{
    link->write((command+"\n").toLocal8Bit());
    if(!link->waitForBytesWritten()){
        emit StatusConnected("Команда не отправлена!");
    }
    if (readdata){
        emit sendReciveData(QString(link->readAll()).remove("\n"));
        if(!link->waitForReadyRead()){
            emit StatusConnected("Данные команды не получены!");
        }
    }
}
//Принимает тип оси и количество частотных точек, для определение времени расчета программы S2VNA. Так же тут обработка полученных данных и отправка их в основной объект
void LinkHandler::Dataforplot(bool axis, quint16 point)
{
    if(axis){
        link->write(("CALC:DATA:FDAT?\n"));
        QThread::msleep((point*1000)/20);
        if (link->waitForReadyRead()){
           QVector<double> buffer = toArrayDouble(QString(link->readAll()).remove("\n"));
           QVector<double> result;
            for(int i=0; i < buffer.size(); i++){
                if(i%2 == 0){
                    result.append(buffer[i]);
                }
            }
           emit sendDataForPlot(result, axis);
        }
    }else{
        link->write(("SENS:FREQ:DATA?\n"));
        if (link->waitForReadyRead()){
        emit sendDataForPlot(toArrayDouble(QString(link->readAll()).remove("\n")), axis);}
    }
}

//Команда отключение от сервера с проверкой соединения
void LinkHandler::Disconnected()
{
    if (link->state() == QAbstractSocket::ConnectedState || link->state() == QAbstractSocket::ConnectingState) {
            link->disconnectFromHost();
            if (link->state() != QAbstractSocket::UnconnectedState) {
                link->waitForDisconnected();
            }
        }
}

//Преобразователь строки в массив double
QVector<double> LinkHandler::toArrayDouble(const QString &str)
{
    QVector<double> da;
    QStringList list = str.split(",");
    bool cheker;
        for (int i = 0; i < list.size(); ++i) {
            da.append(list[i].toDouble(&cheker));
            if (!cheker) {
                qDebug() << "Ошибка преобразования строки:" << list[i];
            }
        }
     return da;
}

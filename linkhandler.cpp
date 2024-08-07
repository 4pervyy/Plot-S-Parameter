// socket_handler.cpp

#include "linkhandler.h"


LinkHandler::LinkHandler(){
    _link = new QTcpSocket(this);
    connect(_link, &QTcpSocket::readyRead, this, &LinkHandler::onReadyData);
    connect(_link, &QTcpSocket::connected, this, &LinkHandler::onConnected);
    connect(_link, &QTcpSocket::disconnected, this, &LinkHandler::onDisconnected);
}

LinkHandler::~LinkHandler() {
    _link->close();
}

void LinkHandler::connectToHost(const QString &host, quint16 port){
    if (_link->state() == QAbstractSocket::UnconnectedState) {
        _link->connectToHost(host, port);
        if(!_link->waitForConnected()){
            emit StatusConnected(eErrorConnected);
        }else {
            onSendCommand("SERV:SWE:FREQ:MAX?");
            onSendCommand("SERV:SWE:FREQ:MIN?");
            onSendCommand("SERV:SWE:POW:MAX?");
            onSendCommand("SERV:SWE:POW:MIN?");
            onSendCommand("SERV:SWE:POIN?");}
    }else{
        emit StatusConnected(eConnectedReady);
    }
}

void LinkHandler::onReadyData()
{
    _bufferReciveData.append(_link->readAll());
    if(_bufferReciveData.lastIndexOf("\n") > 0){
        _bufferReciveData.remove("\n");
        emit sendReciveData(_bufferReciveData, _lastCommandSend);
        _bufferReciveData.clear();
         emit successCommand();
    }
}

void LinkHandler::onConnected() {
    emit StatusConnected(eConnected);
}
void LinkHandler::onDisconnected() {
    emit StatusConnected(eDisconnected);
}

void LinkHandler::onSendCommand(QString command)
{
    _link->write((command+"\n").toLocal8Bit());

    if(!_link->waitForBytesWritten()){
        emit StatusConnected(eErrorSendCommand);
    }
    if(command.lastIndexOf("?")> 0){
        QEventLoop _waitCommand;
        connect(this, SIGNAL(successCommand()), &_waitCommand, SLOT(quit()));
         _lastCommandSend = command ;
          _waitCommand.exec();
    }
}

void LinkHandler::requestResult()
{
     onSendCommand("*OPC?");
     onSendCommand("CALC:DATA:FDAT?");
     onSendCommand("SENS:FREQ:DATA?");

    emit FinishedResult();
}

void LinkHandler::onDisconnectedFromHost()
{
    if (_link->state() == QAbstractSocket::ConnectedState || _link->state() == QAbstractSocket::ConnectingState) {
        _link->disconnectFromHost();
        if (_link->state() != QAbstractSocket::UnconnectedState) {
            _link->waitForDisconnected();
        }
    }
}

void LinkHandler::sendSettigns(QJsonObject arrsettings)
{
    onSendCommand("SENS:FREQ:STAR " + arrsettings.value("F_STAR").toString());
    onSendCommand("SENS:FREQ:STOP " + arrsettings.value("F_STOP").toString());
    onSendCommand("SENS:BAND " + arrsettings.value("S_BAND").toString());
    onSendCommand("SENS:SWE:POIN " + arrsettings.value("S_POIN").toString());
    onSendCommand("SOUR:POW " + arrsettings.value("S_POW").toString());
    onSendCommand("CALC:PAR:DE " + arrsettings.value("C_DEF").toString());

    onSendCommand(":TRIG:SOUR BUS");
    onSendCommand(":TRIG:SING");
}



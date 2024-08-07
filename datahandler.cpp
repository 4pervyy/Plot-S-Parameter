#include "datahandler.h"
//
QVector<double> Datahandler::get_axisx()
{
    return _AxisX;
}
QVector<double> Datahandler::get_axisy()
{
    return _AxisY;
}

QVector<double> Datahandler::get_axisyReal()
{
    QVector<double> result;
    for(int i=0; i < this->_AxisY.size(); i++){
        if(i%2 == 0){
            result.append(this->_AxisY[i]);
        }
    }
    return result;
}

void Datahandler::acceptDate(QString arrDate, QString lastSendCommand)
{
    qDebug()<< arrDate << "Command :" << lastSendCommand << endl;
    if (lastSendCommand == "SENS:FREQ:DATA?")
    {
        _AxisX = toArrayDouble(arrDate);
    } else if (lastSendCommand == "CALC:DATA:FDAT?")
    {
        _AxisY = toArrayDouble(arrDate);
    }else if (lastSendCommand.lastIndexOf("SWE") > 0) {
        handlerBasisSettigns(arrDate, lastSendCommand);
    }else if(lastSendCommand == "SENS:BAND?"){
        emit sendValidorFreqBound(arrDate.toDouble());
    } else
    {
        emit sendStatusBar(QString(arrDate));
    }
}

QVector<double> Datahandler::toArrayDouble(const QString &str)
{
    QVector<double> result;
    QStringList list = str.split(",");
    bool cheker;
    for (int i = 0; i < list.size(); ++i) {
        result.append(list[i].toDouble(&cheker));
        if (!cheker) {
            qDebug() << "Ошибка преобразования строки:" << list[i];
        }
    }
    return result;
}

void Datahandler::handlerBasisSettigns(QString data, QString command)
{
    _arrBasisSettings.insert(command, data.toDouble());
    if (command == "SERV:SWE:POIN?"){
        emit sendBasisSettings(_arrBasisSettings);
    }
}


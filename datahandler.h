#pragma once
#include <QObject>
#include <QDoubleSpinBox>
#include <QDebug>
#include <QJsonObject>

class Datahandler: public QObject
{
    Q_OBJECT
signals:
    void sendStatusBar(QString text);
    void sendReciveResult();
    void sendBasisSettings(QJsonObject);
public:
    QVector<double> get_axisx();
    QVector<double> get_axisy();
    QVector<double> get_axisyReal();
public slots:
    void acceptDate(QString arrDate, QString lastSendCommand);

private:
    QVector<double> _AxisX;
    QVector<double> _AxisY;
    QJsonObject _arrBasisSettings;
    QVector<double> toArrayDouble(const QString& str);
    void handlerBasisSettigns(QString data, QString command);
};

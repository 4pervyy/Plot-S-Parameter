// socket_handler.h

#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

#include "I_link.h"
#include <QTcpSocket>
#include <QThread>
#include <QJsonObject>
#include <QEventLoop>


class LinkHandler : public linkInterface {
    Q_OBJECT
public:
    LinkHandler();
    ~LinkHandler() override;
    enum eStatusDevice {eConnected, eDisconnected, eDisconnectedFromHost, eErrorSendCommand, eErrorReciveData, eConnectedReady, eErrorConnected };

signals:
    void sendStatusCommand(bool stats);
    void sendReciveData(QString data, QString lastCommand);
    void StatusConnected(quint16 statusLink);
    void sendDataForPlot(QVector<double> data, bool axis);
    void FinishedResult();
    void successCommand();
public slots:
    void connectToHost(const QString &host, quint16 port) override;
    void onReadyData() override;
    void onConnected() override;
    void onDisconnected() override;
    void onSendCommand(QString command) override;
    void requestResult() override;
    void onDisconnectedFromHost() override;

    void sendSettigns(QJsonObject arrsettings);
    void queueCammand(QString command);

private:
    QTcpSocket *_link;
    QEventLoop *_waitCommand;
    QString _lastCommandSend = "null";
    QString _bufferReciveData;
    QString _queueCommandSend = "null";
};

#endif // SOCKET_HANDLER_H

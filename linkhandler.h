// socket_handler.h

#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

#include "linkInterface.h"
#include <QTcpSocket>
#include <QThread>

class LinkHandler : public linkInterface {
    Q_OBJECT

public:
    LinkHandler();
    ~LinkHandler();
signals:
    void sendStatusCommand(bool stats);
    void sendReciveData(QString data);
    void StatusConnected(QString data);
    void sendDataForPlot(QVector<double> data, bool axis);
public slots:
    void connectToHost(const QString &host, quint16 port) override;
    void onConnected() override;
    void onDisconnected() override;
    void send(QString command, bool) override;
    void Dataforplot(bool axis, quint16 point) override;
    void Disconnected() override;

private:
    QTcpSocket *link;
    QVector<double> toArrayDouble(const QString& str);
};

#endif // SOCKET_HANDLER_H

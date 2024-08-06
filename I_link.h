#ifndef I_LINK_H
#define I_LINK_H
#include <QObject>

class linkInterface: public QObject {
Q_OBJECT
public slots:
    virtual void connectToHost(const QString &host, quint16 port) = 0;
    virtual void onConnected() = 0;
    virtual void onDisconnected() = 0;
    virtual void onReadyData() = 0;
    virtual void onSendCommand(QString command)  = 0;
    virtual void requestResult() = 0;
    virtual void onDisconnectedFromHost() = 0;

};

#endif // I_LINK_H

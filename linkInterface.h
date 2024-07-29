#ifndef LINKINTERFACE_H
#define LINKINTERFACE_H
#include <QObject>

class linkInterface: public QObject {
Q_OBJECT
public slots:
    virtual void connectToHost(const QString &host, quint16 port) = 0;
    virtual void onConnected() = 0;
    virtual void onDisconnected() = 0;
    virtual void send(QString command, bool)  = 0;
    virtual void Dataforplot(bool axis, quint16 point) = 0;
    virtual void Disconnected() = 0;

};

#endif // LINKINTERFACE_H

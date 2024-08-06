#ifndef SETTINGS_NETWORK_H
#define SETTINGS_NETWORK_H

#include <QWidget>
#include <QFile>
#include <QDebug>

namespace Ui {
class Settings_network;
}

class Settings_network : public QWidget
{
    Q_OBJECT
public:
    explicit Settings_network(QWidget *parent = nullptr);
    ~Settings_network();
    void acccpet_set();
    QFile conf;
    QString statusfileconfig();
    QString ip_adress;
    quint16 port;

private slots:
    void on_pb_cancel_clicked();
    void on_pb_accept_clicked();


private:
    Ui::Settings_network *ui;
signals:
    void updateDataSettings();

};

#endif // SETTINGS_NETWORK_H

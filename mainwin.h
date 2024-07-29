#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include "settings_network.h"
#include "about.h"
#include "linkhandler.h"
#include <QThread>
#include <QtCharts>
#include <QMetaObject>

using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWin; }
QT_END_NAMESPACE

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();
    void createActions();


private slots:
    void on_ac_setnet_triggered();
    void show_about();
    void on_pb_connect_clicked();
    void on_cb_freqstart_currentIndexChanged(int index);
    void on_cb_freqstop_currentIndexChanged(int index);
    void connect_sts(QString status);
    void on_pb_result_clicked();
    void recivedataplot(QVector<double> data, bool axis);

private:
    Ui::MainWin *ui;
    unsigned short  freqstart_si = 0;
    unsigned short  freqstop_si = 0;
    QThread *thread = new QThread();
    LinkHandler *link = new LinkHandler();
    QChart *chrt = new QChart;
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    QLineSeries* series = new QLineSeries();
    QVector<double> buffer_y;
    Settings_network set_win;
    About about_win;

signals:
    void disconnect_();
    void sendquerty(QString str, bool ReciveData);
    void sendquertyDataplot(bool axis, quint16 point = 50);
    void changeHost(const QString &host, quint16 port);
};

#endif // MAINWIN_H

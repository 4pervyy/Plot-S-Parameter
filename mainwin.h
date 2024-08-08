#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QThread>
#include <QtCharts>
#include <QMetaObject>
#include <QJsonArray>

#include "settings_network.h"
#include "about.h"
#include "linkhandler.h"
#include "datahandler.h"
#include "supportclass.h"

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



private slots:
    void on_ac_setnet_triggered();
    void show_about();
    void on_pb_connect_clicked();
    void connect_sts(quint16 status);
    void on_pb_result_clicked();
    void updatePlot();
    void acceptBasisSetting(QJsonObject arrSettings);
    void on_le_freqstart_editingFinished();
    void on_le_freqstop_editingFinished();
    void on_le_boundfreq_editingFinished();
    void onSetValidatorFreqBand(double num);

private:
    Ui::MainWin *ui;
    QThread *thread = new QThread();
    LinkHandler *link = new LinkHandler();
    QChart *chrt = new QChart;
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    QLineSeries* series = new QLineSeries();
    Settings_network set_win;
    About about_win;
    Datahandler _dataaccept;
    QJsonObject _arrSettingsForSend;
    QJsonObject _arrRangeFreqStartStop;
    SupportClass _sc;
    QRegExpValidator _validatorFreq;
    QString enumtoString(quint16 number);
    void createActions();



signals:
    void disconnect_();
    void sendquerty(QString str);
    void sendquertyDataplot(bool axis, quint16 point = 50);
    void changeHost(const QString &host, quint16 port);
    void onSendSettings(QJsonObject);
    void onSendNumberForChekerFreqBand(QString);
};





#endif // MAINWIN_H

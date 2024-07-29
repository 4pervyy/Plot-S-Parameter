#include "settings_network.h"
#include "ui_settings_network.h"

Settings_network::Settings_network(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings_network)
{
    ui->setupUi(this);
    this->conf.setFileName("conf.cfg");

}

Settings_network::~Settings_network()
{
    delete ui;
}

void Settings_network::acccpet_set()
{
    ui->le_ipadress->setText(this->ip_adress);
    ui->sb_port->setValue(this->port);
}

QString Settings_network::statusfileconfig()
{
    //Открываем файл и проверяем его наличие
    if(QFile::exists("conf.cfg"))
    {
        this->conf.open(QIODevice::ReadOnly);
        QString str = this->conf.readAll();
        this->port = str.mid(str.indexOf(":")+1,4).toInt();
        this->ip_adress = str.mid(0, str.indexOf(":"));
        qDebug()<< port << ip_adress;
        this->conf.close();
        this->acccpet_set();
        return "Файл настроек найден";
    }else{
        //Если нет то создаем новый с настройками по умолчанию
        this->port = 5025;
        this->ip_adress = "localhost";
        this->acccpet_set();
        this->conf.open(QIODevice::WriteOnly);
        QString str = ui->le_ipadress->text() + ":" + ui->sb_port->text();
        qDebug()<< str;
        this->conf.write(str.toLocal8Bit());
        this->conf.close();
        return "Файл настроек не найден, будет создан новый";}

}

void Settings_network::on_pb_cancel_clicked()
{
    close();
}

void Settings_network::on_pb_accept_clicked()
{
    // Сигнал кнопки "принять", где записываем данные в файл
    this->conf.open(QIODevice::WriteOnly);
    QString str = ui->le_ipadress->text() + ":" + ui->sb_port->text();
    this->port = ui->sb_port->value();
    this->ip_adress = ui->le_ipadress->text();
    qDebug()<< str;
    this->conf.write(str.toLocal8Bit());
    this->conf.close();
    close();
}

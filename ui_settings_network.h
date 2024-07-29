/********************************************************************************
** Form generated from reading UI file 'settings_network.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_NETWORK_H
#define UI_SETTINGS_NETWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings_network
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *le_ipadress;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *sb_port;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_accept;
    QPushButton *pb_cancel;

    void setupUi(QWidget *Settings_network)
    {
        if (Settings_network->objectName().isEmpty())
            Settings_network->setObjectName(QString::fromUtf8("Settings_network"));
        Settings_network->resize(260, 178);
        verticalLayout = new QVBoxLayout(Settings_network);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(Settings_network);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        le_ipadress = new QLineEdit(groupBox);
        le_ipadress->setObjectName(QString::fromUtf8("le_ipadress"));
        le_ipadress->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(le_ipadress);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Settings_network);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        sb_port = new QSpinBox(groupBox_2);
        sb_port->setObjectName(QString::fromUtf8("sb_port"));
        sb_port->setMaximumSize(QSize(100, 16777215));
        sb_port->setMinimum(1000);
        sb_port->setMaximum(9999);
        sb_port->setValue(5025);

        horizontalLayout_2->addWidget(sb_port);


        verticalLayout->addWidget(groupBox_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pb_accept = new QPushButton(Settings_network);
        pb_accept->setObjectName(QString::fromUtf8("pb_accept"));
        pb_accept->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(pb_accept);

        pb_cancel = new QPushButton(Settings_network);
        pb_cancel->setObjectName(QString::fromUtf8("pb_cancel"));
        pb_cancel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(pb_cancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Settings_network);

        QMetaObject::connectSlotsByName(Settings_network);
    } // setupUi

    void retranslateUi(QWidget *Settings_network)
    {
        Settings_network->setWindowTitle(QCoreApplication::translate("Settings_network", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\201\320\265\321\202\320\270", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Settings_network", "IP-\320\260\320\264\321\200\320\265\321\201:", nullptr));
        le_ipadress->setText(QCoreApplication::translate("Settings_network", "255.255.255.255", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Settings_network", "\320\237\320\276\321\200\321\202:", nullptr));
        pb_accept->setText(QCoreApplication::translate("Settings_network", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        pb_cancel->setText(QCoreApplication::translate("Settings_network", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Settings_network: public Ui_Settings_network {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_NETWORK_H

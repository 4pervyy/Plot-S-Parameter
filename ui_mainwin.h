/********************************************************************************
** Form generated from reading UI file 'mainwin.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIN_H
#define UI_MAINWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qchartview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWin
{
public:
    QAction *ac_setnet;
    QAction *menu_3;
    QAction *action;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QChartView *Plot;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_connect;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *gb_freqstart;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *dsb_freqstart;
    QComboBox *cb_freqstart;
    QGroupBox *gb_freqstop;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *dsb_freqstop;
    QComboBox *cb_freqstop;
    QGroupBox *gb_filterbound;
    QHBoxLayout *horizontalLayout_5;
    QDoubleSpinBox *sb_filterbound;
    QComboBox *cb_filter;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_6;
    QSpinBox *sb_freqpoint;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_7;
    QSpinBox *sb_power;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QComboBox *cm_sparamet;
    QPushButton *pb_result;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *ac_help;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWin)
    {
        if (MainWin->objectName().isEmpty())
            MainWin->setObjectName(QString::fromUtf8("MainWin"));
        MainWin->resize(911, 643);
        ac_setnet = new QAction(MainWin);
        ac_setnet->setObjectName(QString::fromUtf8("ac_setnet"));
        menu_3 = new QAction(MainWin);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        action = new QAction(MainWin);
        action->setObjectName(QString::fromUtf8("action"));
        centralwidget = new QWidget(MainWin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Plot = new QChartView(centralwidget);
        Plot->setObjectName(QString::fromUtf8("Plot"));

        verticalLayout->addWidget(Plot);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pb_connect = new QPushButton(centralwidget);
        pb_connect->setObjectName(QString::fromUtf8("pb_connect"));
        pb_connect->setEnabled(true);
        QFont font;
        font.setPointSize(10);
        pb_connect->setFont(font);

        horizontalLayout_2->addWidget(pb_connect);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gb_freqstart = new QGroupBox(centralwidget);
        gb_freqstart->setObjectName(QString::fromUtf8("gb_freqstart"));
        gb_freqstart->setMaximumSize(QSize(200, 16777215));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        font1.setKerning(true);
        gb_freqstart->setFont(font1);
        horizontalLayout_3 = new QHBoxLayout(gb_freqstart);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        dsb_freqstart = new QDoubleSpinBox(gb_freqstart);
        dsb_freqstart->setObjectName(QString::fromUtf8("dsb_freqstart"));
        dsb_freqstart->setFont(font1);
        dsb_freqstart->setDecimals(1);
        dsb_freqstart->setMinimum(100.000000000000000);
        dsb_freqstart->setMaximum(999.000000000000000);
        dsb_freqstart->setSingleStep(20.000000000000000);

        horizontalLayout_3->addWidget(dsb_freqstart);

        cb_freqstart = new QComboBox(gb_freqstart);
        cb_freqstart->addItem(QString());
        cb_freqstart->addItem(QString());
        cb_freqstart->addItem(QString());
        cb_freqstart->setObjectName(QString::fromUtf8("cb_freqstart"));
        cb_freqstart->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_3->addWidget(cb_freqstart);


        verticalLayout_2->addWidget(gb_freqstart);

        gb_freqstop = new QGroupBox(centralwidget);
        gb_freqstop->setObjectName(QString::fromUtf8("gb_freqstop"));
        gb_freqstop->setMaximumSize(QSize(200, 16777215));
        gb_freqstop->setFont(font);
        horizontalLayout_4 = new QHBoxLayout(gb_freqstop);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        dsb_freqstop = new QDoubleSpinBox(gb_freqstop);
        dsb_freqstop->setObjectName(QString::fromUtf8("dsb_freqstop"));
        dsb_freqstop->setFont(font);
        dsb_freqstop->setDecimals(1);
        dsb_freqstop->setMinimum(100.000000000000000);
        dsb_freqstop->setMaximum(999.899999999999977);
        dsb_freqstop->setSingleStep(20.000000000000000);
        dsb_freqstop->setValue(300.000000000000000);

        horizontalLayout_4->addWidget(dsb_freqstop);

        cb_freqstop = new QComboBox(gb_freqstop);
        cb_freqstop->addItem(QString());
        cb_freqstop->addItem(QString());
        cb_freqstop->addItem(QString());
        cb_freqstop->setObjectName(QString::fromUtf8("cb_freqstop"));
        cb_freqstop->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(cb_freqstop);


        verticalLayout_2->addWidget(gb_freqstop);

        gb_filterbound = new QGroupBox(centralwidget);
        gb_filterbound->setObjectName(QString::fromUtf8("gb_filterbound"));
        gb_filterbound->setMaximumSize(QSize(200, 16777215));
        gb_filterbound->setFont(font);
        horizontalLayout_5 = new QHBoxLayout(gb_filterbound);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        sb_filterbound = new QDoubleSpinBox(gb_filterbound);
        sb_filterbound->setObjectName(QString::fromUtf8("sb_filterbound"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        sb_filterbound->setFont(font2);
        sb_filterbound->setDecimals(1);
        sb_filterbound->setMinimum(1.000000000000000);
        sb_filterbound->setMaximum(1000.000000000000000);
        sb_filterbound->setSingleStep(10.000000000000000);
        sb_filterbound->setValue(100.000000000000000);

        horizontalLayout_5->addWidget(sb_filterbound);

        cb_filter = new QComboBox(gb_filterbound);
        cb_filter->addItem(QString());
        cb_filter->addItem(QString());
        cb_filter->addItem(QString());
        cb_filter->setObjectName(QString::fromUtf8("cb_filter"));
        cb_filter->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_5->addWidget(cb_filter);


        verticalLayout_2->addWidget(gb_filterbound);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMaximumSize(QSize(200, 16777215));
        groupBox_4->setFont(font);
        verticalLayout_6 = new QVBoxLayout(groupBox_4);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        sb_freqpoint = new QSpinBox(groupBox_4);
        sb_freqpoint->setObjectName(QString::fromUtf8("sb_freqpoint"));
        sb_freqpoint->setFont(font2);
        sb_freqpoint->setLayoutDirection(Qt::LeftToRight);
        sb_freqpoint->setMinimum(1);
        sb_freqpoint->setMaximum(200);
        sb_freqpoint->setValue(20);

        verticalLayout_6->addWidget(sb_freqpoint);


        verticalLayout_2->addWidget(groupBox_4);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(200, 16777215));
        groupBox->setFont(font);
        verticalLayout_7 = new QVBoxLayout(groupBox);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        sb_power = new QSpinBox(groupBox);
        sb_power->setObjectName(QString::fromUtf8("sb_power"));
        sb_power->setFont(font);
        sb_power->setMinimum(-60);
        sb_power->setMaximum(15);

        verticalLayout_7->addWidget(sb_power);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        cm_sparamet = new QComboBox(groupBox_2);
        cm_sparamet->addItem(QString());
        cm_sparamet->addItem(QString());
        cm_sparamet->addItem(QString());
        cm_sparamet->addItem(QString());
        cm_sparamet->setObjectName(QString::fromUtf8("cm_sparamet"));
        cm_sparamet->setMaximumSize(QSize(16777215, 16777215));
        QFont font3;
        font3.setPointSize(10);
        font3.setStrikeOut(false);
        font3.setKerning(true);
        cm_sparamet->setFont(font3);
        cm_sparamet->setContextMenuPolicy(Qt::DefaultContextMenu);
        cm_sparamet->setEditable(false);

        verticalLayout_3->addWidget(cm_sparamet);


        verticalLayout_2->addWidget(groupBox_2);

        pb_result = new QPushButton(centralwidget);
        pb_result->setObjectName(QString::fromUtf8("pb_result"));
        pb_result->setMaximumSize(QSize(200, 16777215));
        pb_result->setFont(font);

        verticalLayout_2->addWidget(pb_result);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWin->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWin);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 911, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        ac_help = new QMenu(menubar);
        ac_help->setObjectName(QString::fromUtf8("ac_help"));
        MainWin->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWin);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWin->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(ac_help->menuAction());
        menu->addAction(ac_setnet);

        retranslateUi(MainWin);

        QMetaObject::connectSlotsByName(MainWin);
    } // setupUi

    void retranslateUi(QMainWindow *MainWin)
    {
        MainWin->setWindowTitle(QCoreApplication::translate("MainWin", "MainWin", nullptr));
        ac_setnet->setText(QCoreApplication::translate("MainWin", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \321\201\320\265\321\202\320\270", nullptr));
        menu_3->setText(QCoreApplication::translate("MainWin", "menu_2", nullptr));
        action->setText(QCoreApplication::translate("MainWin", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        pb_connect->setText(QCoreApplication::translate("MainWin", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217", nullptr));
        gb_freqstart->setTitle(QCoreApplication::translate("MainWin", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\260\321\217 \321\207\320\260\321\201\321\202\320\276\321\202\320\260, \320\223\321\206", nullptr));
        dsb_freqstart->setSuffix(QString());
        cb_freqstart->setItemText(0, QCoreApplication::translate("MainWin", "\320\272\320\223\321\206", nullptr));
        cb_freqstart->setItemText(1, QCoreApplication::translate("MainWin", "\320\234\320\223\321\206", nullptr));
        cb_freqstart->setItemText(2, QCoreApplication::translate("MainWin", "\320\223\320\223\321\206", nullptr));

        cb_freqstart->setCurrentText(QCoreApplication::translate("MainWin", "\320\272\320\223\321\206", nullptr));
        gb_freqstop->setTitle(QCoreApplication::translate("MainWin", "\320\232\320\276\320\275\320\265\321\207\320\275\320\260\321\217 \321\207\320\260\321\201\321\202\320\276\321\202\320\260, \320\223\321\206", nullptr));
        cb_freqstop->setItemText(0, QCoreApplication::translate("MainWin", "\320\272\320\223\321\206", nullptr));
        cb_freqstop->setItemText(1, QCoreApplication::translate("MainWin", "\320\234\320\223\321\206", nullptr));
        cb_freqstop->setItemText(2, QCoreApplication::translate("MainWin", "\320\223\320\223\321\206", nullptr));

        cb_freqstop->setCurrentText(QCoreApplication::translate("MainWin", "\320\272\320\223\321\206", nullptr));
        gb_filterbound->setTitle(QCoreApplication::translate("MainWin", "\320\237\320\276\320\273\320\276\321\201\320\260 \321\204\320\270\320\273\321\214\321\202\321\200\320\260 \320\237\320\247, \320\223\321\206", nullptr));
        cb_filter->setItemText(0, QCoreApplication::translate("MainWin", "\320\223\321\206", nullptr));
        cb_filter->setItemText(1, QCoreApplication::translate("MainWin", "\320\272\320\223\321\206", nullptr));
        cb_filter->setItemText(2, QCoreApplication::translate("MainWin", "\320\234\320\223\321\206", nullptr));

        cb_filter->setCurrentText(QCoreApplication::translate("MainWin", "\320\223\321\206", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWin", "\320\247\320\270\321\201\320\273\320\276 \321\207\320\260\321\201\321\202\320\276\321\202\320\275\321\213\321\205 \321\202\320\276\321\207\320\265\320\272", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWin", "\320\234\320\276\321\211\320\275\320\276\321\201\321\202\321\214 \320\275\320\260 \320\262\321\213\321\205\320\276\320\264\320\265, \320\264\320\221\320\274", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWin", "\320\242\320\270\320\277 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", nullptr));
        cm_sparamet->setItemText(0, QCoreApplication::translate("MainWin", "S11", nullptr));
        cm_sparamet->setItemText(1, QCoreApplication::translate("MainWin", "S21", nullptr));
        cm_sparamet->setItemText(2, QCoreApplication::translate("MainWin", "S12", nullptr));
        cm_sparamet->setItemText(3, QCoreApplication::translate("MainWin", "S22", nullptr));

        pb_result->setText(QCoreApplication::translate("MainWin", "\320\230\320\267\320\274\320\265\321\200\320\270\321\202\321\214", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWin", "\320\244\320\260\320\271\320\273", nullptr));
        ac_help->setTitle(QCoreApplication::translate("MainWin", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWin: public Ui_MainWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H

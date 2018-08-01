/********************************************************************************
** Form generated from reading UI file 'MyMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMAINWINDOW_H
#define UI_MYMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "cradar.h"
#include "scene.h"

QT_BEGIN_NAMESPACE

class Ui_MyMainWindowClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_9;
    QFrame *line_4;
    QVBoxLayout *verticalLayout_3;
    QFrame *line_5;
    QGridLayout *gridLayout;
    QComboBox *comboBox_com;
    QLabel *label_25;
    QLabel *label_26;
    QComboBox *comboBox_baud;
    QLabel *label_27;
    QLabel *label_28;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_uart_rfresh;
    QPushButton *pushButton_uart_sw;
    QFrame *line;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_21;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *comboBox_prg;
    QComboBox *comboBox_ball;
    QComboBox *comboBox_place;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_ctrl_rst;
    QPushButton *pushButton_ctrl_cfm;
    QFrame *line_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_x;
    QLabel *label_2;
    QLineEdit *lineEdit_y;
    QLabel *label_4;
    QLineEdit *lineEdit_row;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_10;
    QLineEdit *lineEdit_Vx;
    QLabel *label_11;
    QLineEdit *lineEdit_Vy;
    QLabel *label_12;
    QLineEdit *lineEdit_Vw;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *lineEdit_V1;
    QLabel *label_6;
    QLineEdit *lineEdit_V2;
    QLabel *label_3;
    QLineEdit *lineEdit_V3;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_14;
    QLineEdit *lineEdit_pwm1;
    QLabel *label_15;
    QLineEdit *lineEdit_pwm2;
    QLabel *label_16;
    QLineEdit *lineEdit_pwm3;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_18;
    QLineEdit *lineEdit_m1;
    QLabel *label_19;
    QLineEdit *lineEdit_m2;
    QLabel *label_20;
    QLineEdit *lineEdit_m3;
    QFrame *line_6;
    QFrame *line_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_29;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox_com_radar;
    QLabel *label_32;
    QLabel *label_30;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *pushButton_uart_rfresh_r;
    QPushButton *pushButton_uart_sw_r;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_33;
    QLineEdit *lineEdit_radar_angle;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_34;
    QLineEdit *lineEdit_radar_d;
    CRadar *widget_radar;
    scene *playingGround;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyMainWindowClass)
    {
        if (MyMainWindowClass->objectName().isEmpty())
            MyMainWindowClass->setObjectName(QStringLiteral("MyMainWindowClass"));
        MyMainWindowClass->resize(1602, 742);
        centralWidget = new QWidget(MyMainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(420, 10, 411, 571));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        line_4 = new QFrame(layoutWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_9->addWidget(line_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        line_5 = new QFrame(layoutWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_5);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        comboBox_com = new QComboBox(layoutWidget);
        comboBox_com->setObjectName(QStringLiteral("comboBox_com"));

        gridLayout->addWidget(comboBox_com, 1, 1, 1, 1);

        label_25 = new QLabel(layoutWidget);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_25, 0, 0, 1, 2);

        label_26 = new QLabel(layoutWidget);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setMaximumSize(QSize(90, 16777215));

        gridLayout->addWidget(label_26, 1, 0, 1, 1);

        comboBox_baud = new QComboBox(layoutWidget);
        comboBox_baud->setObjectName(QStringLiteral("comboBox_baud"));

        gridLayout->addWidget(comboBox_baud, 2, 1, 1, 1);

        label_27 = new QLabel(layoutWidget);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout->addWidget(label_27, 2, 0, 1, 1);

        label_28 = new QLabel(layoutWidget);
        label_28->setObjectName(QStringLiteral("label_28"));

        gridLayout->addWidget(label_28, 3, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        pushButton_uart_rfresh = new QPushButton(layoutWidget);
        pushButton_uart_rfresh->setObjectName(QStringLiteral("pushButton_uart_rfresh"));

        horizontalLayout_10->addWidget(pushButton_uart_rfresh);

        pushButton_uart_sw = new QPushButton(layoutWidget);
        pushButton_uart_sw->setObjectName(QStringLiteral("pushButton_uart_sw"));

        horizontalLayout_10->addWidget(pushButton_uart_sw);


        gridLayout->addLayout(horizontalLayout_10, 3, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        line = new QFrame(layoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_21 = new QLabel(layoutWidget);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setMinimumSize(QSize(0, 25));
        label_21->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_21);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_22 = new QLabel(layoutWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_22);

        label_23 = new QLabel(layoutWidget);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_23);

        label_24 = new QLabel(layoutWidget);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_24);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        comboBox_prg = new QComboBox(layoutWidget);
        comboBox_prg->setObjectName(QStringLiteral("comboBox_prg"));

        horizontalLayout_7->addWidget(comboBox_prg);

        comboBox_ball = new QComboBox(layoutWidget);
        comboBox_ball->setObjectName(QStringLiteral("comboBox_ball"));

        horizontalLayout_7->addWidget(comboBox_ball);

        comboBox_place = new QComboBox(layoutWidget);
        comboBox_place->setObjectName(QStringLiteral("comboBox_place"));

        horizontalLayout_7->addWidget(comboBox_place);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        pushButton_ctrl_rst = new QPushButton(layoutWidget);
        pushButton_ctrl_rst->setObjectName(QStringLiteral("pushButton_ctrl_rst"));

        horizontalLayout_8->addWidget(pushButton_ctrl_rst);

        pushButton_ctrl_cfm = new QPushButton(layoutWidget);
        pushButton_ctrl_cfm->setObjectName(QStringLiteral("pushButton_ctrl_cfm"));

        horizontalLayout_8->addWidget(pushButton_ctrl_cfm);


        verticalLayout_2->addLayout(horizontalLayout_8);


        verticalLayout_3->addLayout(verticalLayout_2);

        line_2 = new QFrame(layoutWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(0, 25));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_8);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_x = new QLineEdit(layoutWidget);
        lineEdit_x->setObjectName(QStringLiteral("lineEdit_x"));

        horizontalLayout->addWidget(lineEdit_x);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_y = new QLineEdit(layoutWidget);
        lineEdit_y->setObjectName(QStringLiteral("lineEdit_y"));

        horizontalLayout->addWidget(lineEdit_y);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        lineEdit_row = new QLineEdit(layoutWidget);
        lineEdit_row->setObjectName(QStringLiteral("lineEdit_row"));

        horizontalLayout->addWidget(lineEdit_row);


        verticalLayout->addLayout(horizontalLayout);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_9);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_3->addWidget(label_10);

        lineEdit_Vx = new QLineEdit(layoutWidget);
        lineEdit_Vx->setObjectName(QStringLiteral("lineEdit_Vx"));

        horizontalLayout_3->addWidget(lineEdit_Vx);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_3->addWidget(label_11);

        lineEdit_Vy = new QLineEdit(layoutWidget);
        lineEdit_Vy->setObjectName(QStringLiteral("lineEdit_Vy"));

        horizontalLayout_3->addWidget(lineEdit_Vy);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_3->addWidget(label_12);

        lineEdit_Vw = new QLineEdit(layoutWidget);
        lineEdit_Vw->setObjectName(QStringLiteral("lineEdit_Vw"));

        horizontalLayout_3->addWidget(lineEdit_Vw);


        verticalLayout->addLayout(horizontalLayout_3);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        lineEdit_V1 = new QLineEdit(layoutWidget);
        lineEdit_V1->setObjectName(QStringLiteral("lineEdit_V1"));

        horizontalLayout_2->addWidget(lineEdit_V1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_2->addWidget(label_6);

        lineEdit_V2 = new QLineEdit(layoutWidget);
        lineEdit_V2->setObjectName(QStringLiteral("lineEdit_V2"));

        horizontalLayout_2->addWidget(lineEdit_V2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEdit_V3 = new QLineEdit(layoutWidget);
        lineEdit_V3->setObjectName(QStringLiteral("lineEdit_V3"));

        horizontalLayout_2->addWidget(lineEdit_V3);


        verticalLayout->addLayout(horizontalLayout_2);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_13);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_4->addWidget(label_14);

        lineEdit_pwm1 = new QLineEdit(layoutWidget);
        lineEdit_pwm1->setObjectName(QStringLiteral("lineEdit_pwm1"));

        horizontalLayout_4->addWidget(lineEdit_pwm1);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_4->addWidget(label_15);

        lineEdit_pwm2 = new QLineEdit(layoutWidget);
        lineEdit_pwm2->setObjectName(QStringLiteral("lineEdit_pwm2"));

        horizontalLayout_4->addWidget(lineEdit_pwm2);

        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_4->addWidget(label_16);

        lineEdit_pwm3 = new QLineEdit(layoutWidget);
        lineEdit_pwm3->setObjectName(QStringLiteral("lineEdit_pwm3"));

        horizontalLayout_4->addWidget(lineEdit_pwm3);


        verticalLayout->addLayout(horizontalLayout_4);

        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_17);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_18 = new QLabel(layoutWidget);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_5->addWidget(label_18);

        lineEdit_m1 = new QLineEdit(layoutWidget);
        lineEdit_m1->setObjectName(QStringLiteral("lineEdit_m1"));

        horizontalLayout_5->addWidget(lineEdit_m1);

        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_5->addWidget(label_19);

        lineEdit_m2 = new QLineEdit(layoutWidget);
        lineEdit_m2->setObjectName(QStringLiteral("lineEdit_m2"));

        horizontalLayout_5->addWidget(lineEdit_m2);

        label_20 = new QLabel(layoutWidget);
        label_20->setObjectName(QStringLiteral("label_20"));

        horizontalLayout_5->addWidget(label_20);

        lineEdit_m3 = new QLineEdit(layoutWidget);
        lineEdit_m3->setObjectName(QStringLiteral("lineEdit_m3"));

        horizontalLayout_5->addWidget(lineEdit_m3);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_3->addLayout(verticalLayout);

        line_6 = new QFrame(layoutWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_6);


        horizontalLayout_9->addLayout(verticalLayout_3);

        line_3 = new QFrame(layoutWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_9->addWidget(line_3);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 14, 352, 499));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_29 = new QLabel(layoutWidget1);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setMinimumSize(QSize(0, 30));
        label_29->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_29);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        comboBox_com_radar = new QComboBox(layoutWidget1);
        comboBox_com_radar->setObjectName(QStringLiteral("comboBox_com_radar"));

        gridLayout_2->addWidget(comboBox_com_radar, 1, 1, 1, 1);

        label_32 = new QLabel(layoutWidget1);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setMinimumSize(QSize(0, 25));

        gridLayout_2->addWidget(label_32, 2, 0, 1, 1);

        label_30 = new QLabel(layoutWidget1);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setMinimumSize(QSize(0, 25));
        label_30->setMaximumSize(QSize(90, 16777215));

        gridLayout_2->addWidget(label_30, 1, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        pushButton_uart_rfresh_r = new QPushButton(layoutWidget1);
        pushButton_uart_rfresh_r->setObjectName(QStringLiteral("pushButton_uart_rfresh_r"));

        horizontalLayout_13->addWidget(pushButton_uart_rfresh_r);

        pushButton_uart_sw_r = new QPushButton(layoutWidget1);
        pushButton_uart_sw_r->setObjectName(QStringLiteral("pushButton_uart_sw_r"));

        horizontalLayout_13->addWidget(pushButton_uart_sw_r);


        gridLayout_2->addLayout(horizontalLayout_13, 2, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(8);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_33 = new QLabel(layoutWidget1);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setMinimumSize(QSize(0, 30));

        horizontalLayout_12->addWidget(label_33);

        lineEdit_radar_angle = new QLineEdit(layoutWidget1);
        lineEdit_radar_angle->setObjectName(QStringLiteral("lineEdit_radar_angle"));

        horizontalLayout_12->addWidget(lineEdit_radar_angle);

        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_2);

        label_34 = new QLabel(layoutWidget1);
        label_34->setObjectName(QStringLiteral("label_34"));

        horizontalLayout_12->addWidget(label_34);

        lineEdit_radar_d = new QLineEdit(layoutWidget1);
        lineEdit_radar_d->setObjectName(QStringLiteral("lineEdit_radar_d"));

        horizontalLayout_12->addWidget(lineEdit_radar_d);


        verticalLayout_4->addLayout(horizontalLayout_12);

        widget_radar = new CRadar(layoutWidget1);
        widget_radar->setObjectName(QStringLiteral("widget_radar"));
        widget_radar->setMinimumSize(QSize(350, 350));
        widget_radar->setMaximumSize(QSize(350, 350));

        verticalLayout_4->addWidget(widget_radar);

        playingGround = new scene(centralWidget);
        playingGround->setObjectName(QStringLiteral("playingGround"));
        playingGround->setGeometry(QRect(830, 10, 725, 545));
        playingGround->setMinimumSize(QSize(725, 545));
        playingGround->setMaximumSize(QSize(725, 545));
        MyMainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyMainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1602, 26));
        MyMainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyMainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyMainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyMainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyMainWindowClass->setStatusBar(statusBar);

        retranslateUi(MyMainWindowClass);
        QObject::connect(pushButton_uart_sw, SIGNAL(clicked()), MyMainWindowClass, SLOT(UartSwitch()));

        QMetaObject::connectSlotsByName(MyMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyMainWindowClass)
    {
        MyMainWindowClass->setWindowTitle(QApplication::translate("MyMainWindowClass", "MyMainWindow", Q_NULLPTR));
        label_25->setText(QApplication::translate("MyMainWindowClass", "\344\270\262\345\217\243\351\200\232\350\256\257", Q_NULLPTR));
        label_26->setText(QApplication::translate("MyMainWindowClass", "\351\200\211\346\213\251", Q_NULLPTR));
        comboBox_baud->clear();
        comboBox_baud->insertItems(0, QStringList()
         << QApplication::translate("MyMainWindowClass", "115200", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "9600", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "38400", Q_NULLPTR)
        );
        label_27->setText(QApplication::translate("MyMainWindowClass", "\346\263\242\347\211\271\347\216\207", Q_NULLPTR));
        label_28->setText(QApplication::translate("MyMainWindowClass", "\346\223\215\344\275\234", Q_NULLPTR));
        pushButton_uart_rfresh->setText(QApplication::translate("MyMainWindowClass", "\345\210\267\346\226\260", Q_NULLPTR));
        pushButton_uart_sw->setText(QApplication::translate("MyMainWindowClass", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        label_21->setText(QApplication::translate("MyMainWindowClass", "\346\216\247\345\210\266", Q_NULLPTR));
        label_22->setText(QApplication::translate("MyMainWindowClass", "\347\250\213\345\272\217\351\200\211\346\213\251", Q_NULLPTR));
        label_23->setText(QApplication::translate("MyMainWindowClass", "\347\220\203", Q_NULLPTR));
        label_24->setText(QApplication::translate("MyMainWindowClass", "\345\234\272\345\234\260\351\200\211\346\213\251", Q_NULLPTR));
        comboBox_prg->clear();
        comboBox_prg->insertItems(0, QStringList()
         << QApplication::translate("MyMainWindowClass", "0\357\274\232\346\265\213\350\257\225", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "1\357\274\232\347\254\254\344\270\200\345\233\236\345\220\210", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "2\357\274\232\347\254\254\344\272\214\345\233\236\345\220\210", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "3\357\274\232\347\254\254\344\270\211\345\233\236\345\220\210", Q_NULLPTR)
        );
        comboBox_ball->clear();
        comboBox_ball->insertItems(0, QStringList()
         << QApplication::translate("MyMainWindowClass", "0", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "1", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "2", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "3", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "4", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "5", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "6", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "7", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "8", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "9", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "10", Q_NULLPTR)
        );
        comboBox_place->clear();
        comboBox_place->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MyMainWindowClass", "\345\267\246\345\234\272\345\234\260", Q_NULLPTR)
         << QApplication::translate("MyMainWindowClass", "\345\217\263\345\234\272\345\234\260", Q_NULLPTR)
        );
        pushButton_ctrl_rst->setText(QApplication::translate("MyMainWindowClass", "\351\207\215\347\275\256", Q_NULLPTR));
        pushButton_ctrl_cfm->setText(QApplication::translate("MyMainWindowClass", "\347\241\256\345\256\232", Q_NULLPTR));
        label_8->setText(QApplication::translate("MyMainWindowClass", "\345\247\277\346\200\201\344\277\241\346\201\257", Q_NULLPTR));
        label->setText(QApplication::translate("MyMainWindowClass", "X:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MyMainWindowClass", "Y:", Q_NULLPTR));
        label_4->setText(QApplication::translate("MyMainWindowClass", "ROW:", Q_NULLPTR));
        label_9->setText(QApplication::translate("MyMainWindowClass", "\346\234\272\345\231\250\344\272\272\351\200\237\345\272\246", Q_NULLPTR));
        label_10->setText(QApplication::translate("MyMainWindowClass", "Vx:", Q_NULLPTR));
        label_11->setText(QApplication::translate("MyMainWindowClass", "Vy:", Q_NULLPTR));
        label_12->setText(QApplication::translate("MyMainWindowClass", "Vw:", Q_NULLPTR));
        label_7->setText(QApplication::translate("MyMainWindowClass", "\344\270\273\345\212\250\350\275\256\351\200\237\345\272\246", Q_NULLPTR));
        label_5->setText(QApplication::translate("MyMainWindowClass", "V!:", Q_NULLPTR));
        label_6->setText(QApplication::translate("MyMainWindowClass", "V2:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MyMainWindowClass", "V3:", Q_NULLPTR));
        label_13->setText(QApplication::translate("MyMainWindowClass", "PWM\345\217\202\346\225\260", Q_NULLPTR));
        label_14->setText(QApplication::translate("MyMainWindowClass", "PWM1:", Q_NULLPTR));
        label_15->setText(QApplication::translate("MyMainWindowClass", "PWM2:", Q_NULLPTR));
        label_16->setText(QApplication::translate("MyMainWindowClass", "PWM3:", Q_NULLPTR));
        label_17->setText(QApplication::translate("MyMainWindowClass", "\351\207\214\347\250\213\350\256\241", Q_NULLPTR));
        label_18->setText(QApplication::translate("MyMainWindowClass", "A:", Q_NULLPTR));
        label_19->setText(QApplication::translate("MyMainWindowClass", "B:", Q_NULLPTR));
        label_20->setText(QApplication::translate("MyMainWindowClass", "C:", Q_NULLPTR));
        label_29->setText(QApplication::translate("MyMainWindowClass", "\351\233\267\350\276\276\344\270\262\345\217\243\351\200\211\346\213\251", Q_NULLPTR));
        label_32->setText(QApplication::translate("MyMainWindowClass", "\346\223\215\344\275\234", Q_NULLPTR));
        label_30->setText(QApplication::translate("MyMainWindowClass", "\351\200\211\346\213\251", Q_NULLPTR));
        pushButton_uart_rfresh_r->setText(QApplication::translate("MyMainWindowClass", "\345\210\267\346\226\260", Q_NULLPTR));
        pushButton_uart_sw_r->setText(QApplication::translate("MyMainWindowClass", "\345\274\200\345\247\213", Q_NULLPTR));
        label_33->setText(QApplication::translate("MyMainWindowClass", "\350\247\222\345\272\246\357\274\232", Q_NULLPTR));
        label_34->setText(QApplication::translate("MyMainWindowClass", "\350\267\235\347\246\273\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyMainWindowClass: public Ui_MyMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMAINWINDOW_H

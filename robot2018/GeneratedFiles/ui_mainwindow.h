/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *restartButton;
    QPushButton *leftGroundButton;
    QPushButton *rightGroundButton;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *portLineEdit;
    QPushButton *serverButton;
    QLineEdit *socketLineEditer;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QComboBox *baudRateComboBox;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QComboBox *dataBitsComboBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QComboBox *parityComboBox;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_6;
    QComboBox *stopBitsComboBox;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *comComboBox;
    QPushButton *comRefreshButton;
    QPushButton *comButton;
    QLineEdit *comLineEdit;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *xLineEdit;
    QLineEdit *yLineEdit;
    QLineEdit *thetaLineEdit;
    QPushButton *handPositionButton;
    QFrame *line_4;
    QPushButton *shotButton;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(733, 529);
        QIcon icon;
        icon.addFile(QStringLiteral("source/iconn.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        restartButton = new QPushButton(centralWidget);
        restartButton->setObjectName(QStringLiteral("restartButton"));

        verticalLayout->addWidget(restartButton);

        leftGroundButton = new QPushButton(centralWidget);
        leftGroundButton->setObjectName(QStringLiteral("leftGroundButton"));

        verticalLayout->addWidget(leftGroundButton);

        rightGroundButton = new QPushButton(centralWidget);
        rightGroundButton->setObjectName(QStringLiteral("rightGroundButton"));

        verticalLayout->addWidget(rightGroundButton);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);

        portLineEdit = new QLineEdit(centralWidget);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));

        horizontalLayout_6->addWidget(portLineEdit);

        serverButton = new QPushButton(centralWidget);
        serverButton->setObjectName(QStringLiteral("serverButton"));

        horizontalLayout_6->addWidget(serverButton);


        verticalLayout->addLayout(horizontalLayout_6);

        socketLineEditer = new QLineEdit(centralWidget);
        socketLineEditer->setObjectName(QStringLiteral("socketLineEditer"));

        verticalLayout->addWidget(socketLineEditer);

        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMaximumSize(QSize(50, 16777215));
        label_8->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_8);

        baudRateComboBox = new QComboBox(centralWidget);
        baudRateComboBox->addItem(QString());
        baudRateComboBox->addItem(QString());
        baudRateComboBox->addItem(QString());
        baudRateComboBox->addItem(QString());
        baudRateComboBox->addItem(QString());
        baudRateComboBox->addItem(QString());
        baudRateComboBox->addItem(QString());
        baudRateComboBox->addItem(QString());
        baudRateComboBox->setObjectName(QStringLiteral("baudRateComboBox"));

        horizontalLayout_2->addWidget(baudRateComboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(50, 16777215));
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_7);

        dataBitsComboBox = new QComboBox(centralWidget);
        dataBitsComboBox->addItem(QString());
        dataBitsComboBox->addItem(QString());
        dataBitsComboBox->addItem(QString());
        dataBitsComboBox->addItem(QString());
        dataBitsComboBox->setObjectName(QStringLiteral("dataBitsComboBox"));

        horizontalLayout_7->addWidget(dataBitsComboBox);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(50, 16777215));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label);

        parityComboBox = new QComboBox(centralWidget);
        parityComboBox->addItem(QString());
        parityComboBox->addItem(QString());
        parityComboBox->addItem(QString());
        parityComboBox->addItem(QString());
        parityComboBox->addItem(QString());
        parityComboBox->setObjectName(QStringLiteral("parityComboBox"));

        horizontalLayout_8->addWidget(parityComboBox);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMaximumSize(QSize(50, 16777215));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(label_6);

        stopBitsComboBox = new QComboBox(centralWidget);
        stopBitsComboBox->addItem(QString());
        stopBitsComboBox->addItem(QString());
        stopBitsComboBox->addItem(QString());
        stopBitsComboBox->setObjectName(QStringLiteral("stopBitsComboBox"));

        horizontalLayout_9->addWidget(stopBitsComboBox);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        comComboBox = new QComboBox(centralWidget);
        comComboBox->setObjectName(QStringLiteral("comComboBox"));

        horizontalLayout_5->addWidget(comComboBox);

        comRefreshButton = new QPushButton(centralWidget);
        comRefreshButton->setObjectName(QStringLiteral("comRefreshButton"));

        horizontalLayout_5->addWidget(comRefreshButton);


        verticalLayout->addLayout(horizontalLayout_5);

        comButton = new QPushButton(centralWidget);
        comButton->setObjectName(QStringLiteral("comButton"));

        verticalLayout->addWidget(comButton);

        comLineEdit = new QLineEdit(centralWidget);
        comLineEdit->setObjectName(QStringLiteral("comLineEdit"));

        verticalLayout->addWidget(comLineEdit);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_4);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        xLineEdit = new QLineEdit(centralWidget);
        xLineEdit->setObjectName(QStringLiteral("xLineEdit"));
        xLineEdit->setReadOnly(false);

        horizontalLayout_3->addWidget(xLineEdit);

        yLineEdit = new QLineEdit(centralWidget);
        yLineEdit->setObjectName(QStringLiteral("yLineEdit"));
        yLineEdit->setReadOnly(false);

        horizontalLayout_3->addWidget(yLineEdit);

        thetaLineEdit = new QLineEdit(centralWidget);
        thetaLineEdit->setObjectName(QStringLiteral("thetaLineEdit"));
        thetaLineEdit->setReadOnly(false);

        horizontalLayout_3->addWidget(thetaLineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        handPositionButton = new QPushButton(centralWidget);
        handPositionButton->setObjectName(QStringLiteral("handPositionButton"));

        verticalLayout->addWidget(handPositionButton);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        shotButton = new QPushButton(centralWidget);
        shotButton->setObjectName(QStringLiteral("shotButton"));

        verticalLayout->addWidget(shotButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        verticalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 733, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(action);
        menu->addAction(action_3);
        menu_2->addAction(action_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\216\247\345\210\266\347\263\273\347\273\237", nullptr));
        action->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        action_2->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        action_3->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256", nullptr));
        restartButton->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256", nullptr));
        leftGroundButton->setText(QApplication::translate("MainWindow", "\345\267\246\345\215\212\347\220\203\345\234\272", nullptr));
        rightGroundButton->setText(QApplication::translate("MainWindow", "\345\217\263\345\215\212\347\220\203\345\234\272", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Port", nullptr));
        serverButton->setText(QApplication::translate("MainWindow", "Server\346\211\223\345\274\200", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        baudRateComboBox->setItemText(0, QApplication::translate("MainWindow", "1200", nullptr));
        baudRateComboBox->setItemText(1, QApplication::translate("MainWindow", "2400", nullptr));
        baudRateComboBox->setItemText(2, QApplication::translate("MainWindow", "4800", nullptr));
        baudRateComboBox->setItemText(3, QApplication::translate("MainWindow", "9600", nullptr));
        baudRateComboBox->setItemText(4, QApplication::translate("MainWindow", "19200", nullptr));
        baudRateComboBox->setItemText(5, QApplication::translate("MainWindow", "38400", nullptr));
        baudRateComboBox->setItemText(6, QApplication::translate("MainWindow", "57600", nullptr));
        baudRateComboBox->setItemText(7, QApplication::translate("MainWindow", "115200", nullptr));

        baudRateComboBox->setCurrentText(QApplication::translate("MainWindow", "1200", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        dataBitsComboBox->setItemText(0, QApplication::translate("MainWindow", "5", nullptr));
        dataBitsComboBox->setItemText(1, QApplication::translate("MainWindow", "6", nullptr));
        dataBitsComboBox->setItemText(2, QApplication::translate("MainWindow", "7", nullptr));
        dataBitsComboBox->setItemText(3, QApplication::translate("MainWindow", "8", nullptr));

        dataBitsComboBox->setCurrentText(QApplication::translate("MainWindow", "5", nullptr));
        label->setText(QApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", nullptr));
        parityComboBox->setItemText(0, QApplication::translate("MainWindow", "No", nullptr));
        parityComboBox->setItemText(1, QApplication::translate("MainWindow", "Even", nullptr));
        parityComboBox->setItemText(2, QApplication::translate("MainWindow", "Odd", nullptr));
        parityComboBox->setItemText(3, QApplication::translate("MainWindow", "Space", nullptr));
        parityComboBox->setItemText(4, QApplication::translate("MainWindow", "Mark", nullptr));

        label_6->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        stopBitsComboBox->setItemText(0, QApplication::translate("MainWindow", "1", nullptr));
        stopBitsComboBox->setItemText(1, QApplication::translate("MainWindow", "1.5", nullptr));
        stopBitsComboBox->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));

        comRefreshButton->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        comButton->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\243\346\211\223\345\274\200", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "X\350\275\264", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Y\350\275\264", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Theta\350\247\222", nullptr));
        handPositionButton->setText(QApplication::translate("MainWindow", "\346\211\213\345\212\250\350\256\276\347\275\256", nullptr));
        shotButton->setText(QApplication::translate("MainWindow", "\345\274\271\345\260\204", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

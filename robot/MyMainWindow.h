#pragma once

#include <QtWidgets/QMainWindow>
#include <qserialport.h>
#include <qstring.h>
#include <qbytearray.h>
#include <qserialportinfo.h>
#include <qmessagebox.h>
#include <qtooltip.h>
#include <qdebug.h>
#include <qpainter.h>
#include <qbitmap.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <qthread.h>
#include "Receive.h"
#include "ui_MyMainWindow.h"
#include "radar.h"
#include "robot.h"

enum class UartState { ON, OFF };

class MyMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MyMainWindow(QWidget *parent = Q_NULLPTR);
	~MyMainWindow(void);

protected:
	void timerEvent(QTimerEvent *event);    //定时器事件
	

private slots:
    void on_pushButton_uart_sw_clicked();

    void on_pushButton_uart_rfresh_clicked();

    void on_comboBox_com_currentTextChanged(const QString &arg1);

    void on_pushButton_ctrl_rst_clicked();

    void on_pushButton_ctrl_cfm_clicked();

	//void Show();

	void robotDataUpdate();

	void stopThread();

    void on_pushButton_uart_rfresh_r_clicked();

    void on_pushButton_uart_sw_r_clicked();

signals:
	void startRadar(QString com);

	void stopRadar(void);

private:
	Ui::MyMainWindowClass ui;
	//地图显示
	QPixmap *pixmap;            
	QGraphicsScene *scene;
	QGraphicsView *view;

	//
	robot *bRobot;
	//串口接收和其线程
	UartState currentUartState = UartState::OFF;
	QSerialPort *currentSerialPort;
	Receive *uartReceive;
	QThread *receiveThread;

	//雷达及其串口
	UartState radarUartState = UartState::OFF;
	radar *robotRadar;
	QThread *radarThread;
	
	int showTimerId;
	
	void uartInit(void);

	void showMapInit();

	void showMapLeft();

	void showMapRight();

	void showRobotData();

	void uartSendCommand(char cmd,int pwm1 = 0, int pwm2 = 0, int pwm3 = 0);

	

};



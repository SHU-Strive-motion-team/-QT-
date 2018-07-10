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

class MyMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MyMainWindow(QWidget *parent = Q_NULLPTR);
	~MyMainWindow(void);
	

private slots:
    void on_pushButton_uart_sw_clicked();

    void on_pushButton_uart_rfresh_clicked();

    void on_comboBox_com_currentTextChanged(const QString &arg1);

    void on_pushButton_ctrl_rst_clicked();

    void on_pushButton_ctrl_cfm_clicked();

	void Show();

	void stopThread();

private:
	Ui::MyMainWindowClass ui;
	//地图显示
	QPixmap *pixmap;            
	QGraphicsScene *scene;
	QGraphicsView *view;
	//串口接收和其线程
	enum class UartState { ON, OFF } currentUartState;
	QSerialPort *currentSerialPort;
	Receive *uartReceive;
	QThread *receiveThread;

	void UartInit(void);

	void showMapInit();

	void showMapLeft();

	void showMapRight();

	void uartSendCommand(char cmd,int pwm1 = 0, int pwm2 = 0, int pwm3 = 0);
};

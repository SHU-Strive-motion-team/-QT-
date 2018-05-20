#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets>
#include <QMainWindow>
#include <QPainter>
#include <QDebug>
#include <QBitmap>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTimer>
#include "robotcontroller.h"
#include "robot2018.h"


namespace Ui {
	class MainWindow;
}

class QGraphicsScene;
class QGraphicsView;
class RobotController;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void paintEvent(QPaintEvent *);

	private slots:
	void on_restartButton_clicked();

	void on_leftGroundButton_clicked();

	void on_rightGroundButton_clicked();

	void on_handPositionButton_clicked();

	void on_serverButton_clicked();

	void ui_rplidarData();

	void on_comButton_clicked();

	void com_readData();

	void on_comRefreshButton_clicked();

	void on_shotButton_clicked();

	void timer_timeout();


private:
	void showMapLeft();

	void showMapRight();

	bool comCheckSum(unsigned char *data, int size);


	Ui::MainWindow *ui;
	QPixmap *pixmap;            //地图显示区域
	QGraphicsScene *scene;
	QGraphicsView *view;

	RobotController *controller;
	int mapType;                //场地类型，0-左半场，1-右半场

	QSerialPort *comPort;       //串口连接指针
	int comStat;

	QTimer * timer;

};



#endif // MAINWINDOW_H

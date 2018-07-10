#pragma once

#include <QObject>
#include <qserialport.h>
#include <qstring.h>
#include <qdebug.h>
#include <qthread.h>

class Receive : public QObject
{
	Q_OBJECT

public:
	Receive(QSerialPort* p);
	~Receive();

	void ReceiveUartData();

	bool isSuccess();
	bool isStart();
	QByteArray getData();


	enum RECTYPE
	{
		POSITION = 1,	//姿态信息
		VELOCITY,		//速度信息
		PWM,			//pwm信息
		ENCODER			//里程计信息
	}Type;

	

signals:
	void RecSuccess(void);

private:
	QSerialPort *receiveSerialPort;
	QByteArray Data;
	QByteArray originalData;
	bool Success = false;
	bool Start = false;
	char Sum = 0;

	//接收失败
	void receiveFail();
	//接收成功，发信号
	void receiveSuccessful(void);


};

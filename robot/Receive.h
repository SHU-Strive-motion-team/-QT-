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
	int *getData();


	enum RECTYPE
	{
		POSITION = 1,	//��̬��Ϣ
		VELOCITY,		//�ٶ���Ϣ
		PWM,			//pwm��Ϣ
		ENCODER			//��̼���Ϣ
	}Type;

	

signals:
	void RecSuccess(void);

private:
	QSerialPort * receiveSerialPort;
	int *Data = new int[3];
	QByteArray originalData;
	bool Success = false;
	bool Start = false;
	char Sum = 0;

	//����ʧ��
	void receiveFail();
	//���ճɹ������ź�
	void receiveSuccessful(void);


};

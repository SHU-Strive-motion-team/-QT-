#pragma once
#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QtNetwork>
#include <QByteArray>
#include <QString>

extern int socketStat; //socket����״̬ 0-δ������1-����
extern QByteArray lidar;
extern QByteArray shijue;


class Tcpserver : public QTcpServer
{
	Q_OBJECT

public:
	void getlisten() { this->listenConnection(); }





signals:
	void renew_ui();


	private slots:
	void listenConnection();

	void acceptConnection();

	void readClient();

	void readwriteClient();

	void sockSend();

private:

	QTcpSocket * rplidarConnection = NULL; //socket��tcp����ָ��
	QTcpSocket *shijueConnection = NULL;


};



#endif // TCPSOCKET_H

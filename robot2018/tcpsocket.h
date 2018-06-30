#pragma once
#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QtNetwork>
#include <QByteArray>
#include <QString>

extern int socketStat; //socketº‡Ã˝◊¥Ã¨ 0-Œ¥º‡Ã˝£¨1-º‡Ã˝
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

	QTcpSocket * rplidarConnection = NULL; //socketµƒtcp¡¨Ω”÷∏’Î
	QTcpSocket *shijueConnection = NULL;


};



#endif // TCPSOCKET_H

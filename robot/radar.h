#pragma once

#include <QObject>
#include <qdebug.h>
#include "rplidar.h"
#include "robot.h"
#include "cradar.h"

#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

#ifdef _WIN32
#include <Windows.h>
#define delay(x)   ::Sleep(x)
#endif

//注册参数类型
//qRegisterMetaType<QList<QPoint>>("QList<QPoint>");

using namespace rp::standalone::rplidar;

struct scanDot {
	_u8   quality;
	float angle;
	float dist;
};

class radar : public QObject
{
	Q_OBJECT

public:
	radar(robot *r,CRadar *w);
	~radar();

	void setCom(QString com);
	//停止雷达
	void setStop(bool v);





public slots:
	void startScan(QString com);

signals:
	//void completeScan(QList<QPoint> point);
	void reportError(QString _err);

private:

	bool checkRPLIDARHealth(RPlidarDriver * drv);

	void getNearest();
	
	bool stop = false;
	const char * opt_com_path = NULL;
	_u32         opt_com_baudrate = 115200;
	u_result     op_result;
	RPlidarDriver * drv;
	rplidar_response_measurement_node_t nodes[360 * 2];

	std::vector<scanDot> _scan_data;

	QList<QPoint> m_points;

	robot *Robot;

	CRadar *radarWidget;

	



};

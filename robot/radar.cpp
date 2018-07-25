#include "radar.h"
#include <stdio.h>
#include <stdlib.h>
#include <qthread.h>
#include <qmessagebox.h>
//#pragma comment(lib,"rplidar_driver")

#include <signal.h>
bool ctrl_c_pressed;
void ctrlc(int)
{
	ctrl_c_pressed = true;
}

//const float PI = (float)3.14159265;

radar::radar( robot *r, CRadar *w)
	: Robot(r),
	radarWidget(w)
{
	drv = RPlidarDriver::CreateDriver(RPlidarDriver::DRIVER_TYPE_SERIALPORT);
}

radar::~radar()
{
	RPlidarDriver::DisposeDriver(drv);
	Robot->deleteLater();
}

void radar::setCom(QString com)
{
	std::string tem;
	tem = com.toLower().toLatin1().toStdString();
	tem = "\\\\.\\" + tem;
	const char *_com = tem.c_str();
	qDebug() <<_com << endl;
	//"\\\\.\\com3"
	opt_com_path = tem.c_str();
	//opt_com_path = "\\\\.\\com5";
	
	qDebug() << opt_com_path << endl;
}

void radar::setStop(bool v)
{
	stop = v;
}


void radar::startScan(QString com)
{
	std::string tem;
	tem = com.toLower().toLatin1().toStdString();
	tem = "\\\\.\\" + tem;
	opt_com_path = tem.c_str();

	//opt_com_path = "\\\\.\\com5";
	//qDebug() << u8"雷达线程" << QThread::currentThread() << endl;

	if (!drv) 
	{
		/*fprintf(stderr, "insufficent memory, exit\n");
		exit(-2);*/

		qDebug() << "insufficent memory, exit\n";
		emit reportError("insufficent memory, exit");
		//QMessageBox::critical()
	}

	// make connection...
	if (IS_FAIL(drv->connect(opt_com_path, opt_com_baudrate))) 
	{
		//fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n"		, opt_com_path);
		qDebug() << "Error, cannot bind to the specified serial port " << opt_com_path << endl;
		emit reportError("Error, cannot bind to the specified serial port "+ com);

		RPlidarDriver::DisposeDriver(drv);
		drv = RPlidarDriver::CreateDriver(RPlidarDriver::DRIVER_TYPE_SERIALPORT);
		return;
	}


	// check health...
	if (!checkRPLIDARHealth(drv))
	{
		RPlidarDriver::DisposeDriver(drv);
		drv = RPlidarDriver::CreateDriver(RPlidarDriver::DRIVER_TYPE_SERIALPORT);
		return;
	}
		
	signal(SIGINT, ctrlc);

	drv->startMotor();
	// start scan...
	drv->startScan();

	// fetech result and print it out...
	while (false == stop) 
	{
		rplidar_response_measurement_node_t nodes[360 * 2];
		size_t   count = _countof(nodes);

		op_result = drv->grabScanData(nodes, count);

		if (IS_OK(op_result)) 
		{
			drv->ascendScanData(nodes, count);
			_scan_data.clear();
			for (int pos = 0; pos < (int)count; ++pos) 
			{
				scanDot dot;
				/*qDebug() << ((nodes[pos].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT) ? "S " : "  ")
					<< "theta:"<< (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f
					<<" Dist: "<< nodes[pos].distance_q2 / 4.0f
					<< "Q:" << (nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT) << endl;
				*/
				dot.quality = (nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);
				dot.angle = (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f;
				dot.dist = nodes[pos].distance_q2 / 4.0f;
				_scan_data.push_back(dot);
				
			}
			getNearest();
		}

		if (ctrl_c_pressed)
			break;
	}
	drv->stop();
	drv->stopMotor();
}

bool radar::checkRPLIDARHealth(RPlidarDriver * drv)
{
	u_result     op_result;
	rplidar_response_device_health_t healthinfo;

	op_result = drv->getHealth(healthinfo);
	if (IS_OK(op_result)) 
	{ // the macro IS_OK is the preperred way to judge whether the operation is succeed.
		//printf("RPLidar health status : %d\n", healthinfo.status);
		qDebug() << "RPLidar health status :" << healthinfo.status << endl;
		//emit reportError("RPLidar health status :"  + healthinfo.status);
		if (healthinfo.status == RPLIDAR_STATUS_ERROR) 
		{
			//fprintf(stderr, "Error, rplidar internal error detected. Please reboot the device to retry.\n");
			qDebug() << "Error, rplidar internal error detected. Please reboot the device to retry.\n";
			emit reportError("Error, rplidar internal error detected. Please reboot the device to retry.");
			// enable the following code if you want rplidar to be reboot by software
			// drv->reset();
			return false;
		}
		else 
			return true;
		
	}
	else 
	{
		//fprintf(stderr, "Error, cannot retrieve the lidar health code: %x\n", op_result);
		qDebug() << "Error, cannot retrieve the lidar health code:" << op_result << endl;
		emit reportError("Error, cannot retrieve the lidar health code: "+QString::number(op_result));
		return false;
	}
}

void radar::getNearest()
{
	float min_dep = 5000, min_ang = 0;							//最近点角度、距离（实际位置）
	float dep_pre = 5000, ang_pre = 240;						//前一个采样点角度、距离
	m_points.clear();
	for (int pos = 0; pos < (int)_scan_data.size(); ++pos)
	{
		float rad = (float)(_scan_data[pos].angle*PI / 180.0);

		if (rad < 5.23599f && rad>4.18879f)
		{
			if (_scan_data[pos].dist > 10)
			{
				//取最近点
				if (min_dep > _scan_data[pos].dist)
				{
					min_dep = _scan_data[pos].dist;
					min_ang = _scan_data[pos].angle;
				}	

			if (_scan_data[pos].dist < 1000)
			{
				int offsetX = 350 / 2 + cos(_scan_data[pos].angle*PI / 180.0)*_scan_data[pos].dist / 1000 * 350 / 2;
				int offsetY = 350 / 2 + sin(_scan_data[pos].angle*PI / 180.0)*_scan_data[pos].dist / 1000 * 350 / 2;
				m_points << QPoint(offsetX, offsetY);
			}				
		}	
	}
	Robot->setRadarData(min_ang, min_dep);
	Robot->sendCommand('r', min_ang, min_dep, 0);
	radarWidget->showUpdate(m_points);

	//emit completeScan(m_points);
}

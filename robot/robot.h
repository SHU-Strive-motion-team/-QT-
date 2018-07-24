#pragma once

#include <QObject>
#include <qserialport.h>
#include <qstring.h>
#include <qdebug.h>

//PD参数
typedef struct
{
	float Kp;
	float Kd;
}PD;
//铲球电机运行状态
typedef enum
{
	STOP = 0,
	UP,
	DOWM
}shovemotor;

class robot : public QObject
{
	Q_OBJECT

public:
	robot(QObject *parent, QSerialPort* p);
	~robot();

	void setPosion(float _x, float _y, float _yaw);
	void setRadarData(float _angle, float dist);
	void setVisionData(float _depth, float _x);
	void setRobotV(float _x, float _y, float _yaw);

	void sendCommand(char cmd, int pwm1 = 0, int pwm2 = 0, int pwm3 = 0);

	float X;		//机器人在坐标系中x坐标
	float Y;		//机器人在坐标系中y坐标
					//float x;		//机器人在坐标系中x坐标
					//float y;		//机器人在坐标系中y坐标
	float ThetaR;	//机器人正方向和y轴夹角 弧度
	float ThetaD;	//机器人正方向和y轴夹角 角度

	float Vx;		//机器人在坐标系x方向速度
	float Vy;		//机器人在坐标系y方向速度	
	float W;		//机器人角速度，顺时针正方向

	PD xPD;			//机器人在坐标系x方向 PD
	PD yPD;
	PD wPD;

	int w[3];		//编码器的实际计数
	int v[3];		//编码器所得速度

	int PWM[3];
	float Velocity[3];	//轮子的速度
	float LastTheta;	//上一时刻，机器人theta角
	float theta_offset;	//角度偏差矫正

						//接收雷达数据，极坐标
	struct RADAR
	{
		float Distance;  //距离

		float Angle;	//角度

		bool State;	//状态
	}Radar;

	//接收视觉数据
	struct VISION
	{
		float Depth;	//深度，纵轴

		float X;		//X位置，横轴

		bool State;	//状态
	}Vison;

private:
	QSerialPort *sendSerialPort;
	

};

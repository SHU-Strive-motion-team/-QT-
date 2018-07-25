#pragma once
#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <qserialport.h>
#include <qstring.h>
#include <qdebug.h>
//#include "control.h"

//class RobotController;

#define RADAR_MID 268	//雷达定位中心
#define VISION_MID 320	//视觉定位中心
#define DIS_RADAR 2500	//篮筐雷达定位距离
#define DIS_VISION 280	//篮筐视觉定位距离

#define PI 		3.141592654f

#define MOTOR_L 0.2013f		//轮到机器人中心的距离
#define MOTOR_R 0.0508f		//轮子的半径

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

	void uartSendCommand(char cmd, int pwm1 = 0, int pwm2 = 0, int pwm3 = 0);

	float X;		//机器人在坐标系中x坐标
	float Y;		//机器人在坐标系中y坐标
	float PX;		//点的x坐标
	float PY;		//点的y坐标
	float ThetaR;	//机器人正方向和y轴夹角 弧度
	float ThetaD;	//机器人正方向和y轴夹角 角度

	float Vx;		//机器人在坐标系x方向速度
	float Vy;		//机器人在坐标系y方向速度	
	float W;		//机器人角速度，顺时针正方向

	PD xPD;			//机器人在坐标系x方向 PD
	PD yPD;
	PD wPD;

	float w[3];		//编码器的实际计数
	float v[3];		//编码器所得速度

	int PWM[3];
	float Velocity[3];	//轮子的速度
	float LastTheta;	//上一时刻，机器人theta角
	float theta_offset;	//角度偏差矫正

	int Infr;		//红外状态

	void Velocity2PWM(float *V);		//电机速度转换成PWM数值，原理看电机驱动板手册
	float AdjustAngleV(float D_Theta);		//根据偏差大小调整角速度
	float AdjustVy(float D_Y);			//根据偏差大小调整Y轴速度
	float AdjustVx(float D_X);			//根据偏差大小调整X轴速度


	void Control_Init(void);	//机器人初始化
	void SetPWM(char cmd, float V1, float V2, float V3); 	//设置三个轮子PWM
	void GetMotorVelocity(float vx, float vy, float w);		//给定球场坐标速度求得轮子的速度
	void GetMotorVelocity_Self(float vx, float vy, float w);	//给自身坐标系速度求得轮子的速度
	void RobotRotate(float theta);		//自旋运动，根据误差角度，自动调节
	void RobotGoTo(float X_I, float Y_I, float Theta_I);		//行至指定坐标
	void RobotGoAvoidance(void);		//避障直行




	void FindBasketball(void);		//所找球为篮球
	void FindVolleyball(void);		//所找球为排球

	void FindBall_vision(unsigned char ball);		//视觉找球
	void FindBall_radar(void);						//雷达找球
	void FindBall_VandR(unsigned char ball);					//视觉雷达找球结合

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
	}Vision;

private:
	QSerialPort * sendSerialPort;

};

#endif	//ROBOT_H

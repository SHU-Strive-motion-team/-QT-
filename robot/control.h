#pragma once
#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QSerialPort>
#include "robot.h"
#define PI 3.141592654f
#define MOTOR_L 0.2013f
//extern char Data[7];
//robot BasketballRobot;


#define RADAR_MID 268	//雷达定位中心
#define VISION_MID 320	//视觉定位中心
#define DIS_RADAR 2500	//篮筐雷达定位距离
#define DIS_VISION 280	//篮筐视觉定位距离

class QGraphicsScene;
class QKeyEvent;


class ROBOT
{
public:
	float X;	//机器人在球场坐标系中的x坐标
	float Y;	//机器人在球场坐标系中的y坐标

	float ThetaR;	//机器人正方向和y轴夹角 弧度
	float ThetaD;	//机器人正方向和y轴夹角 角度

	float PX;		//临时点x坐标
	float PY;		//临时点y坐标

	float Vx;		//机器人在坐标系x方向速度
	float Vy;		//机器人在坐标系y方向速度	
	float W;		//机器人角速度，顺时针正方向

	float w[3];		//编码器的实际计数
	float v[3];		//编码器所得速度

	float Velocity[3];	//轮子的速度
	float LastTheta;	//上一时刻，机器人theta角
	float theta_offset;	//角度偏差矫正

	int Infr;		//红外状态

};

class RADAR
{
public:
	uint32_t Distance;  //距离

	uint32_t Angle;	//角度

	unsigned char State;	//状态
};

class VISION
{
public:
	uint32_t Depth;	//深度，纵轴

	uint32_t X;		//X位置，横轴

	unsigned char State;	//状态
};

extern ROBOT Robot;
extern RADAR Radar;
extern VISION Vision;

//void MyMainWindow::Control_Init(void);	//机器人初始化
static void Velocity2PWM(float *V);		//电机速度转换成PWM数值，原理看电机驱动板手册
//void SetPWM(float V1, float V2, float V3); 	//设置三个轮子PWM

//void GetMotorVelocity(float vx, float vy, float w);		//给定球场坐标速度求得轮子的速度
//void GetMotorVelocity_Self(float vx, float vy, float w);	//给自身坐标系速度求得轮子的速度

static float AdjustAngleV(float D_Theta);		//根据偏差大小调整角速度
static float AdjustVy(float D_Y);			//根据偏差大小调整Y轴速度
static float AdjustVx(float D_X);			//根据偏差大小调整X轴速度


//void RobotRotate(float theta);	//自旋运动，根据误差角度，自动调节

//void RobotGoTo(float X_I, float Y_I, float Theta_I);	//行至指定坐标

//void RobotGoAvoidance(void);	//避障直行

//void GetRadarData();			//转换雷达数据
//void GetVisionData();			//转换视觉数据






#endif // CONTROL_H

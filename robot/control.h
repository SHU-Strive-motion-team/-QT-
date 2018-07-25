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


#define RADAR_MID 268	//�״ﶨλ����
#define VISION_MID 320	//�Ӿ���λ����
#define DIS_RADAR 2500	//�����״ﶨλ����
#define DIS_VISION 280	//�����Ӿ���λ����

class QGraphicsScene;
class QKeyEvent;


class ROBOT
{
public:
	float X;	//��������������ϵ�е�x����
	float Y;	//��������������ϵ�е�y����

	float ThetaR;	//�������������y��н� ����
	float ThetaD;	//�������������y��н� �Ƕ�

	float PX;		//��ʱ��x����
	float PY;		//��ʱ��y����

	float Vx;		//������������ϵx�����ٶ�
	float Vy;		//������������ϵy�����ٶ�	
	float W;		//�����˽��ٶȣ�˳ʱ��������

	float w[3];		//��������ʵ�ʼ���
	float v[3];		//�����������ٶ�

	float Velocity[3];	//���ӵ��ٶ�
	float LastTheta;	//��һʱ�̣�������theta��
	float theta_offset;	//�Ƕ�ƫ�����

	int Infr;		//����״̬

};

class RADAR
{
public:
	uint32_t Distance;  //����

	uint32_t Angle;	//�Ƕ�

	unsigned char State;	//״̬
};

class VISION
{
public:
	uint32_t Depth;	//��ȣ�����

	uint32_t X;		//Xλ�ã�����

	unsigned char State;	//״̬
};

extern ROBOT Robot;
extern RADAR Radar;
extern VISION Vision;

//void MyMainWindow::Control_Init(void);	//�����˳�ʼ��
static void Velocity2PWM(float *V);		//����ٶ�ת����PWM��ֵ��ԭ������������ֲ�
//void SetPWM(float V1, float V2, float V3); 	//������������PWM

//void GetMotorVelocity(float vx, float vy, float w);		//�����������ٶ�������ӵ��ٶ�
//void GetMotorVelocity_Self(float vx, float vy, float w);	//����������ϵ�ٶ�������ӵ��ٶ�

static float AdjustAngleV(float D_Theta);		//����ƫ���С�������ٶ�
static float AdjustVy(float D_Y);			//����ƫ���С����Y���ٶ�
static float AdjustVx(float D_X);			//����ƫ���С����X���ٶ�


//void RobotRotate(float theta);	//�����˶����������Ƕȣ��Զ�����

//void RobotGoTo(float X_I, float Y_I, float Theta_I);	//����ָ������

//void RobotGoAvoidance(void);	//����ֱ��

//void GetRadarData();			//ת���״�����
//void GetVisionData();			//ת���Ӿ�����






#endif // CONTROL_H

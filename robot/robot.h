#pragma once
#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <qserialport.h>
#include <qstring.h>
#include <qdebug.h>
//#include "control.h"

//class RobotController;

#define RADAR_MID 268	//�״ﶨλ����
#define VISION_MID 320	//�Ӿ���λ����
#define DIS_RADAR 2500	//�����״ﶨλ����
#define DIS_VISION 280	//�����Ӿ���λ����

#define PI 		3.141592654f

#define MOTOR_L 0.2013f		//�ֵ����������ĵľ���
#define MOTOR_R 0.0508f		//���ӵİ뾶

//PD����
typedef struct
{
	float Kp;
	float Kd;
}PD;
//����������״̬
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

	float X;		//������������ϵ��x����
	float Y;		//������������ϵ��y����
	float PX;		//���x����
	float PY;		//���y����
	float ThetaR;	//�������������y��н� ����
	float ThetaD;	//�������������y��н� �Ƕ�

	float Vx;		//������������ϵx�����ٶ�
	float Vy;		//������������ϵy�����ٶ�	
	float W;		//�����˽��ٶȣ�˳ʱ��������

	PD xPD;			//������������ϵx���� PD
	PD yPD;
	PD wPD;

	float w[3];		//��������ʵ�ʼ���
	float v[3];		//�����������ٶ�

	int PWM[3];
	float Velocity[3];	//���ӵ��ٶ�
	float LastTheta;	//��һʱ�̣�������theta��
	float theta_offset;	//�Ƕ�ƫ�����

	int Infr;		//����״̬

	void Velocity2PWM(float *V);		//����ٶ�ת����PWM��ֵ��ԭ������������ֲ�
	float AdjustAngleV(float D_Theta);		//����ƫ���С�������ٶ�
	float AdjustVy(float D_Y);			//����ƫ���С����Y���ٶ�
	float AdjustVx(float D_X);			//����ƫ���С����X���ٶ�


	void Control_Init(void);	//�����˳�ʼ��
	void SetPWM(char cmd, float V1, float V2, float V3); 	//������������PWM
	void GetMotorVelocity(float vx, float vy, float w);		//�����������ٶ�������ӵ��ٶ�
	void GetMotorVelocity_Self(float vx, float vy, float w);	//����������ϵ�ٶ�������ӵ��ٶ�
	void RobotRotate(float theta);		//�����˶����������Ƕȣ��Զ�����
	void RobotGoTo(float X_I, float Y_I, float Theta_I);		//����ָ������
	void RobotGoAvoidance(void);		//����ֱ��




	void FindBasketball(void);		//������Ϊ����
	void FindVolleyball(void);		//������Ϊ����

	void FindBall_vision(unsigned char ball);		//�Ӿ�����
	void FindBall_radar(void);						//�״�����
	void FindBall_VandR(unsigned char ball);					//�Ӿ��״�������

	struct RADAR
	{
		float Distance;  //����

		float Angle;	//�Ƕ�

		bool State;	//״̬
	}Radar;

	//�����Ӿ�����
	struct VISION
	{
		float Depth;	//��ȣ�����

		float X;		//Xλ�ã�����

		bool State;	//״̬
	}Vision;

private:
	QSerialPort * sendSerialPort;

};

#endif	//ROBOT_H

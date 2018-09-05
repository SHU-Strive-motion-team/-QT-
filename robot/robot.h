#pragma once

#include <QObject>
#include <qserialport.h>
#include <qstring.h>
#include <qdebug.h>

#define RADAR_MID 268	//�״ﶨλ����
#define VISION_MID 320	//�Ӿ���λ����
#define DIS_RADAR 2500	//�����״ﶨλ����
#define DIS_VISION 280	//�����Ӿ���λ����

#define MOTOR_L 1//0.2013f		//�ֵ����������ĵľ���
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
	robot();
	~robot();

	void setPosion(float _x, float _y, float _yaw);
	void setRadarData(float _angle, float dist);
	void setVisionData(float _depth, float _x);
	void setRobotV(float _x, float _y, float _yaw);

	void Control_Init(void);	//�����˳�ʼ��

	void Velocity2PWM(float *V);		//����ٶ�ת����PWM��ֵ��ԭ������������ֲ�

	float AdjustAngleV(float D_Theta);		//����ƫ���С�������ٶ�

	float AdjustVy(float D_Y);			//����ƫ���С����Y���ٶ�

	float AdjustVx(float D_X);			//����ƫ���С����X���ٶ�

	void SetPWM(char cmd, float V1, float V2, float V3); 	//������������PWM
	//void SetPWM(char cmd); 	//������������PWM

	void GetMotorVelocity(float vx, float vy, float w);		//�����������ٶ�������ӵ��ٶ�

	void GetMotorVelocity_Self(float vx, float vy, float w);	//����������ϵ�ٶ�������ӵ��ٶ�

	void RobotRotate(float theta);		//�����˶����������Ƕȣ��Զ�����

	void RobotGoTo(float X_I, float Y_I, float Theta_I);		//����ָ������

	void RobotGoAvoidance(void);		//����ֱ��

	//void sendCommand(char cmd, int pwm1 = 0, int pwm2 = 0, int pwm3 = 0);

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

	int w[3];		//��������ʵ�ʼ���
	int v[3];		//�����������ٶ�

	int PWM[3];
	float Velocity[3];	//���ӵ��ٶ�
	float LastTheta;	//��һʱ�̣�������theta��
	float theta_offset;	//�Ƕ�ƫ�����

						//�����״����ݣ�������
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

signals:
	void sendCommend(char cmd, int d1, int d2, int d3);

private:
	

};

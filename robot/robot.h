#pragma once

#include <QObject>
#include <qserialport.h>
#include <qstring.h>
#include <qdebug.h>

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

	void sendCommand(char cmd, int pwm1 = 0, int pwm2 = 0, int pwm3 = 0);

	float X;		//������������ϵ��x����
	float Y;		//������������ϵ��y����
					//float x;		//������������ϵ��x����
					//float y;		//������������ϵ��y����
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
	}Vison;

private:
	QSerialPort *sendSerialPort;
	

};

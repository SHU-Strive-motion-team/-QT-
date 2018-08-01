#include "robot.h"

robot::robot()
{

}

robot::~robot()
{
	//sendSerialPort->deleteLater();
}

void robot::setPosion(float _x, float _y, float _yaw)
{
	X = _x;
	Y = _y;
	ThetaD = _yaw;
}

void robot::setRadarData(float _angle, float dist)
{
	Radar.Angle = _angle;
	Radar.Distance = dist;
	Radar.State = true;

	//sendCommand('r', Radar.Angle, Radar.Angle, 0);
}

void robot::setVisionData(float _depth, float _x)
{
	Vision.Depth = _depth;
	Vision.X = _x;
	Vision.State = true;
}

void robot::setRobotV(float _x, float _y, float _yaw)
{
	Vx = _x;
	Vy = _y;
	W = _yaw;
}

void robot::Control_Init(void)
{
	X = 0;		//������������ϵ��x����
	Y = 0;		//������������ϵ��y����
	ThetaD = 0;		//��������������y��н� �Ƕ�
	ThetaR = 0;		//��������������y��н� ����
					//	Robot.PX = 0;			//��ʱ��x����
					//	Robot.PY = 0;			//��ʱ��y����
	Vx = 0;		//������������ϵ��x�����ٶ�
	Vy = 0;		//������������ϵ��y�����ٶ�
	W = 0;		//�����˽��ٶȣ�˳ʱ��Ϊ������

	w[1] = 0;		//��һ��������ʵ�ʼ���
	w[2] = 0;		//�ڶ���������ʵ�ʼ���
	w[0] = 0;		//������������ʵ�ʼ���

	v[1] = 0;		//��һ�������������ٶ�
	v[2] = 0;		//�ڶ��������������ٶ�
	v[0] = 0;		//�����������������ٶ�

	LastTheta = 0;	//��һʱ�̻�����theta��
	theta_offset = 0;		//�Ƕ�ƫ�����

							//�״��������
	Radar.Distance = 0;
	Radar.Angle = 0;
	Radar.State = false;

	//�Ӿ��������
	Vision.Depth = 0;
	Vision.X = 0;
	Vision.State = false;
}

 void robot::Velocity2PWM(float *V)
{
	*V += 1000;//*V = 1000 - *V;
	if (*V >= 1900)
		*V = 1900;
	if (*V <= 100)
		*V = 100;
}

float robot::AdjustAngleV(float D_Theta)
{
	return 0.0f;
}

float robot::AdjustVy(float D_Y)
{
	return 0.0f;
}

float robot::AdjustVx(float D_X)
{
	return 0.0f;
}

void robot::SetPWM(char cmd, float V1, float V2, float V3)
{
	Velocity[0] = V1;
	Velocity[1] = V2;
	Velocity[2] = V3;

	//ת��
	Velocity2PWM(&V1);
	Velocity2PWM(&V2);
	Velocity2PWM(&V3);

	PWM[0] = V1;
	PWM[1] = V2;
	PWM[2] = V3;

	emit sendCommend(cmd,V1,V2,V3);
}

void robot::GetMotorVelocity(float vx, float vy, float w)
{
	unsigned char i, j, k;
	float L[3][3];
	float theta[3][3];
	float V[3];
	float tem[3][3];

	//v(PWM)=L*Theta*V
	//   cos(60)	sin(60)	-MOTOR_L
	//L= cos(180) 	sin(180)	-MOTOR_L
	//   cos(-60)	sin(-60)	-MOTOR_L
	L[0][0] = 0.5;					L[0][1] = 0.8660254037844386;		L[0][2] = -MOTOR_L;
	L[1][0] = -1;					L[1][1] = 0;						L[1][2] = -MOTOR_L;
	L[2][0] = 0.5;					L[2][1] = -0.8660254037844386;		L[2][2] = -MOTOR_L;
	//		cos(theta)	sin(theta)	0
	//theta= -sin(theta)	cos(theta) 	0
	//		 	0			0		1
	theta[0][0] = cos(ThetaR);		theta[0][1] = sin(ThetaR);			theta[0][2] = 0;
	theta[1][0] = -theta[0][1];		theta[1][1] = theta[0][0];			theta[1][2] = 0;
	theta[2][0] = 0;				theta[2][1] = 0;					theta[2][2] = 1;
	//V
	V[0] = -vx * 10;
	V[1] = -vy;
	V[2] = -w;

	for (i = 0; i<3; i++)
	{
		for (j = 0; j<3; j++)
		{
			tem[i][j] = 0;
			for (k = 0; k<3; k++)
				tem[i][j] += L[i][k] * theta[k][j];
		}
	}

	for (i = 0; i<3; i++)
	{
		Velocity[i] = 0;
		for (j = 0; j<3; j++)
			Velocity[i] += tem[i][j] * V[j];
	}
}

//������������ϵ�ٶ�������ӵ��ٶ�
//��ʾ�ڽ�����
void robot::GetMotorVelocity_Self(float vx, float vy, float w)
{
	unsigned i, j;
	float L[3][3];
	float V[3];

	//v(PWM)=L*Theta*V
	//   cos(60)	sin(60)	-MOTOR_L
	//L= cos(180) 	sin(180)	-MOTOR_L
	//   cos(-60)	sin(-60)	-MOTOR_L
	L[0][0] = 0.5;					L[0][1] = 0.8660254037844386;		L[0][2] = -MOTOR_L;
	L[1][0] = -1;						L[1][1] = 0;						L[1][2] = -MOTOR_L;
	L[2][0] = 0.5;					L[2][1] = -0.8660254037844386;		L[2][2] = -MOTOR_L;

	//V
	V[0] = -vx * 10;
	V[1] = -vy;
	V[2] = -w;


	for (i = 0; i<3; i++)
	{
		Velocity[i] = 0;
		for (j = 0; j<3; j++)
			Velocity[i] += L[i][j] * V[j];
	}
}

void robot::RobotRotate(float theta)
{
	float D_Theta;
	float Vw = 0;        //W����0 ��ʱ��

						 //D_Theta = theta-BasketballRobot.ThetaD;
	D_Theta = theta - 0;
	Vw = AdjustAngleV(D_Theta);


	while (D_Theta>1 || D_Theta < -1)
	{
		GetMotorVelocity(0, 0, Vw);

		SetPWM('Z', Velocity[0], Velocity[1], Velocity[2]);

		D_Theta = theta - ThetaD;

		Vw = AdjustAngleV(D_Theta);
	}

	SetPWM('S', 0, 0, 0);

	while (W);
}

void robot::RobotGoTo(float X_I, float Y_I, float Theta_I)
{
	float D_Theta, D_X, D_Y, Vw = 0, sx, sy = 0;

	D_Theta = Theta_I - ThetaD;	//�ǶȲ�
	D_X = X_I - X;
	D_Y = Y_I - Y;

	while (fabs(D_Y) > 0.05f || fabs(D_X) > 0.05f)
	{
		sy = AdjustVy(D_Y);

		sx = AdjustVx(D_X);

		Vw = AdjustAngleV(D_Theta) / 2;

		GetMotorVelocity(sx * 12, sy * 100, Vw);

		SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);

		D_Theta = Theta_I - ThetaD;
		D_X = X_I - X;
		D_Y = Y_I - Y;
	}

	SetPWM('S', 0, 0, 0);

	//��ʱ
	//uartSendCommand('D', 1000, 0, 0);

	RobotRotate(Theta_I);
}

void robot::RobotGoAvoidance(void)
{
}

/*��λ������λ������Э�飨����Ϊ��������PWM��
*	��ʼ1	��ʼ2	������	����1	����1	����2	����2	����3	����3	У���
*	@(0x40) ^(0x5E)	cmd		H1		L2		H2		L2		H3		L3		sum
* SUM = 0x40 + 0x5E + cmd + H1 + L1 + H2 + L2 + H3 + L3
*  cod:
*		r �״�
*		v pwm��
*/
//void robot::sendCommand(char cmd, int pwm1, int pwm2, int pwm3)
//{
//	char sendData[10];
//	sendData[0] = '@';
//	sendData[1] = '^';
//	sendData[2] = cmd;
//	sendData[3] = (pwm1 >> 8) & 0xff;
//	sendData[4] = pwm1 & 0xff;
//	sendData[5] = (pwm2 >> 8) & 0xff;
//	sendData[6] = pwm2 & 0xff;
//	sendData[7] = (pwm2 >> 8) & 0xff;
//	sendData[8] = pwm3 & 0xff;
//	sendData[9] = 0;
//	for (int i = 0; i < 9; i++)
//		sendData[9] += sendData[i];
//	qDebug() << int(sendData[9]) << endl;
//
//	sendSerialPort->write(sendData, 10);
//
//	//parent
//}


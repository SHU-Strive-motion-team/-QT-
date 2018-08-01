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
	X = 0;		//机器人在坐标系中x坐标
	Y = 0;		//机器人在坐标系中y坐标
	ThetaD = 0;		//机器人正方向与y轴夹角 角度
	ThetaR = 0;		//机器人正方向与y轴夹角 弧度
					//	Robot.PX = 0;			//临时点x坐标
					//	Robot.PY = 0;			//临时点y坐标
	Vx = 0;		//机器人在坐标系中x方向速度
	Vy = 0;		//机器人在坐标系中y方向速度
	W = 0;		//机器人角速度，顺时针为正方向

	w[1] = 0;		//第一个编码器实际计数
	w[2] = 0;		//第二个编码器实际计数
	w[0] = 0;		//第三个编码器实际计数

	v[1] = 0;		//第一个编码器所得速度
	v[2] = 0;		//第二个编码器所得速度
	v[0] = 0;		//第三个编码器所得速度

	LastTheta = 0;	//上一时刻机器人theta角
	theta_offset = 0;		//角度偏差矫正

							//雷达数据清空
	Radar.Distance = 0;
	Radar.Angle = 0;
	Radar.State = false;

	//视觉数据清空
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

	//转换
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

//给定自身坐标系速度求得轮子的速度
//显示在界面上
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
	float Vw = 0;        //W大于0 逆时针

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

	D_Theta = Theta_I - ThetaD;	//角度差
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

	//延时
	//uartSendCommand('D', 1000, 0, 0);

	RobotRotate(Theta_I);
}

void robot::RobotGoAvoidance(void)
{
}

/*上位机给下位机发送协议（数据为三个轮子PWM）
*	开始1	开始2	控制字	数据1	数据1	数据2	数据2	数据3	数据3	校验和
*	@(0x40) ^(0x5E)	cmd		H1		L2		H2		L2		H3		L3		sum
* SUM = 0x40 + 0x5E + cmd + H1 + L1 + H2 + L2 + H3 + L3
*  cod:
*		r 雷达
*		v pwm波
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


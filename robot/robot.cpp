#include <QtMath>
#include <signal.h>
#include "robot.h"

int findballtime;		//找球时调整角度的次数


robot::robot(QSerialPort* p)
	:sendSerialPort(p)

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

//	sendCommand('r', Radar.Angle, Radar.Angle, 0);
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

/*上位机给下位机发送协议（数据为三个轮子PWM）
*	开始1	开始2	控制字	数据1	数据1	数据2	数据2	数据3	数据3	校验和
*	@(0x40) ^(0x5E)	cmd		H1		L2		H2		L2		H3		L3		sum
* SUM = 0x40 + 0x5E + cmd + H1 + L1 + H2 + L2 + H3 + L3
*  cod:
*		r 雷达
*		v pwm波
*/
void robot::sendCommand(char cmd, int pwm1, int pwm2, int pwm3)
{
	char sendData[10];
	sendData[0] = '@';
	sendData[1] = '^';
	sendData[2] = cmd;
	sendData[3] = (pwm1 >> 8) & 0xff;
	sendData[4] = pwm1 & 0xff;
	sendData[5] = (pwm2 >> 8) & 0xff;
	sendData[6] = pwm2 & 0xff;
	sendData[7] = (pwm2 >> 8) & 0xff;
	sendData[8] = pwm3 & 0xff;
	sendData[9] = 0;
	for (int i = 0; i < 9; i++)
		sendData[9] += sendData[i];
	qDebug() << int(sendData[9]) << endl;

	sendSerialPort->write(sendData, 10);

	//parent
}

//机器人初始化函数
//在界面上显示相应信息
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

	//视觉数据清空
	Vision.Depth = 0;
	Vision.X = 0;

		

}

//根据偏差大小调整角速度
float robot::AdjustAngleV(float D_Theta)
{
	float Vw = 0;

	//大于30°线性控制
	if (D_Theta>0 && (D_Theta<180))
	{
		Vw = D_Theta;
	}
	else if (D_Theta>0 && (D_Theta >= 180))
	{
		D_Theta = 360 - D_Theta;
		Vw = -D_Theta;
	}
	else if (D_Theta<0 && (D_Theta >= -180))
	{
		D_Theta = -D_Theta;
		Vw = -D_Theta;
	}
	else if (D_Theta<0 && (D_Theta<-180))
	{
		D_Theta = 360 + D_Theta;
		Vw = D_Theta;
	}
	else
		//Vw=Vw;

		//小于60°大于30°匀速
		//实际PWM为100
		if (D_Theta < 60)
		{
			if (Vw>0)
				Vw = 1000;
			else
				Vw = -1000;
		}

	//小于30°大于5°
	if (D_Theta < 30)
	{
		if (Vw>30)
			Vw = 200;
		else
			Vw = -200;
	}
	//小于5°
	if (D_Theta < 5)
	{
		if (Vw>0)
			Vw = 40;
		else
			Vw = -40;
	}
	if (D_Theta == 0)
		Vw = 0;

	return Vw;
}

//根据偏差大小调整Y轴速度
float robot::AdjustVy(float D_Y)
{
	float sy;

	if (D_Y > 0.05f)
	{

		if (D_Y >= 1.5f)
		{
			sy = 8;
			if (Vy < 0.3f)
				sy = 2;
			else if (Vy < 0.5f)
				sy = 4;
			else if (Vy < 0.9f)
				sy = 6;
		}
		if (D_Y < 1.5f&&D_Y > 0.2f)
			sy = D_Y * 10 / 2;

		if (D_Y < 0.2f)
			sy = 0.25;
	}
	else if (D_Y < -0.05f)
	{
		if (D_Y < -1.5f)
		{
			sy = -8;
			if (Vy > -0.3f)
				sy = -2;
			else if (Vy > -0.5f)
				sy = -4;
			else if (Vy > -0.9f)
				sy = -6;
		}

		if (D_Y > -1.5f&&D_Y < -0.2f)
			sy = D_Y * 10 / 2;

		if (D_Y > -0.2f)
			sy = -0.25;
	}
	else
		sy = 0;

	return sy;

}

//根据偏差大小调整X轴速度
float robot::AdjustVx(float D_X)
{
	float sx;

	if (D_X > 0.05f)
	{
		if (D_X > 1.5f)
		{
			sx = 8;
			if (Vx < 0.1f)
				sx = 0.5;
			else if (Vx < 0.2f)
				sx = 1;
			else if (Vx < 0.4f)
				sx = 2;
			else if (Vx < 0.58f)
				sx = 4;
			else if (Vx < 7.5f)
				sx = 6;
		}
		else if (D_X < 1.5f)
		{
			if (D_X > 0.2f)
				sx = 2;

			else if (D_X > 0.15f)
				sx = 1;

			else if (D_X > 0.1f)
				sx = 0.5f;

			else
				sx = 0.25f;
		}
	}
	else if (D_X < -0.05f)
	{
		if (D_X < -1.5f)
		{
			sx = -8;
			if (Vx > -0.1f)
				sx = -0.5;
			else if (Vx > -0.2f)
				sx = -1;
			else if (Vx > -0.4f)
				sx = -2;
			else if (Vx > -0.58f)
				sx = -4;
			else if (Vx > -7.5f)
				sx = -6;
		}
		else if (D_X > -1.5f)
		{
			if (D_X < -0.2f)
				sx = -2;

			else if (D_X < -0.15f)
				sx = -1;

			else if (D_X < -0.1f)
				sx = -0.5f;
			else
				sx = -0.25f;
		}
	}
	else
		sx = 0;

	return sx;

}

/*电机速度转换成PWM数值*/
 void robot::Velocity2PWM(float *V)
{
	*V = 1000 - *V;//*V+=1000;
	if (*V >= 1900)
		*V = 1900;
	if (*V <= 100)
		*V = 100;
}

//设置三个轮子PWM并发送给下位机，同时显示在界面上
//cmd:	控制字	R：复位重启					O:正常走点					F：找球			
//				Y：找到球，放铲铲球			N：球不见，升铲				Z：自旋运动		
//				S：停止动，三个pwm值都为0；	D：延时						A：避障
//V1:	电机1速度
//V2:	电机2速度
//V3;	电机3速度
void robot::SetPWM(char cmd, float V1, float V2, float V3)
{
	Velocity[0] = V1;
	Velocity[1] = V2;
	Velocity[2] = V3;

	//转换
	Velocity2PWM(&V1);
	Velocity2PWM(&V2);
	Velocity2PWM(&V3);

	////将float型转换成QString类型
	//QString data1 = QString("%1").arg(V1);
	//QString data2 = QString("%1").arg(V2);
	//QString data3 = QString("%1").arg(V3);

	////显示PWM波在界面上
	//ui.lineEdit_pwm1->setText(data1);
	//ui.lineEdit_pwm2->setText(data2);
	//ui.lineEdit_pwm3->setText(data3);

	//通过串口发送PWM波给单片机
	sendCommand(cmd, V1, V2, V3);

}

//给定球场坐标速度求得轮子的速度
//显示在界面上
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
	L[1][0] = -1;						L[1][1] = 0;						L[1][2] = -MOTOR_L;
	L[2][0] = 0.5;					L[2][1] = -0.8660254037844386;		L[2][2] = -MOTOR_L;
	//		cos(theta)	sin(theta)	0
	//theta= -sin(theta)	cos(theta) 	0
	//		 	0			0		1
	theta[0][0] = cos(ThetaR);	theta[0][1] = sin(ThetaR);	theta[0][2] = 0;
	theta[1][0] = -theta[0][1];				theta[1][1] = theta[0][0];				theta[1][2] = 0;
	theta[2][0] = 0;						theta[2][1] = 0;						theta[2][2] = 1;
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

	////将轮子速度从float型转换成QString型
	//QString datav1 = QString("%1").arg(Robot.Velocity[0]);
	//QString datav2 = QString("%1").arg(Robot.Velocity[1]);
	//QString datav3 = QString("%1").arg(Robot.Velocity[2]);

	////将轮子速度显示在界面上
	//ui.lineEdit_V1->setText(datav1);
	//ui.lineEdit_V2->setText(datav2);
	//ui.lineEdit_V3->setText(datav3);

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

	////将轮子速度从float型转换成QString型
	//QString datav1 = QString("%1").arg(Robot.Velocity[0]);
	//QString datav2 = QString("%1").arg(Robot.Velocity[1]);
	//QString datav3 = QString("%1").arg(Robot.Velocity[2]);

	////将轮子速度显示在界面上
	//ui.lineEdit_V1->setText(datav1);
	//ui.lineEdit_V2->setText(datav2);
	//ui.lineEdit_V3->setText(datav3);
}

//自旋运动，根据误差角度，自动调节
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

//行至指定坐标
//X_I：	目标坐标的X
//Y_I:	目标坐标的Y
//Theta_I:	目标坐标的角度
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
	sendCommand('D', 1000, 0, 0);
	//delay_ms(1000);
	RobotRotate(Theta_I);
}

//避障直行
void robot::RobotGoAvoidance()
{
	float D_Theta, Distance;
	//	float StraightDistance=0;

	D_Theta = Radar.Angle - RADAR_MID;
	Distance = Radar.Distance*sin(D_Theta);

	while ((Distance < 35) || (Distance > (-35))) 
	{
		D_Theta = Radar.Angle - 270;
		Distance = Radar.Distance*sin(D_Theta);

		if (Distance > 0) 
		{
			GetMotorVelocity_Self(6, 0, 0);
			SetPWM('A', Velocity[0], Velocity[1], Velocity[2]);
		}
		else 
		{
			GetMotorVelocity_Self(-6, 0, 0);
			SetPWM('A', Velocity[0], Velocity[1], Velocity[2]);
		}

		//延时
		sendCommand('D', 1000, 0, 0);
		//delay_ms(1000);
	}

	PX = X;
	PY = Y;

	/*
	while(StraightDistance<=1000){

	StraightDistance=sqrt(pow(BasketballRobot.PX-BasketballRobot.X,2)+pow(BasketballRobot.PY-BasketballRobot.Y,2));

	GetMotorVelocity_Self(0,10,0);
	SetPWM(BasketballRobot.Velocity[0],BasketballRobot.Velocity[1],BasketballRobot.Velocity[2]);
	delay_ms(1000);
	}
	*/

	RobotGoTo(PX + 700, PY + 500, 60);
	SetPWM('S', 0, 0, 0);

}

//所找球为篮球
//同时在界面上显示“篮球”
void robot::FindBasketball()
{
	//	ball = 1;
	//	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
	//ui.comboBox_ball->addItem("篮球");

}

//所找球为排球
//同时在界面上显示“排球”
void robot::FindVolleyball()
{
	//	ball = 3;
	//	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
	//ui.comboBox_ball->addItem("排球");
}

//视觉找球
//限制4米以内
void robot::FindBall_vision(unsigned char ball)
{
	float w = 200;

	unsigned char time = 1;
	unsigned char findballtime2 = 1;

	float theta = ThetaR, D_theta = 0;

	switch (ball)
	{
	case 1:
		FindBasketball();
		sendCommand('D', 100, 0, 0);	//延时	delay_ms(100);
		FindBasketball();
		sendCommand('D', 100, 0, 0);	//延时	delay_ms(100);
		FindBasketball();
		break;
	case 3:
		FindVolleyball();
		sendCommand('D', 100, 0, 0);	//延时	delay_ms(100);
		FindVolleyball();
		sendCommand('D', 100, 0, 0);	//延时	delay_ms(100);
		FindVolleyball();
		break;
	}

	SetPWM('S', 0, 0, 0);

	//while(receive != 1);
	//USART1_RX_STA = 0;
	//receive = 0;
	do {
		//等待数据接收完成
		//while (receive != 1);

		//所得数据无效
		if (!Vision.State)
		{
			if (time == 0);

			//尝试五次
			else if (time++ <5)
			{
				//SetPWM(0,0,0);
				continue;
			}
			//尝试五次后仍未找到球
			else if (time != 0)
				time = 0;
		}
		//数据有效
		else
			time = 1;

		//没找到球,自转
		if (time == 0)
		{
			D_theta = ThetaR - theta;
			if ((D_theta > PI / 6.0f && D_theta < PI) || (D_theta < -PI && D_theta > -PI * 11.0f / 6.0f))
			{
				w = -200;
			}
			if ((D_theta < -PI / 6.0f && D_theta > -PI) || (D_theta > PI && D_theta < PI*11.0f / 6.0f))
			{
				w = 200;
			}
			GetMotorVelocity(0, 0, w);
			SetPWM('Z', Velocity[0], Velocity[1], Velocity[2]);

			//如果调整100次后仍未找到球，则退出
			findballtime++;
			if (findballtime >= 100) {
				findballtime = 0;
				findballtime2 = 0;
				break;
			}
		}

		//无效数据
		else if (Vision.Depth > 4000)
		{
			GetMotorVelocity(0, 0, 0);
			SetPWM('S', Velocity[0], Velocity[1], Velocity[2]);
		}

		else if ((Vision.X< VISION_MID - 30) && Vision.Depth>1300)
		{
			GetMotorVelocity_Self(-5, 10, 0);  //原来 -50 10 0
			SetPWM('F', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if ((Vision.X > VISION_MID + 30) && Vision.Depth > 1300)
		{
			GetMotorVelocity_Self(5, 10, 0);
			SetPWM('F', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if (Vision.Depth > 1300)
		{
			GetMotorVelocity_Self(0, 20, 0);
			SetPWM('F', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if ((Vision.X< VISION_MID - 20) && Vision.Depth > 700)
		{
			GetMotorVelocity_Self(-4, 0, 0);  //原来-40 0 0
			SetPWM('F', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if ((Vision.X > VISION_MID + 20) && (Vision.Depth >700))
		{
			GetMotorVelocity_Self(4, 0, 0); //原来4 0 0
			SetPWM('F', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if (Vision.Depth>700)
		{
			GetMotorVelocity_Self(0, 12, 0);
			SetPWM('F', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if (Vision.X< VISION_MID - 30)
		{
			GetMotorVelocity_Self(-3, 0, 0); //原来-30 0 0
			SetPWM('F', Velocity[0], Velocity[1], Velocity[2]);;
		}
		else if (Vision.X > VISION_MID + 30)
		{
			GetMotorVelocity_Self(3, 0, 0); //原来30 0 0
			SetPWM('F', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if (Vision.X <= VISION_MID + 30 && Vision.X > VISION_MID + 10)
		{
			GetMotorVelocity_Self(1.5, 0, 0); //原来15 0 0 
			SetPWM('F', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if (Vision.X >= VISION_MID - 30 && Vision.X < VISION_MID - 10)
		{
			GetMotorVelocity_Self(-1.5, 0, 0); //原来-15 0 0 
			SetPWM('F', Velocity[0], Velocity[1], Velocity[2]);
		}
		else
		{
			SetPWM('S', 0, 0, 0);

			SetPWM('Y', 0, 0, 0);	//发送信号给单片机，铲子下降 Robot_armDown();
			GetMotorVelocity_Self(0, 7, 0);
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
			break;

		}
	} while (1);

	//如果找到球
	if (findballtime2 == 1) {

		//获取红外状态 GetInfraredState();
		while (1)
		{
			if (Infr)
				break;
		}

		SetPWM('S', 0, 0, 0);	//铲到球，停止前进

		SetPWM('N', 0, 0, 0);	//铲到球，升铲 Robot_armUp();
	}

}

//利用激光找球
//不用区分颜色
//限制3m以内
void robot::FindBall_radar(void)
{
	float w = 300;
	float theta = ThetaD, D_theta = 0;

	SetPWM('S', 0, 0, 0);
	do {
		//while (receive3 != 1);

		if (!Radar.State)
		{

			SetPWM('S', 0, 0, 0);
			//	continue;
		}
		//LED0 = !LED0;

		if (Radar.Distance < 10)
			continue;
		if (Radar.Distance > 3000)
		{
			D_theta = ThetaR - theta;
			if ((D_theta > PI / 6.0f && D_theta < PI) || (D_theta < -PI && D_theta > -PI * 11.0f / 6.0f))
			{
				w = -300;
			}
			if ((D_theta < -PI / 6.0f && D_theta > -PI) || (D_theta > PI && D_theta < PI*11.0f / 6.0f))
			{
				w = 300;
			}
			GetMotorVelocity(0, 0, w);
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if (Radar.Angle< RADAR_MID - 15)
		{
			GetMotorVelocity_Self(0, 0, 200);
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if (Radar.Angle > RADAR_MID + 15)
		{
			GetMotorVelocity_Self(0, 0, -200);
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if (Radar.Distance > 1000)
		{
			GetMotorVelocity_Self(0, 30, 0);
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if ((Radar.Angle< RADAR_MID - 10) && Radar.Distance >700)
		{
			GetMotorVelocity_Self(0, 0, 150);
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if ((Radar.Angle > RADAR_MID + 10) && Radar.Distance >700)
		{
			GetMotorVelocity_Self(0, 0, -150);
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if (Radar.Distance>700)
		{
			GetMotorVelocity_Self(0, 20, 0);
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if (Radar.Angle< RADAR_MID - 5)
		{
			GetMotorVelocity_Self(-8, 0, 0); //原来-80 0 0
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if (Radar.Angle > RADAR_MID + 5)
		{
			GetMotorVelocity_Self(8, 0, 0);//原来80 0 0
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
		}
		else
		{
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
			SetPWM('Y', 0, 0, 0);	//发送信号给单片机，铲子下降 Robot_armDown();
			GetMotorVelocity_Self(0, 7, 0);
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
			if (Radar.Distance < 350)
				break;
		}
	} while (1);

	//获取红外状态 GetInfraredState();
	while (1)
	{
		if (Infr)
			break;
	}

	SetPWM('S', 0, 0, 0);

	SetPWM('N', 0, 0, 0);	//铲到球，升铲 Robot_armUp();

}

//视觉、雷达找球结合
//限制4m以内
void robot::FindBall_VandR(unsigned char ball)
{

	float w = 200;
	unsigned char time = 1;
	//	u8 findballtime2 = 1;
	float theta = ThetaR, D_theta = 0;
	switch (ball)
	{
	case 1:
		FindBasketball();
		sendCommand('D', 10000, 0, 0);	//延时	delay_ms(10000);
		FindBasketball();
		sendCommand('D', 10000, 0, 0);	//延时	delay_ms(10000);
		FindBasketball();
		break;
	case 3:
		FindVolleyball();

		sendCommand('D', 10000, 0, 0);	//延时	delay_ms(10000);

		FindVolleyball();
		sendCommand('D', 10000, 0, 0);	//延时	delay_ms(10000);
		FindVolleyball();

		break;


	}
	SetPWM('S', 0, 0, 0);

	//清空视觉串口数据
	//	while (receive != 1);
	//	USART1_RX_STA = 0;
	//	receive = 0;

	//清空串口接收数据缓存   
	//	receive3 = 0;
	//	USART3_RX_STA = 0;

	SetPWM('S', 0, 0, 0);

	//防止无效数据

	//	while (receive3 != 1);
	//	receive3 = 0;
	//	USART3_RX_STA = 0;


	do {
		//while (receive != 1);
		//while (receive3 != 1);

		if (!Vision.State)
		{
			if (time == 0)
			{
			}
			else if (time++ <5)
			{
				SetPWM('S', 0, 0, 0);
				continue;
			}
			else if (time != 0)
				time = 0;
		}
		else
			time = 1;

		//GetRadarData();

		if (time == 0)
		{
			D_theta = ThetaR - theta;
			if ((D_theta > PI / 6.0f && D_theta < PI) || (D_theta < -PI && D_theta > -PI * 11.0f / 6.0f))
			{
				w = -200;
			}
			if ((D_theta < -PI / 6.0f && D_theta > -PI) || (D_theta > PI && D_theta < PI*11.0f / 6.0f))
			{
				w = 200;
			}
			GetMotorVelocity(0, 0, w);
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
			findballtime++;

			//如果调整100次仍未找到球，则退出
			if (findballtime >= 100) {
				findballtime = 0;
				//				findballtime2=0;
				break;
			}
		}
		else if (Vision.Depth>4000)
		{

			SetPWM('S', 0, 0, 0);
		}
		else if ((Vision.X< VISION_MID - 30) && Vision.Depth>1000)
		{
			GetMotorVelocity_Self(-8, 16, 0); //原来-5 10 0
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if ((Vision.X > VISION_MID + 30) && Vision.Depth > 1000)
		{
			GetMotorVelocity_Self(8, 16, 0);//原来 5 10 0
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
		}
		else if (Vision.Depth > 1000)
		{
			GetMotorVelocity_Self(0, 30, 0);
			SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
		}
		else
			break;
	} while (1);

	if (Radar.Distance>800)
	{
		//		LCD_ShowString(30 + 200, 500, 200, 16, 16, "View!");
		//雷达数据不同时，按照视觉数据寻找
		while (1)
		{
			//while (receive != 1);

			//GetVisionData();
			//GetRadarData();

			if (Radar.Distance<800)
				break;

			if (!Vision.State)
				SetPWM('S', 0, 0, 0);

			if (Radar.Angle< VISION_MID - 20)
			{
				GetMotorVelocity_Self(-6, 0, 0); //原来-4 0 0
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
			}
			else if (Radar.Angle > VISION_MID + 20)
			{
				GetMotorVelocity_Self(6, 0, 0);//原来4 0 0
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
			}

			else if (Radar.Distance>700)
			{
				GetMotorVelocity_Self(0, 20, 0);
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
			}

			else if (Radar.Angle< VISION_MID - 30)
			{
				GetMotorVelocity_Self(-6, 0, 0); //原来-3 0 0
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);
			}
			else if (Radar.Angle > VISION_MID + 30)
			{
				GetMotorVelocity_Self(6, 0, 0);//原来 3 0 0
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);


			}
			else if (Radar.Angle <= VISION_MID + 30 && Radar.Angle > VISION_MID + 10)
			{
				GetMotorVelocity_Self(3, 0, 0); //原来 1.5 0 0 
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);


			}
			else if (Radar.Angle >= VISION_MID - 30 && Radar.Angle < VISION_MID - 10)
			{
				GetMotorVelocity_Self(-3, 0, 0);//原来-1.5 0 0
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);


			}
			else
			{
				SetPWM('S', 0, 0, 0);
				SetPWM('Y', 0, 0, 0);	//发送信号给单片机，铲子下降 Robot_armDown();
				GetMotorVelocity_Self(0, 7, 0);
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);


				break;
			}
		}
	}



	if (Radar.Distance <= 800)
	{
		//LCD_ShowString(30 + 200, 500, 200, 16, 16, "Radar!");
		//雷达数据相同，按照雷达数据寻找
		while (1)
		{
			//while (receive3 != 1);
			//GetRadarData();
			//GetVisionData();

			if (!Radar.State)
			{
				GetMotorVelocity_Self(0, 0, 0);
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);


			}

			else if ((Radar.Angle< RADAR_MID - 10) && Radar.Distance >700)
			{
				GetMotorVelocity_Self(-10, 0, 0);//原来-10 0 0
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);


			}
			else if ((Radar.Angle > RADAR_MID + 10) && Radar.Distance >700)
			{
				GetMotorVelocity_Self(10, 0, 0); //原来10 0 0
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);


			}
			else if (Radar.Distance>700)
			{
				GetMotorVelocity_Self(0, 20, 0); //原来 0 14 0
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);


			}
			else if (Radar.Angle< RADAR_MID - 5)
			{
				GetMotorVelocity_Self(-10, 0, 0);//原来-10 0 0
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);


			}
			else if (Radar.Angle > RADAR_MID + 5)
			{
				GetMotorVelocity_Self(10, 0, 0);//原来10 0 0
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);


			}
			/*	else if(Radar.Angle <= RADAR_MID+5 && Radar.Angle > RADAR_MID+2)
			{
			GetMotorVelocity_Self(1,0,0);
			SetPWM(BasketballRobot.Velocity[0],BasketballRobot.Velocity[1],BasketballRobot.Velocity[2]);


			}
			else if(Radar.Angle >= RADAR_MID-5 && Radar.Angle < RADAR_MID -2)
			{
			GetMotorVelocity_Self(-1,0,0);
			SetPWM(BasketballRobot.Velocity[0],BasketballRobot.Velocity[1],BasketballRobot.Velocity[2]);


			}
			*/
			else
			{
				SetPWM('S', 0, 0, 0);
				SetPWM('Y', 0, 0, 0);	//发送信号给单片机，铲子下降 Robot_armDown();
				GetMotorVelocity_Self(0, 7, 0);//原来0 7 0 
				SetPWM('O', Velocity[0], Velocity[1], Velocity[2]);


				if (Radar.Distance < 350)
					break;
			}

		}
	}


	//获取红外状态 GetInfraredState();
	while (1)
	{
		if (Infr)
			break;
	}	SetPWM('S', 0, 0, 0);

	SetPWM('N', 0, 0, 0);	//铲到球，升铲 Robot_armUp();


}






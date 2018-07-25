#include "control.h"
#include "robot.h"
#include <QtMath>
#include <QGraphicsScene>
#include <QMessageBox>
#include "MyMainWindow.h"

ROBOT Robot;
RADAR Radar;
VISION Vision;

int findballtime;		//找球时调整角度的次数

//机器人初始化函数
//在界面上显示相应信息
void MyMainWindow::Control_Init(void)
{
	Robot.X = 0;		//机器人在坐标系中x坐标
	Robot.Y = 0;		//机器人在坐标系中y坐标
	Robot.ThetaD = 0;		//机器人正方向与y轴夹角 角度
	Robot.ThetaR = 0;		//机器人正方向与y轴夹角 弧度
	Robot.PX = 0;			//临时点x坐标
	Robot.PY = 0;			//临时点y坐标
	Robot.Vx = 0;		//机器人在坐标系中x方向速度
	Robot.Vy = 0;		//机器人在坐标系中y方向速度
	Robot.W = 0;		//机器人角速度，顺时针为正方向

	Robot.w[1] = 0;		//第一个编码器实际计数
	Robot.w[2] = 0;		//第二个编码器实际计数
	Robot.w[0] = 0;		//第三个编码器实际计数

	Robot.v[1] = 0;		//第一个编码器所得速度
	Robot.v[2] = 0;		//第二个编码器所得速度
	Robot.v[0] = 0;		//第三个编码器所得速度

	Robot.LastTheta = 0;	//上一时刻机器人theta角
	Robot.theta_offset = 0;		//角度偏差矫正

	//雷达数据清空
	Radar.Distance = 0;
	Radar.Angle = 0;
	
	//视觉数据清空
	Vision.Depth = 0;
	Vision.X = 0;

	//将float型转换成QString类型
	QString dataX = QString("%1").arg(Robot.X);
	QString dataY = QString("%1").arg(Robot.Y);
	QString dataTD = QString("%1").arg(Robot.ThetaD);
	QString dataTR = QString("%1").arg(Robot.ThetaR);

	QString dataVx = QString("%1").arg(Robot.Vx);
	QString dataVy = QString("%1").arg(Robot.Vy);
	QString dataVw = QString("%1").arg(Robot.W);

	QString dataw1 = QString("%1").arg(Robot.w[1]);
	QString dataw2 = QString("%1").arg(Robot.w[2]);
	QString dataw0 = QString("%1").arg(Robot.w[0]);

//	QString datav1 = QString("%1").arg(Robot.v[1]);
//	QString datav2 = QString("%1").arg(Robot.v[2]);
//	QString datav0 = QString("%1").arg(Robot.v[0]);

	QString dataRD = QString("%1").arg(Radar.Distance);
	QString dataRA = QString("%1").arg(Radar.Angle);


	ui.lineEdit_x->setText(dataX);
	ui.lineEdit_y->setText(dataY);
	ui.lineEdit_row->setText(dataRD);

	ui.lineEdit_V1_2->setText(dataVx);
	ui.lineEdit_V2_2->setText(dataVy);
	ui.lineEdit_V3_2->setText(dataVw);

	ui.lineEdit_pwm1->setText(dataw1);
	ui.lineEdit_pwm2->setText(dataw2);
	ui.lineEdit_pwm3->setText(dataw0);

}

//根据偏差大小调整角速度
static float AdjustAngleV(float D_Theta)
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
static float AdjustVy(float D_Y)
{
	float sy;

	if (D_Y > 0.05f)
	{

		if (D_Y >= 1.5f)
		{
			sy = 8;
			if (Robot.Vy < 0.3f)
				sy = 2;
			else if (Robot.Vy < 0.5f)
				sy = 4;
			else if (Robot.Vy < 0.9f)
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
			if (Robot.Vy > -0.3f)
				sy = -2;
			else if (Robot.Vy > -0.5f)
				sy = -4;
			else if (Robot.Vy > -0.9f)
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
static float AdjustVx(float D_X)
{
	float sx;

	if (D_X > 0.05f)
	{
		if (D_X > 1.5f)
		{
			sx = 8;
			if (Robot.Vx < 0.1f)
				sx = 0.5;
			else if (Robot.Vx < 0.2f)
				sx = 1;
			else if (Robot.Vx < 0.4f)
				sx = 2;
			else if (Robot.Vx < 0.58f)
				sx = 4;
			else if (Robot.Vx < 7.5f)
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
			if (Robot.Vx > -0.1f)
				sx = -0.5;
			else if (Robot.Vx > -0.2f)
				sx = -1;
			else if (Robot.Vx > -0.4f)
				sx = -2;
			else if (Robot.Vx > -0.58f)
				sx = -4;
			else if (Robot.Vx > -7.5f)
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
static void Velocity2PWM(float *V)
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
void MyMainWindow::SetPWM(char cmd,float V1, float V2, float V3)
{
	Robot.Velocity[0] = V1;
	Robot.Velocity[1] = V2;
	Robot.Velocity[2] = V3;

	//转换
	Velocity2PWM(&V1);
	Velocity2PWM(&V2);
	Velocity2PWM(&V3);

	//将float型转换成QString类型
	QString data1 = QString("%1").arg(V1);
	QString data2 = QString("%1").arg(V2);
	QString data3 = QString("%1").arg(V3);

	//显示PWM波在界面上
	ui.lineEdit_pwm1->setText(data1);
	ui.lineEdit_pwm2->setText(data2);
	ui.lineEdit_pwm3->setText(data3);

	//通过串口发送PWM波给单片机
	uartSendCommand(cmd, V1, V2, V3);	

}

//给定球场坐标速度求得轮子的速度
//显示在界面上
void MyMainWindow::GetMotorVelocity(float vx, float vy, float w)
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
	theta[0][0] = cos(Robot.ThetaR);	theta[0][1] = sin(Robot.ThetaR);	theta[0][2] = 0;
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
		Robot.Velocity[i] = 0;
		for (j = 0; j<3; j++)
			Robot.Velocity[i] += tem[i][j] * V[j];
	}

	//将轮子速度从float型转换成QString型
	QString datav1 = QString("%1").arg(Robot.Velocity[0]);
	QString datav2 = QString("%1").arg(Robot.Velocity[1]);
	QString datav3 = QString("%1").arg(Robot.Velocity[2]);

	//将轮子速度显示在界面上
	ui.lineEdit_V1->setText(datav1);
	ui.lineEdit_V2->setText(datav2);
	ui.lineEdit_V3->setText(datav3);
	
}

//给定自身坐标系速度求得轮子的速度
//显示在界面上
void MyMainWindow::GetMotorVelocity_Self(float vx, float vy, float w)
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
		Robot.Velocity[i] = 0;
		for (j = 0; j<3; j++)
			Robot.Velocity[i] += L[i][j] * V[j];
	}

	//将轮子速度从float型转换成QString型
	QString datav1 = QString("%1").arg(Robot.Velocity[0]);
	QString datav2 = QString("%1").arg(Robot.Velocity[1]);
	QString datav3 = QString("%1").arg(Robot.Velocity[2]);

	//将轮子速度显示在界面上
	ui.lineEdit_V1->setText(datav1);
	ui.lineEdit_V2->setText(datav2);
	ui.lineEdit_V3->setText(datav3);
}

//自旋运动，根据误差角度，自动调节
void MyMainWindow::RobotRotate(float theta)
{
	float D_Theta;
	float Vw = 0;        //W大于0 逆时针

						 //D_Theta = theta-BasketballRobot.ThetaD;
	D_Theta = theta - 0;
	Vw = AdjustAngleV(D_Theta);


	while (D_Theta>1 || D_Theta < -1)
	{
		GetMotorVelocity(0, 0, Vw);

		SetPWM('Z',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);

		D_Theta = theta - Robot.ThetaD;

		Vw = AdjustAngleV(D_Theta);
	}

	SetPWM('S',0, 0, 0);

	while (Robot.W);
}

//行至指定坐标
//X_I：	目标坐标的X
//Y_I:	目标坐标的Y
//Theta_I:	目标坐标的角度
void MyMainWindow::RobotGoTo(float X_I, float Y_I, float Theta_I)
{
	float D_Theta, D_X, D_Y, Vw = 0, sx, sy = 0;
	
	D_Theta = Theta_I - Robot.ThetaD;	//角度差
	D_X = X_I - Robot.X;
	D_Y = Y_I - Robot.Y;

	while (fabs(D_Y) > 0.05f || fabs(D_X) > 0.05f)
	{
		sy = AdjustVy(D_Y);

		sx = AdjustVx(D_X);

		Vw = AdjustAngleV(D_Theta) / 2;

		GetMotorVelocity(sx * 12, sy * 100, Vw);

		SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);

		D_Theta = Theta_I - Robot.ThetaD;
		D_X = X_I - Robot.X;
		D_Y = Y_I - Robot.Y;
	}
	
	SetPWM('S',0, 0, 0);

	//延时
	uartSendCommand('D', 1000, 0, 0);
	//delay_ms(1000);
	RobotRotate(Theta_I);
}

//避障直行
void MyMainWindow::RobotGoAvoidance(void)
{
	float D_Theta, Distance;
	//	float StraightDistance=0;

	D_Theta = Radar.Angle - RADAR_MID;
	Distance = Radar.Distance*sin(D_Theta);

	while ((Distance<35) || (Distance>(-35))) {
		D_Theta = Radar.Angle - 270;
		Distance = Radar.Distance*sin(D_Theta);

		if (Distance>0) {
			GetMotorVelocity_Self(6, 0, 0);
			SetPWM('A',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else {
			GetMotorVelocity_Self(-6, 0, 0);
			SetPWM('A',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}

		//延时
		uartSendCommand('D', 1000, 0, 0);
		//delay_ms(1000);
	}

	Robot.PX = Robot.X;
	Robot.PY = Robot.Y;

	/*
	while(StraightDistance<=1000){

	StraightDistance=sqrt(pow(BasketballRobot.PX-BasketballRobot.X,2)+pow(BasketballRobot.PY-BasketballRobot.Y,2));

	GetMotorVelocity_Self(0,10,0);
	SetPWM(BasketballRobot.Velocity[0],BasketballRobot.Velocity[1],BasketballRobot.Velocity[2]);
	delay_ms(1000);
	}
	*/

	RobotGoTo(Robot.PX + 700, Robot.PY + 500, 60);
	SetPWM('S',0, 0, 0);

}

//所找球为篮球
//同时在界面上显示“篮球”
void MyMainWindow::FindBasketball(void)
{
//	ball = 1;
//	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
	ui.comboBox_ball->addItem("篮球");
}

//所找球为排球
//同时在界面上显示“排球”
void MyMainWindow::FindVolleyball(void)
{
//	ball = 3;
//	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
	ui.comboBox_ball->addItem("排球");
}

//视觉找球
//限制4米以内
void MyMainWindow::FindBall_vision(unsigned char ball)
{
	float w = 200;

	unsigned char time = 1;
	unsigned char findballtime2 = 1;

	float theta = Robot.ThetaR, D_theta = 0;

	switch (ball)
	{
	case 1:
		FindBasketball();
		uartSendCommand('D', 100, 0, 0);	//延时	delay_ms(100);
		FindBasketball();
		uartSendCommand('D', 100, 0, 0);	//延时	delay_ms(100);
		FindBasketball();
		break;
	case 3:
		FindVolleyball();
		uartSendCommand('D', 100, 0, 0);	//延时	delay_ms(100);
		FindVolleyball();
		uartSendCommand('D', 100, 0, 0);	//延时	delay_ms(100);
		FindVolleyball();
		break;
	}

	SetPWM('S',0, 0, 0);

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
			D_theta = Robot.ThetaR - theta;
			if ((D_theta > PI / 6.0f && D_theta < PI) || (D_theta < -PI && D_theta > -PI * 11.0f / 6.0f))
			{
				w = -200;
			}
			if ((D_theta < -PI / 6.0f && D_theta > -PI) || (D_theta > PI && D_theta < PI*11.0f / 6.0f))
			{
				w = 200;
			}
			GetMotorVelocity(0, 0, w);
			SetPWM('Z',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);

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
			SetPWM('S',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}

		else if ((Vision.X< VISION_MID - 30) && Vision.Depth>1300)
		{
			GetMotorVelocity_Self(-5, 10, 0);  //原来 -50 10 0
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1],Robot.Velocity[2]);
		}
		else if ((Vision.X > VISION_MID + 30) && Vision.Depth > 1300)
		{
			GetMotorVelocity_Self(5, 10, 0);
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Vision.Depth > 1300)
		{
			GetMotorVelocity_Self(0, 20, 0);
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if ((Vision.X< VISION_MID - 20) && Vision.Depth > 700)
		{
			GetMotorVelocity_Self(-4, 0, 0);  //原来-40 0 0
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if ((Vision.X > VISION_MID + 20) && (Vision.Depth >700))
		{
			GetMotorVelocity_Self(4, 0, 0); //原来4 0 0
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Vision.Depth>700)
		{
			GetMotorVelocity_Self(0, 12, 0);
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Vision.X< VISION_MID - 30)
		{
			GetMotorVelocity_Self(-3, 0, 0); //原来-30 0 0
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);;
		}
		else if (Vision.X > VISION_MID + 30)
		{
			GetMotorVelocity_Self(3, 0, 0); //原来30 0 0
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Vision.X <= VISION_MID + 30 && Vision.X > VISION_MID + 10)
		{
			GetMotorVelocity_Self(1.5, 0, 0); //原来15 0 0 
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Vision.X >= VISION_MID - 30 && Vision.X < VISION_MID - 10)
		{
			GetMotorVelocity_Self(-1.5, 0, 0); //原来-15 0 0 
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else
		{
			SetPWM('S',0, 0, 0);

			SetPWM('Y', 0, 0, 0);	//发送信号给单片机，铲子下降 Robot_armDown();
			GetMotorVelocity_Self(0, 7, 0);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			break;

		}
	} while (1);

	//如果找到球
	if (findballtime2 == 1) {

		//获取红外状态 GetInfraredState();
		while (1)
		{
			if (Robot.Infr)
				break;
		}

		SetPWM('S',0, 0, 0);	//铲到球，停止前进

		SetPWM('N', 0, 0, 0);	//铲到球，升铲 Robot_armUp();
	}

}

//利用激光找球
//不用区分颜色
//限制3m以内
void MyMainWindow::FindBall_radar(void)
{
	float w = 300;
	float theta = Robot.ThetaD, D_theta = 0;

	SetPWM('S', 0, 0, 0);
	do {
		//while (receive3 != 1);

		if (!Radar.State)
		{

			SetPWM('S',0, 0, 0);
			//	continue;
		}
		//LED0 = !LED0;

		if (Radar.Distance < 10)
			continue;
		if (Radar.Distance > 3000)
		{
			D_theta = Robot.ThetaR - theta;
			if ((D_theta > PI / 6.0f && D_theta < PI) || (D_theta < -PI && D_theta > -PI * 11.0f / 6.0f))
			{
				w = -300;
			}
			if ((D_theta < -PI / 6.0f && D_theta > -PI) || (D_theta > PI && D_theta < PI*11.0f / 6.0f))
			{
				w = 300;
			}
			GetMotorVelocity(0, 0, w);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Radar.Angle< RADAR_MID - 15)
		{
			GetMotorVelocity_Self(0, 0, 200);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Radar.Angle > RADAR_MID + 15)
		{
			GetMotorVelocity_Self(0, 0, -200);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Radar.Distance > 1000)
		{
			GetMotorVelocity_Self(0, 30, 0);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if ((Radar.Angle< RADAR_MID - 10) && Radar.Distance >700)
		{
			GetMotorVelocity_Self(0, 0, 150);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if ((Radar.Angle > RADAR_MID + 10) && Radar.Distance >700)
		{
			GetMotorVelocity_Self(0, 0, -150);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Radar.Distance>700)
		{
			GetMotorVelocity_Self(0, 20, 0);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Radar.Angle< RADAR_MID - 5)
		{
			GetMotorVelocity_Self(-8, 0, 0); //原来-80 0 0
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Radar.Angle > RADAR_MID + 5)
		{
			GetMotorVelocity_Self(8, 0, 0);//原来80 0 0
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else
		{
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			SetPWM('Y', 0, 0, 0);	//发送信号给单片机，铲子下降 Robot_armDown();
			GetMotorVelocity_Self(0, 7, 0);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			if (Radar.Distance < 350)
				break;
		}
	} while (1);

	//获取红外状态 GetInfraredState();
	while (1)
	{
		if (Robot.Infr)
			break;
	}

	SetPWM('S',0, 0, 0);

	SetPWM('N', 0, 0, 0);	//铲到球，升铲 Robot_armUp();

}

//视觉、雷达找球结合
//限制4m以内
void MyMainWindow::FindBall_VandR(unsigned char ball)
{

	float w = 200;
	unsigned char time = 1;
	//	u8 findballtime2 = 1;
	float theta = Robot.ThetaR, D_theta = 0;
	switch (ball)
	{
	case 1:
		FindBasketball();
		uartSendCommand('D', 10000, 0, 0);	//延时	delay_ms(10000);
		FindBasketball();
		uartSendCommand('D', 10000, 0, 0);	//延时	delay_ms(10000);
		FindBasketball();
		break;
	case 3:
		FindVolleyball();

		uartSendCommand('D', 10000, 0, 0);	//延时	delay_ms(10000);

		FindVolleyball();
		uartSendCommand('D', 10000, 0, 0);	//延时	delay_ms(10000);
		FindVolleyball();

		break;


	}
	SetPWM('S',0, 0, 0);
	
	//清空视觉串口数据
//	while (receive != 1);
//	USART1_RX_STA = 0;
//	receive = 0;

	//清空串口接收数据缓存   
//	receive3 = 0;
//	USART3_RX_STA = 0;

	SetPWM('S',0, 0, 0);
	
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
				SetPWM('S',0, 0, 0);
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
			D_theta = Robot.ThetaR - theta;
			if ((D_theta > PI / 6.0f && D_theta < PI) || (D_theta < -PI && D_theta > -PI * 11.0f / 6.0f))
			{
				w = -200;
			}
			if ((D_theta < -PI / 6.0f && D_theta > -PI) || (D_theta > PI && D_theta < PI*11.0f / 6.0f))
			{
				w = 200;
			}
			GetMotorVelocity(0, 0, w);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
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

			SetPWM('S',0, 0, 0);
		}
		else if ((Vision.X< VISION_MID - 30) && Vision.Depth>1000)
		{
			GetMotorVelocity_Self(-8, 16, 0); //原来-5 10 0
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if ((Vision.X > VISION_MID + 30) && Vision.Depth > 1000)
		{
			GetMotorVelocity_Self(8, 16, 0);//原来 5 10 0
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Vision.Depth > 1000)
		{
			GetMotorVelocity_Self(0, 30, 0);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
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
				SetPWM('S',0, 0, 0);

			if (Radar.Angle< VISION_MID - 20)
			{
				GetMotorVelocity_Self(-6, 0, 0); //原来-4 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			}
			else if (Radar.Angle > VISION_MID + 20)
			{
				GetMotorVelocity_Self(6, 0, 0);//原来4 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			}

			else if (Radar.Distance>700)
			{
				GetMotorVelocity_Self(0, 20, 0);
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			}

			else if (Radar.Angle< VISION_MID - 30)
			{
				GetMotorVelocity_Self(-6, 0, 0); //原来-3 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			}
			else if (Radar.Angle > VISION_MID + 30)
			{
				GetMotorVelocity_Self(6, 0, 0);//原来 3 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}
			else if (Radar.Angle <= VISION_MID + 30 && Radar.Angle > VISION_MID + 10)
			{
				GetMotorVelocity_Self(3, 0, 0); //原来 1.5 0 0 
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}
			else if (Radar.Angle >= VISION_MID - 30 && Radar.Angle < VISION_MID - 10)
			{
				GetMotorVelocity_Self(-3, 0, 0);//原来-1.5 0 0
				SetPWM('O', Robot.Velocity[0],Robot.Velocity[1], Robot.Velocity[2]);


			}
			else
			{
				SetPWM('S',0, 0, 0);
				SetPWM('Y', 0, 0, 0);	//发送信号给单片机，铲子下降 Robot_armDown();
				GetMotorVelocity_Self(0, 7, 0);
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


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
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}

			else if ((Radar.Angle< RADAR_MID - 10) && Radar.Distance >700)
			{
				GetMotorVelocity_Self(-10, 0, 0);//原来-10 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}
			else if ((Radar.Angle > RADAR_MID + 10) && Radar.Distance >700)
			{
				GetMotorVelocity_Self(10, 0, 0); //原来10 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}
			else if (Radar.Distance>700)
			{
				GetMotorVelocity_Self(0, 20, 0); //原来 0 14 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}
			else if (Radar.Angle< RADAR_MID - 5)
			{
				GetMotorVelocity_Self(-10, 0, 0);//原来-10 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}
			else if (Radar.Angle > RADAR_MID + 5)
			{
				GetMotorVelocity_Self(10, 0, 0);//原来10 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


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
				SetPWM('S',0, 0, 0);
				SetPWM('Y', 0, 0, 0);	//发送信号给单片机，铲子下降 Robot_armDown();
				GetMotorVelocity_Self(0, 7, 0);//原来0 7 0 
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1],Robot.Velocity[2]);


				if (Radar.Distance < 350)
					break;
			}

		}
	}


	//获取红外状态 GetInfraredState();
	while (1)
	{
		if (Robot.Infr)
			break;
	}	SetPWM('S',0, 0, 0);

	SetPWM('N', 0, 0, 0);	//铲到球，升铲 Robot_armUp();


}


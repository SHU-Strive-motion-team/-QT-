#include "control.h"
#include "robot.h"
#include <QtMath>
#include <QGraphicsScene>
#include <QMessageBox>
#include "MyMainWindow.h"

ROBOT Robot;
RADAR Radar;
VISION Vision;

int findballtime;		//����ʱ�����ǶȵĴ���

//�����˳�ʼ������
//�ڽ�������ʾ��Ӧ��Ϣ
void MyMainWindow::Control_Init(void)
{
	Robot.X = 0;		//������������ϵ��x����
	Robot.Y = 0;		//������������ϵ��y����
	Robot.ThetaD = 0;		//��������������y��н� �Ƕ�
	Robot.ThetaR = 0;		//��������������y��н� ����
	Robot.PX = 0;			//��ʱ��x����
	Robot.PY = 0;			//��ʱ��y����
	Robot.Vx = 0;		//������������ϵ��x�����ٶ�
	Robot.Vy = 0;		//������������ϵ��y�����ٶ�
	Robot.W = 0;		//�����˽��ٶȣ�˳ʱ��Ϊ������

	Robot.w[1] = 0;		//��һ��������ʵ�ʼ���
	Robot.w[2] = 0;		//�ڶ���������ʵ�ʼ���
	Robot.w[0] = 0;		//������������ʵ�ʼ���

	Robot.v[1] = 0;		//��һ�������������ٶ�
	Robot.v[2] = 0;		//�ڶ��������������ٶ�
	Robot.v[0] = 0;		//�����������������ٶ�

	Robot.LastTheta = 0;	//��һʱ�̻�����theta��
	Robot.theta_offset = 0;		//�Ƕ�ƫ�����

	//�״��������
	Radar.Distance = 0;
	Radar.Angle = 0;
	
	//�Ӿ��������
	Vision.Depth = 0;
	Vision.X = 0;

	//��float��ת����QString����
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

//����ƫ���С�������ٶ�
static float AdjustAngleV(float D_Theta)
{
	float Vw = 0;

	//����30�����Կ���
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

		//С��60�����30������
		//ʵ��PWMΪ100
		if (D_Theta < 60)
		{
			if (Vw>0)
				Vw = 1000;
			else
				Vw = -1000;
		}

	//С��30�����5��
	if (D_Theta < 30)
	{
		if (Vw>30)
			Vw = 200;
		else
			Vw = -200;
	}
	//С��5��
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

//����ƫ���С����Y���ٶ�
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

//����ƫ���С����X���ٶ�
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

/*����ٶ�ת����PWM��ֵ*/
static void Velocity2PWM(float *V)
{
	*V = 1000 - *V;//*V+=1000;
	if (*V >= 1900)
		*V = 1900;
	if (*V <= 100)
		*V = 100;
}

//������������PWM�����͸���λ����ͬʱ��ʾ�ڽ�����
//cmd:	������	R����λ����					O:�����ߵ�					F������			
//				Y���ҵ��򣬷Ų�����			N���򲻼�������				Z�������˶�		
//				S��ֹͣ��������pwmֵ��Ϊ0��	D����ʱ						A������
//V1:	���1�ٶ�
//V2:	���2�ٶ�
//V3;	���3�ٶ�
void MyMainWindow::SetPWM(char cmd,float V1, float V2, float V3)
{
	Robot.Velocity[0] = V1;
	Robot.Velocity[1] = V2;
	Robot.Velocity[2] = V3;

	//ת��
	Velocity2PWM(&V1);
	Velocity2PWM(&V2);
	Velocity2PWM(&V3);

	//��float��ת����QString����
	QString data1 = QString("%1").arg(V1);
	QString data2 = QString("%1").arg(V2);
	QString data3 = QString("%1").arg(V3);

	//��ʾPWM���ڽ�����
	ui.lineEdit_pwm1->setText(data1);
	ui.lineEdit_pwm2->setText(data2);
	ui.lineEdit_pwm3->setText(data3);

	//ͨ�����ڷ���PWM������Ƭ��
	uartSendCommand(cmd, V1, V2, V3);	

}

//�����������ٶ�������ӵ��ٶ�
//��ʾ�ڽ�����
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

	//�������ٶȴ�float��ת����QString��
	QString datav1 = QString("%1").arg(Robot.Velocity[0]);
	QString datav2 = QString("%1").arg(Robot.Velocity[1]);
	QString datav3 = QString("%1").arg(Robot.Velocity[2]);

	//�������ٶ���ʾ�ڽ�����
	ui.lineEdit_V1->setText(datav1);
	ui.lineEdit_V2->setText(datav2);
	ui.lineEdit_V3->setText(datav3);
	
}

//������������ϵ�ٶ�������ӵ��ٶ�
//��ʾ�ڽ�����
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

	//�������ٶȴ�float��ת����QString��
	QString datav1 = QString("%1").arg(Robot.Velocity[0]);
	QString datav2 = QString("%1").arg(Robot.Velocity[1]);
	QString datav3 = QString("%1").arg(Robot.Velocity[2]);

	//�������ٶ���ʾ�ڽ�����
	ui.lineEdit_V1->setText(datav1);
	ui.lineEdit_V2->setText(datav2);
	ui.lineEdit_V3->setText(datav3);
}

//�����˶����������Ƕȣ��Զ�����
void MyMainWindow::RobotRotate(float theta)
{
	float D_Theta;
	float Vw = 0;        //W����0 ��ʱ��

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

//����ָ������
//X_I��	Ŀ�������X
//Y_I:	Ŀ�������Y
//Theta_I:	Ŀ������ĽǶ�
void MyMainWindow::RobotGoTo(float X_I, float Y_I, float Theta_I)
{
	float D_Theta, D_X, D_Y, Vw = 0, sx, sy = 0;
	
	D_Theta = Theta_I - Robot.ThetaD;	//�ǶȲ�
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

	//��ʱ
	uartSendCommand('D', 1000, 0, 0);
	//delay_ms(1000);
	RobotRotate(Theta_I);
}

//����ֱ��
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

		//��ʱ
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

//������Ϊ����
//ͬʱ�ڽ�������ʾ������
void MyMainWindow::FindBasketball(void)
{
//	ball = 1;
//	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
	ui.comboBox_ball->addItem("����");
}

//������Ϊ����
//ͬʱ�ڽ�������ʾ������
void MyMainWindow::FindVolleyball(void)
{
//	ball = 3;
//	HAL_UART_Transmit(&huart1, &ball, 1, 1000);
	ui.comboBox_ball->addItem("����");
}

//�Ӿ�����
//����4������
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
		uartSendCommand('D', 100, 0, 0);	//��ʱ	delay_ms(100);
		FindBasketball();
		uartSendCommand('D', 100, 0, 0);	//��ʱ	delay_ms(100);
		FindBasketball();
		break;
	case 3:
		FindVolleyball();
		uartSendCommand('D', 100, 0, 0);	//��ʱ	delay_ms(100);
		FindVolleyball();
		uartSendCommand('D', 100, 0, 0);	//��ʱ	delay_ms(100);
		FindVolleyball();
		break;
	}

	SetPWM('S',0, 0, 0);

	//while(receive != 1);
	//USART1_RX_STA = 0;
	//receive = 0;
	do {
		//�ȴ����ݽ������
		//while (receive != 1);

		//����������Ч
		if (!Vision.State)
		{
			if (time == 0);

			//�������
			else if (time++ <5)
			{
				//SetPWM(0,0,0);
				continue;
			}
			//������κ���δ�ҵ���
			else if (time != 0)
				time = 0;
		}
		//������Ч
		else
			time = 1;

		//û�ҵ���,��ת
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

			//�������100�κ���δ�ҵ������˳�
			findballtime++;
			if (findballtime >= 100) {
				findballtime = 0;
				findballtime2 = 0;
				break;
			}
		}

		//��Ч����
		else if (Vision.Depth > 4000)
		{
			GetMotorVelocity(0, 0, 0);
			SetPWM('S',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}

		else if ((Vision.X< VISION_MID - 30) && Vision.Depth>1300)
		{
			GetMotorVelocity_Self(-5, 10, 0);  //ԭ�� -50 10 0
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
			GetMotorVelocity_Self(-4, 0, 0);  //ԭ��-40 0 0
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if ((Vision.X > VISION_MID + 20) && (Vision.Depth >700))
		{
			GetMotorVelocity_Self(4, 0, 0); //ԭ��4 0 0
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Vision.Depth>700)
		{
			GetMotorVelocity_Self(0, 12, 0);
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Vision.X< VISION_MID - 30)
		{
			GetMotorVelocity_Self(-3, 0, 0); //ԭ��-30 0 0
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);;
		}
		else if (Vision.X > VISION_MID + 30)
		{
			GetMotorVelocity_Self(3, 0, 0); //ԭ��30 0 0
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Vision.X <= VISION_MID + 30 && Vision.X > VISION_MID + 10)
		{
			GetMotorVelocity_Self(1.5, 0, 0); //ԭ��15 0 0 
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Vision.X >= VISION_MID - 30 && Vision.X < VISION_MID - 10)
		{
			GetMotorVelocity_Self(-1.5, 0, 0); //ԭ��-15 0 0 
			SetPWM('F',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else
		{
			SetPWM('S',0, 0, 0);

			SetPWM('Y', 0, 0, 0);	//�����źŸ���Ƭ���������½� Robot_armDown();
			GetMotorVelocity_Self(0, 7, 0);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			break;

		}
	} while (1);

	//����ҵ���
	if (findballtime2 == 1) {

		//��ȡ����״̬ GetInfraredState();
		while (1)
		{
			if (Robot.Infr)
				break;
		}

		SetPWM('S',0, 0, 0);	//������ֹͣǰ��

		SetPWM('N', 0, 0, 0);	//���������� Robot_armUp();
	}

}

//���ü�������
//����������ɫ
//����3m����
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
			GetMotorVelocity_Self(-8, 0, 0); //ԭ��-80 0 0
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if (Radar.Angle > RADAR_MID + 5)
		{
			GetMotorVelocity_Self(8, 0, 0);//ԭ��80 0 0
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else
		{
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			SetPWM('Y', 0, 0, 0);	//�����źŸ���Ƭ���������½� Robot_armDown();
			GetMotorVelocity_Self(0, 7, 0);
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			if (Radar.Distance < 350)
				break;
		}
	} while (1);

	//��ȡ����״̬ GetInfraredState();
	while (1)
	{
		if (Robot.Infr)
			break;
	}

	SetPWM('S',0, 0, 0);

	SetPWM('N', 0, 0, 0);	//���������� Robot_armUp();

}

//�Ӿ����״�������
//����4m����
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
		uartSendCommand('D', 10000, 0, 0);	//��ʱ	delay_ms(10000);
		FindBasketball();
		uartSendCommand('D', 10000, 0, 0);	//��ʱ	delay_ms(10000);
		FindBasketball();
		break;
	case 3:
		FindVolleyball();

		uartSendCommand('D', 10000, 0, 0);	//��ʱ	delay_ms(10000);

		FindVolleyball();
		uartSendCommand('D', 10000, 0, 0);	//��ʱ	delay_ms(10000);
		FindVolleyball();

		break;


	}
	SetPWM('S',0, 0, 0);
	
	//����Ӿ���������
//	while (receive != 1);
//	USART1_RX_STA = 0;
//	receive = 0;

	//��մ��ڽ������ݻ���   
//	receive3 = 0;
//	USART3_RX_STA = 0;

	SetPWM('S',0, 0, 0);
	
	//��ֹ��Ч����

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

			//�������100����δ�ҵ������˳�
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
			GetMotorVelocity_Self(-8, 16, 0); //ԭ��-5 10 0
			SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
		}
		else if ((Vision.X > VISION_MID + 30) && Vision.Depth > 1000)
		{
			GetMotorVelocity_Self(8, 16, 0);//ԭ�� 5 10 0
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
		//�״����ݲ�ͬʱ�������Ӿ�����Ѱ��
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
				GetMotorVelocity_Self(-6, 0, 0); //ԭ��-4 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			}
			else if (Radar.Angle > VISION_MID + 20)
			{
				GetMotorVelocity_Self(6, 0, 0);//ԭ��4 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			}

			else if (Radar.Distance>700)
			{
				GetMotorVelocity_Self(0, 20, 0);
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			}

			else if (Radar.Angle< VISION_MID - 30)
			{
				GetMotorVelocity_Self(-6, 0, 0); //ԭ��-3 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);
			}
			else if (Radar.Angle > VISION_MID + 30)
			{
				GetMotorVelocity_Self(6, 0, 0);//ԭ�� 3 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}
			else if (Radar.Angle <= VISION_MID + 30 && Radar.Angle > VISION_MID + 10)
			{
				GetMotorVelocity_Self(3, 0, 0); //ԭ�� 1.5 0 0 
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}
			else if (Radar.Angle >= VISION_MID - 30 && Radar.Angle < VISION_MID - 10)
			{
				GetMotorVelocity_Self(-3, 0, 0);//ԭ��-1.5 0 0
				SetPWM('O', Robot.Velocity[0],Robot.Velocity[1], Robot.Velocity[2]);


			}
			else
			{
				SetPWM('S',0, 0, 0);
				SetPWM('Y', 0, 0, 0);	//�����źŸ���Ƭ���������½� Robot_armDown();
				GetMotorVelocity_Self(0, 7, 0);
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


				break;
			}
		}
	}



	if (Radar.Distance <= 800)
	{
		//LCD_ShowString(30 + 200, 500, 200, 16, 16, "Radar!");
		//�״�������ͬ�������״�����Ѱ��
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
				GetMotorVelocity_Self(-10, 0, 0);//ԭ��-10 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}
			else if ((Radar.Angle > RADAR_MID + 10) && Radar.Distance >700)
			{
				GetMotorVelocity_Self(10, 0, 0); //ԭ��10 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}
			else if (Radar.Distance>700)
			{
				GetMotorVelocity_Self(0, 20, 0); //ԭ�� 0 14 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}
			else if (Radar.Angle< RADAR_MID - 5)
			{
				GetMotorVelocity_Self(-10, 0, 0);//ԭ��-10 0 0
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1], Robot.Velocity[2]);


			}
			else if (Radar.Angle > RADAR_MID + 5)
			{
				GetMotorVelocity_Self(10, 0, 0);//ԭ��10 0 0
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
				SetPWM('Y', 0, 0, 0);	//�����źŸ���Ƭ���������½� Robot_armDown();
				GetMotorVelocity_Self(0, 7, 0);//ԭ��0 7 0 
				SetPWM('O',Robot.Velocity[0], Robot.Velocity[1],Robot.Velocity[2]);


				if (Radar.Distance < 350)
					break;
			}

		}
	}


	//��ȡ����״̬ GetInfraredState();
	while (1)
	{
		if (Robot.Infr)
			break;
	}	SetPWM('S',0, 0, 0);

	SetPWM('N', 0, 0, 0);	//���������� Robot_armUp();


}


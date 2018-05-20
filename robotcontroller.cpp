#include "robotcontroller.h"
#include "robot2018.h"
#include <QtMath>
#include <QGraphicsScene>
#include <QMessageBox>

char Data[7];

RobotController::RobotController(QGraphicsScene & scene, QObject *parent) :
	QObject(parent),
	scene(scene),
	pRobot(new Robot(*this))
{
}

RobotController::~RobotController()
{
}

/* robotInit
* 描述：robot初始化
* 输入：无
* 输出：无
*/
void RobotController::robotInit()
{
	switch (mapType) {
	case LeftMap:
		pRobot->setMapType(0);
		pRobot->setCoordinate(0, 0);
		pRobot->w[1] = 0;//第一个轮的角速度
		pRobot->w[2] = 0;//第二个轮的角速度
		pRobot->w[3] = 0;//第三个轮的角速度
		pRobot->v[1] = 0;//第一个轮的速度
		pRobot->v[2] = 0;//第二个轮的速度
		pRobot->v[0] = 0;//第三个轮的速度
		scene.addItem(pRobot);
		break;
	case RightMap:
		pRobot->setMapType(1);
		pRobot->setCoordinate(0, 0);
		pRobot->w[1] = 0;//第一个轮的角速度
		pRobot->w[2] = 0;//第二个轮的角速度
		pRobot->w[3] = 0;//第三个轮的角速度
		pRobot->v[1] = 0;//第一个轮的速度
		pRobot->v[2] = 0;//第二个轮的速度
		pRobot->v[0] = 0;//第三个轮的速度
		scene.addItem(pRobot);
		break;
	default:
		break;
	}
}

/* setMapType
* 描述：设置地图类型
* 输入：mapType - 0：左半场
*                1：右半场
* 输出：无
*/
void RobotController::setMapType(int mapType)
{
	switch (mapType) {
	case 0:
		this->mapType = LeftMap;
		break;
	case 1:
		this->mapType = RightMap;
		break;
	default:
		break;
	}
}

/* setRobotCoordinate
* 描述：设置robot坐标，给手动设置坐标提供接口
* 输入：x - X轴坐标
*      y - Y轴坐标
* 输出：无
*/
void RobotController::setRobotCoordinate(float x, float y, float theta)
{
	pRobot->setCoordinate(x, y, theta);
	scene.addItem(pRobot);
	scene.update();
}

/* setRobotSpeedFromArm
* 描述：通过串口获得10ms内运动，传递给robot类并显示
* 输入：x - x轴运动数据
*      y - y轴运动数据
*      theta - 自转运动数据
* 输出：无
*/
void RobotController::setRobotSpeedFromArm(float x, float y, float theta)
{
	float xOfCoordinate = pRobot->getXOfCoordinate();
	float yOfCoordinate = pRobot->getYOfCoordinate();
	float thetaOfCoordinate = pRobot->getTheta();

	xOfCoordinate += x;
	yOfCoordinate += y;
	thetaOfCoordinate += theta;

	while (thetaOfCoordinate > 360)
		thetaOfCoordinate -= 360;

	while (thetaOfCoordinate < 0)
		thetaOfCoordinate += 360;

	pRobot->setCoordinate(xOfCoordinate, yOfCoordinate, thetaOfCoordinate);
	scene.addItem(pRobot);
	scene.update();
}


void RobotController::getRobotCoordinate(float *x, float *y, float *theta)
{
	*x = pRobot->getXOfCoordinate();
	*y = pRobot->getYOfCoordinate();
	*theta = pRobot->getTheta();
}

/* robot_straight_stage
* 描述：直线行走,阶梯变速
* 输入：X_I - 目标坐标的X
*      Y_I - 目标坐标的Y
*      Theta_I - 目标坐标的角速度
* 输出：无
*/
void RobotController::robot_straight_stage(float X_I, float Y_I, float Theta_I)
{
	float D_Theta, D_X, D_Y, Vw = 0, sx, sy = 0;
	D_Theta = Theta_I / 180 * PI - pRobot->getTheta();
	D_X = X_I - pRobot->getXOfCoordinate();
	D_Y = Y_I - pRobot->getYOfCoordinate();
	while (qFabs(D_Y) > 0.05f || qFabs(D_X) > 0.05f)
	{
		if (D_Y > 0.05f)
		{

			if (D_Y >= 1.5f)
			{
				sy = 8;
				if (pRobot->Vy < 0.3f)
					sy = 2;
				else if (pRobot->Vy < 0.5f)
					sy = 4;
				else if (pRobot->Vy < 0.9f)
					sy = 6;
			}
			else
			{
				sy = 8;
			}
			if (D_Y < 1.5f) {
				sy = 6;
			}
			if (D_Y < 0.8f) {
				sy = 4;
			}
			if (D_Y < 0.3f) {
				sy = 2;
			}
			if (D_Y < 0.2f) {
				sy = 0.25;
			}

		}
		else if (D_Y < -0.05f)
		{
			if (D_Y < -1.5f)
			{
				sy = -8;
				if (pRobot->Vy > -0.3f)
					sy = -2;
				else if (pRobot->Vy > -0.5f)
					sy = -4;
				else if (pRobot->Vy> -0.9f)
					sy = -6;
			}
			else
			{
				sy = -8;
			}
			if (D_Y > -1.5f) {
				sy = -6;
			}
			if (D_Y > -0.8f) {
				sy = -4;
			}
			if (D_Y > -0.3f) {
				sy = -2;
			}
			if (D_Y > -0.2f) {
				sy = -0.25;
			}
		}
		else
			sy = 0;


		if (D_X > 0.05f)
		{
			if (D_X > 1.5f)
			{
				sx = 8;
				if (pRobot->Vx < 0.1f)
					sx = 0.5;
				else if (pRobot->Vx< 0.2f)
					sx = 1;
				else if (pRobot->Vx< 0.4f)
					sx = 2;
				else if (pRobot->Vx < 0.58f)
					sx = 4;
				else if (pRobot->Vx< 7.5f)
					sx = 6;
			}
			else if (D_X < 1.5f)
			{
				if (D_X > 0.2f)
				{
					sx = 2;
				}
				else if (D_X > 0.15f)
				{
					sx = 1;
				}
				else if (D_X > 0.1f)
				{
					sx = 0.5f;
				}
				else
					sx = 0.25f;
			}
		}
		else if (D_X < -0.05f)
		{
			if (D_X < -1.5f)
			{
				sx = -8;
				if (pRobot->Vx > -0.1f)
					sx = -0.5;
				else if (pRobot->Vx> -0.2f)
					sx = -1;
				else if (pRobot->Vx > -0.4f)
					sx = -2;
				else if (pRobot->Vx> -0.58f)
					sx = -4;
				else if (pRobot->Vx> -7.5f)
					sx = -6;
			}
			else if (D_X > -1.5f)
			{
				if (D_X < -0.2f)
				{
					sx = -2;
				}
				else if (D_X < -0.15f)
				{
					sx = -1;
				}
				else if (D_X < -0.1f)
				{
					sx = -0.5f;
				}
				else
					sx = -0.25f;
			}
		}
		else
			sx = 0;


		if (D_Theta>0 && (D_Theta<PI))
		{
			Vw = D_Theta * 500;
		}
		else if (D_Theta>0 && (D_Theta >= PI))
		{
			D_Theta = 2 * PI - D_Theta;
			Vw = -D_Theta * 500;
		}
		else if (D_Theta<0 && (D_Theta >= -PI))
		{
			D_Theta = -D_Theta;
			Vw = -D_Theta * 500;
		}
		else if (D_Theta<0 && (D_Theta<-PI))
		{
			D_Theta = 2 * PI + D_Theta;
			Vw = D_Theta * 500;
		}
		else
			Vw = Vw;

		//小于60°大于30°匀速
		//实际PWM为201
		if (D_Theta > 0.523599f)
		{
			if (Vw>0)
				Vw = 300;
			else
				Vw = -300;
		}

		//小于30°大于5° PWM40
		if (D_Theta < 0.523599f)
		{
			if (Vw>0)
				Vw = 150;
			else
				Vw = -150;
		}
		//小于5°	pwm8
		if (D_Theta < 0.0872665f)
		{
			if (Vw>0)
				Vw = 20;
			else
				Vw = -20;
		}
		set_motor_vx_vy_w(sx * 12, sy * 100, Vw);


		D_Theta = Theta_I / 180 * PI - pRobot->getTheta();
		D_X = X_I - pRobot->getXOfCoordinate();
		D_Y = Y_I - pRobot->getYOfCoordinate();
		Data[0] = 0xA5;
		Data[1] = 0x5A;
		Data[2] = 0x01;
		Data[3] = (int)control1_W(pRobot->pwm[0]);
		Data[4] = (int)control2_W(pRobot->pwm[1]);
		Data[5] = (int)control3_W(pRobot->pwm[2]);
		//Data[6] = Data[3] + Data[4] + Data[5];

	}
	control1_W(0);
	control2_W(0);
	control3_W(0);
	robot_turnOrigin_stage(Theta_I);



}

/* 描述:球场坐标速度转轮子的PWM
* 输入:vx球场坐标的x轴速度
*     vy球场坐标的y轴速度
*     w机器人原地旋转的角速度
* 输出:无
* 注意最大速度
*/


void RobotController::set_motor_vx_vy_w(float vx, float vy, float w)
{
	int i, j, k;
	float L[3][3];
	float theta[3][3];
	float V[3][1];
	float tem[3][3];

	//v(PWM)=L*Theta*V
	//   cos(60)	sin(60)		-MOTOR_L
	//L= cos(180) 	sin(180)	-MOTOR_L
	//   cos(-60)	sin(-60)	-MOTOR_L
	L[0][0] = 0.5;					L[0][1] = 0.8660254037844386;		L[0][2] = -MOTOR_L;
	L[1][0] = -1;					L[1][1] = 0;				L[1][2] = -MOTOR_L;
	L[2][0] = 0.5;					L[2][1] = -0.8660254037844386;		L[2][2] = -MOTOR_L;
	//cos(theta)		sin(theta)	0
	//theta= -sin(theta)	cos(theta) 	0
	//		 0				0			1
	theta[0][0] = qCos(pRobot->getTheta());     theta[0][1] = qSin(pRobot->getTheta());	theta[0][2] = 0;
	theta[1][0] = -qSin(pRobot->getTheta());    theta[1][1] = qCos(pRobot->getTheta());	theta[1][2] = 0;
	theta[2][0] = 0;                            theta[2][1] = 0;                         theta[2][2] = 1;
	//V
	V[0][0] = -vx * 10;
	V[1][0] = -vy;
	V[2][0] = -w;

	for (i = 0; i<3; i++)
	{
		for (j = 0; j<3; j++)
		{
			tem[i][j] = 0;
			for (k = 0; k<3; k++)
			{
				tem[i][j] += L[i][k] * theta[k][j];
			}
		}
	}

	for (i = 0; i<3; i++)
	{
		pRobot->pwm[i] = 0;
		for (j = 0; j<3; j++)
		{
			pRobot->pwm[i] += tem[i][j] * V[j][0];
		}
	}

	/*
	for(i = 0;i<3;i++)
	{
	if(pRobot->pwm[i] > 700 || pRobot->pwm[i] < -700)
	{
	pRobot->pwm[0] = pRobot->pwm[0] * 700 /pRobot->pwm[i];
	pRobot->pwm[1] = pRobot->pwm[1] * 700 /pRobot->pwm[i];
	pRobot->pwm[2] = pRobot->pwm[2] * 700 /pRobot->pwm[i];

	}
	}
	*/
}

//电机1转速
float RobotController::control1_W(float W)
{
	W = 1000 - W;//W+=1000;
	if (W >= 1900)
		W = 1900;
	if (W <= 100)
		W = 100; 				//PC6
	W = W / 10;
	return W;

}
//电机2转速
float  RobotController::control2_W(float W)
{
	W = 1000 - W;//W+=1000;
	if (W >= 1900)
		W = 1900;
	if (W <= 100)
		W = 100;
	W = W / 10;
	return W;			//PC7

}
//电机3转速
float  RobotController::control3_W(float W)
{
	W = 1000 - W;//W+=1000;
	if (W >= 1900)
		W = 1900;
	if (W <= 100)
		W = 100;
	W = W / 10;
	return W;			//PC8
}
//自旋运动 根据误差角度 自动调节
void RobotController::robot_turnOrigin_stage(float theta)
{
	float D_Theta, Vw = 0;     //W大于0 逆时针
	theta = theta / 180.0f*PI;
	D_Theta = theta - pRobot->getTheta();

	// 大于30° 线性控制
	if (D_Theta>0 && (D_Theta<PI))
	{
		Vw = D_Theta * 500;
	}
	else if (D_Theta>0 && (D_Theta >= PI))
	{
		D_Theta = 2 * PI - D_Theta;
		Vw = -D_Theta * 500;
	}
	else if (D_Theta<0 && (D_Theta >= -PI))
	{
		D_Theta = -D_Theta;
		Vw = -D_Theta * 500;
	}
	else if (D_Theta<0 && (D_Theta<-PI))
	{
		D_Theta = 2 * PI + D_Theta;
		Vw = D_Theta * 500;
	}
	else
		Vw = Vw;

	//小于60°大于30°匀速
	//实际PWM为100
	if (D_Theta < 2.0944f)
	{
		if (Vw>0)
			Vw = 1000;
		else
			Vw = -1000;
	}

	//小于30°大于5°
	if (D_Theta < 0.523599f)
	{
		if (Vw>0)
			Vw = 200;
		else
			Vw = -200;
	}
	//小于5°
	if (D_Theta < 0.0872665f)
	{
		if (Vw>0)
			Vw = 40;
		else
			Vw = -40;
	}

	while (D_Theta>0.015f) {
		set_motor_vx_vy_w(0, 0, Vw);
		Data[0] = 0xA5;
		Data[1] = 0x5A;
		Data[2] = 0x02;
		Data[3] = (int)control1_W(pRobot->pwm[0]);
		Data[4] = (int)control2_W(pRobot->pwm[1]);
		Data[5] = (int)control3_W(pRobot->pwm[2]);

		D_Theta = theta - pRobot->getTheta();
		//大于30°线性控制
		if (D_Theta>0 && (D_Theta<PI))
		{
			Vw = D_Theta * 500;
		}
		else if (D_Theta>0 && (D_Theta >= PI))
		{
			D_Theta = 2 * PI - D_Theta;
			Vw = -D_Theta * 500;
		}
		else if (D_Theta<0 && (D_Theta >= -PI))
		{
			D_Theta = -D_Theta;
			Vw = -D_Theta * 500;
		}
		else if (D_Theta<0 && (D_Theta<-PI))
		{
			D_Theta = 2 * PI + D_Theta;
			Vw = D_Theta * 500;
		}
		else
			Vw = Vw;

		//小于60°大于30°匀速
		//实际PWM为201
		if (D_Theta < 2.0944f)
		{
			if (Vw>0)
				Vw = 1000;
			else
				Vw = -1000;
		}

		//小于30°大于5°	PWM40
		if (D_Theta < 0.523599f)
		{
			if (Vw>0)
				Vw = 200;
			else
				Vw = -200;
		}
		//小于5°	pwm8
		if (D_Theta < 0.0872665f)
		{
			if (Vw>0)
				Vw = 40;
			else
				Vw = -40;
		}
	}
	control1_W(0);
	control2_W(0);
	control3_W(0);
	set_motor_vx_vy_w(0, 0, 0);
	while (pRobot->W);
}

void RobotController::get_position()
{


	//根据速度运算球场坐标
	int i, j, k;
	float theta;
	float L_inv[3][3];
	float theta_inv[3][3];
	float tem[3][3];

	//取Theta采样中值
	if (qFabs(pRobot->getTheta() - pRobot->theta_dev < PI))
		theta = (pRobot->getTheta() + pRobot->theta_dev) / 2.0f;
	else
		theta = (pRobot->getTheta() + pRobot->theta_dev) / 2.0f + PI;
	pRobot->theta_dev = pRobot->getTheta();

	//v(bmq)=L * Theta * V
	//theta_inv
	theta_inv[0][0] = qCos(theta);	theta_inv[0][1] = -qSin(theta);		theta_inv[0][2] = 0;
	theta_inv[1][0] = qSin(theta);	theta_inv[1][1] = qCos(theta);		theta_inv[1][2] = 0;
	theta_inv[2][0] = 0;		theta_inv[2][1] = 0;			theta_inv[2][2] = 1;
	//		[-cos(0)	-sin(0)		BMQ_L]-1
	//L_inv=[-cos(120) 	-sin(120)	BMQ_L]
	//		[-cos(-120)	-sin(-120)	BMQ_L]
	L_inv[0][0] = -0.666666666666667;		L_inv[0][1] = 0.333333333333333;		L_inv[0][2] = 0.333333333333333;
	L_inv[1][0] = 0;				L_inv[1][1] = -0.577350269189626;		L_inv[1][2] = 0.577350269189626;
	L_inv[2][0] = 1.666666666666667;		L_inv[2][1] = 1.666666666666667;		L_inv[2][2] = 1.666666666666667;

	for (i = 0; i<3; i++)
	{
		for (j = 0; j<3; j++)
		{
			tem[i][j] = 0;
			for (k = 0; k<3; k++)
			{
				tem[i][j] += theta_inv[i][k] * L_inv[k][j];
			}
		}
	}

	pRobot->Vx = 0;
	for (j = 0; j<3; j++) {
		pRobot->Vx += tem[0][j] * pRobot->v[j];
	}
	pRobot->Vy = 0;
	for (j = 0; j<3; j++) {
		pRobot->Vy += tem[1][j] * pRobot->v[j];
	}
	pRobot->W = 0;
	for (j = 0; j<3; j++) {
		pRobot->W += tem[2][j] * pRobot->v[j];
	}

	pRobot->setCoordinateX(pRobot->getXOfCoordinate() + pRobot->Vx*0.01f);
	pRobot->setCoordinateY(pRobot->getYOfCoordinate() + pRobot->Vy*0.01f);

	/*
	//根据里程计计算角度
	//用陀螺仪代替
	robot_zqd.theta += robot_zqd.W*0.01f;

	while(robot_zqd.theta<0)
	{
	robot_zqd.theta += 2*PI;
	}
	while(robot_zqd.theta > 2*PI)
	{
	robot_zqd.theta -= 2*PI;
	}
	*/




	/*
	//根据里程计累计值运算球场坐标
	u8 i,j,k;
	float L_inv[3][3];
	float theta_inv[3][3];
	float tem[3][3];
	//L*theta*V=R*w
	//theta_inv
	theta_inv[0][0]= 1;		theta_inv[0][1] = 0;		theta_inv[0][2] = 0;
	theta_inv[1][0]= 0;		theta_inv[1][1] = 1;		theta_inv[1][2] = 0;
	theta_inv[2][0]= 0;		theta_inv[2][1] = 0;		theta_inv[2][2] = 1;
	//L_inv

	L_inv[0][0] = -0.666666666666667;		L_inv[0][1] =  0.333333333333333;		L_inv[0][2] = 0.333333333333333;
	L_inv[1][0] =  0;						L_inv[1][1] = -0.577350269189626;		L_inv[1][2] = 0.577350269189626;
	L_inv[2][0] =  1.877934272300470;		L_inv[2][1] =  1.877934272300470;		L_inv[2][2] = 1.877934272300470;

	//L_inv[0][0] = -0.691823899371069;		L_inv[0][1] =  0.345911949685535;		L_inv[0][2] = 0.345911949685535;
	//L_inv[1][0] =  0;						L_inv[1][1] = -0.558469178636527;		L_inv[1][2] = 0.558469178636527;
	//L_inv[2][0] =  1.736203383824963;		L_inv[2][1] =  1.948799716538223;		L_inv[2][2] = 1.948799716538223;

	for(i=0;i<3;i++)
	{
	for(j=0;j<3;j++)
	{
	tem[i][j] = 0;
	for(k=0;k<3;k++)
	{
	tem[i][j] += theta_inv[i][k] * L_inv[k][j];
	}
	}
	}

	robot_zqd.X = 0;
	for(j=0;j<3;j++){
	robot_zqd.X += tem[0][j] * robot_zqd.w[j]*0.0001727875959474386f;
	}
	robot_zqd.Y = 0;
	for(j=0;j<3;j++){
	robot_zqd.Y += tem[1][j] * robot_zqd.w[j]*0.0001727875959474386f;
	}
	robot_zqd.Y *= 1.123f;
	robot_zqd.theta = 0;
	for(j=0;j<3;j++){
	robot_zqd.theta += tem[2][j] * robot_zqd.w[j]*0.0001727875959474386f;
	}
	robot_zqd.theta *= 1.14f;

	while(robot_zqd.theta<0)
	{
	robot_zqd.theta += 2*PI;
	}
	while(robot_zqd.theta > 2*PI)
	{
	robot_zqd.theta -= 2*PI;
	}
	*/
	/*
	//ºÏ
	u8 i;
	float L_inv[3][3];

	//L_inv
	L_inv[0][0] = -0.666666666666667;		L_inv[0][1] =  0.333333333333333;		L_inv[0][2] = 0.333333333333333;
	L_inv[1][0] =  0;						L_inv[1][1] = -0.577350269189626;		L_inv[1][2] = 0.577350269189626;
	L_inv[2][0] =  1.877934272300470;		L_inv[2][1] =  1.877934272300470;		L_inv[2][2] = 1.877934272300470;

	robot_zqd.X = 0;
	for(i=0;i<3;i++){
	robot_zqd.X += L_inv[0][i] * robot_zqd.w[i]*0.0001727875959474386f;
	}
	robot_zqd.X *= 1.123f;
	robot_zqd.Y = 0;
	for(i=0;i<3;i++){
	robot_zqd.Y += L_inv[1][i] * robot_zqd.w[i]*0.0001727875959474386f;
	}

	robot_zqd.W = 0;
	for(i=0;i<3;i++){
	robot_zqd.W += L_inv[2][i] * robot_zqd.v[i];
	}
	robot_zqd.theta += robot_zqd.W*0.01f;

	while(robot_zqd.theta<0)
	{
	robot_zqd.theta += 2*PI;
	}
	while(robot_zqd.theta > 2*PI)
	{
	robot_zqd.theta -= 2*PI;
	}
	*/

}

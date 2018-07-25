#include "robot.h"

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

//	uartSendCommand('r', Radar.Angle, Radar.Angle, 0);
}

void robot::setVisionData(float _depth, float _x)
{
	Vison.Depth = _depth;
	Vison.X = _x;
	Vison.State = true;
}

void robot::setRobotV(float _x, float _y, float _yaw)
{
	Vx = _x;
	Vy = _y;
	W = _yaw;
}

/*��λ������λ������Э�飨����Ϊ��������PWM��
*	��ʼ1	��ʼ2	������	����1	����1	����2	����2	����3	����3	У���
*	@(0x40) ^(0x5E)	cmd		H1		L2		H2		L2		H3		L3		sum
* SUM = 0x40 + 0x5E + cmd + H1 + L1 + H2 + L2 + H3 + L3
*  cod:
*		r �״�
*		v pwm��
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


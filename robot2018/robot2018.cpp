#include "robot2018.h"


Robot::Robot(RobotController &controller) :
	controller(controller)
{
	xOfCoordinate = 0;
	yOfCoordinate = 0;
	xOfMap = 0;
	yOfMap = 0;
}

Robot::~Robot()
{

}

/* shape
* �������̳��Ը��࣬�����ิд��Ԫ�����,����60cm����
* ���룺��
* �����Ԫ��·��
*/
QPainterPath Robot::shape() const
{
	QPainterPath path;
	//����ڻ���ԭ�㣬��-15��-15��λ��Ϊ���Ͻǣ�����30
	path.moveTo(-7.5, -12.99);
	path.arcTo(-15, -15, 30, 30, 120, 300);
	//path.addRect(QRectF(-15,-15,30,30));

	return path;
}

/* paint
* �������̳��Ը��࣬������ʵ������д
* ���룺
* �������
*/
void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->save();
	//painterԭ���ƶ�������������λ��
	painter->translate(xOfMap, yOfMap);
	//�Ի����������谲װ
	painter->rotate(theta);
	//���û��������ɫ
	painter->fillPath(shape(), Qt::yellow);
	painter->restore();
}

/* boundingRect
* �������̳��Ը��࣬�����ิд���궨Ԫ�ط�Χ����100cm����
* ���룺��
* �������
*/
QRectF Robot::boundingRect() const
{
	QRectF bound = QRectF(xOfMap, yOfMap, 50, 50);

	return bound;
}

/* setPosition
* �������趨robot����λ�ã���λm
* ���룺x - X��λ��
*      y - Y��λ��
* �������
*/
void Robot::setCoordinate(float x, float y, float theta)
{
	this->xOfCoordinate = x;
	this->yOfCoordinate = y;
	this->theta = theta;

	xOfMap = centerXOfMap + x * 50;
	yOfMap = centerYOfMap - y * 50;
}

void Robot::setCoordinateX(float x)
{
	this->xOfCoordinate = x;
}

void Robot::setCoordinateY(float y)
{
	this->yOfCoordinate = y;
}

void Robot::setCoordinateTheta(float theta)
{
	this->theta = theta;
}
/* setMapType
* ����������������
* ���룺mapType - 0����볡
*                1���Ұ볡
* �������
*/
void Robot::setMapType(int mapType)
{
	this->mapType = mapType;
	switch (mapType) {
	case 0:
		centerXOfMap = 635;
		centerYOfMap = 510;
		break;
	case 1:
		centerXOfMap = 85;
		centerYOfMap = 510;
		break;
	default:
		break;
	}
}

float Robot::getXOfCoordinate()
{
	return xOfCoordinate;
}

float Robot::getYOfCoordinate()
{
	return yOfCoordinate;
}

float Robot::getTheta()
{
	return theta;
}

/*
* float Robot::getSpeedx()
{
return Vx;
}

float Robot::getSpeedy()
{
return Vy;
}

float Robot::getSpeedw()
{
return W;
}

float Robot::getTheta_dev()
{
return theta_dev;
}

float Robot::getTheta_offset()
{
return theta_offset;
}
*/


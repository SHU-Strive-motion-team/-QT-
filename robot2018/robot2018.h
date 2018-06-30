#pragma once
#ifndef ROBOT2018_H
#define ROBOT2018_H


#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include "robotcontroller.h"

class RobotController;

class Robot : public QGraphicsItem
{
public:
	Robot(RobotController &controller);
	~Robot();
	QPainterPath shape() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
	QRectF boundingRect() const;
	void setCoordinate(float x = 0, float y = 0, float theta = 0);        //�������꣬��λm
	void setCoordinateX(float x);
	void setCoordinateY(float y);
	void setCoordinateTheta(float theta);
	void setMapType(int mapType);               //����������
	float getXOfCoordinate();
	float getYOfCoordinate();
	float getTheta();
	//  float getSpeedx();
	//  float getSpeedy();
	//  float getSpeedw();
	//  float getTheta_dev();
	//  float getTheta_offset();
	float pwm[3];       //���ӵ�pwm
	float w[3];		//��������ʵ�ʼ���/4
	float v[3];		//���������ٶ�
	float Vx = 0;		//������������ϵx������ٶ�
	float Vy = 0;		//������������ϵy������ٶ�
	float W = 0;		//�����˽��ٶ�,˳ʱ�뷽��
	float theta_dev = 0;	//��һʱ�̻�����theta��
	float theta_offset = 0;	//�Ƕ�ƫ�����

private:
	float xOfMap;           //����
	float yOfMap;
	float theta;
	float xOfCoordinate;    //����
	float yOfCoordinate;



	float centerYOfMap;     //��ʼλ������
	float centerXOfMap;
	int mapType;            //�����ͣ�0-��볡��1-�Ұ볡
	RobotController &controller;
};

#endif // ROBOT_H

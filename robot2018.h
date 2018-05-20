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
	void setCoordinate(float x = 0, float y = 0, float theta = 0);        //设置坐标，单位m
	void setCoordinateX(float x);
	void setCoordinateY(float y);
	void setCoordinateTheta(float theta);
	void setMapType(int mapType);               //设置球场类型
	float getXOfCoordinate();
	float getYOfCoordinate();
	float getTheta();
	//  float getSpeedx();
	//  float getSpeedy();
	//  float getSpeedw();
	//  float getTheta_dev();
	//  float getTheta_offset();
	float pwm[3];       //轮子的pwm
	float w[3];		//编码器的实际计数/4
	float v[3];		//编码器的速度
	float Vx = 0;		//机器人在坐标系x方向的速度
	float Vy = 0;		//机器人在坐标系y方向的速度
	float W = 0;		//机器人角速度,顺时针方向
	float theta_dev = 0;	//上一时刻机器人theta角
	float theta_offset = 0;	//角度偏差矫正

private:
	float xOfMap;           //像素
	float yOfMap;
	float theta;
	float xOfCoordinate;    //坐标
	float yOfCoordinate;



	float centerYOfMap;     //起始位置像素
	float centerXOfMap;
	int mapType;            //球场类型，0-左半场，1-右半场
	RobotController &controller;
};

#endif // ROBOT_H

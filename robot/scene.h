#pragma once

#include <QWidget>

typedef enum
{
	Right = 0,
	Left
}MAP;


class scene : public QWidget
{
	Q_OBJECT

public:
	scene(QWidget *parent);
	~scene();

	typedef enum
	{
		Right = 0,
		Left,
		CLear
	}MAP;

	void showMap(MAP map);

	void showMapLeft();

	void showMapRight();

	

protected:
	void paintEvent(QPaintEvent *event);    //»æÖÆÊÂ¼þ

private:
	MAP map;

};

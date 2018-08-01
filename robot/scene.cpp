#include "scene.h"
#include <QPainter>

scene::scene(QWidget *parent)
	: QWidget(parent)
{
	/*QPainter painter(this);
	painter.fillRect(rect(), QColor(Qt::gray));*/
}

scene::~scene()
{
}

void scene::showMap(MAP _map)
{
	
	map = _map;

	update();
}

void scene::showMapLeft()
{
	//QPainter painter(this);
	////设置背景色
	//painter.setPen(Qt::gray);
	//painter.setBrush(Qt::gray);
	//painter.drawRect(0, 0, 720, 545);
	QPainter painter(this);
	painter.fillRect(rect(), QColor(Qt::gray));

	//设置线条颜色
	painter.setPen(Qt::black);
	painter.setBrush(Qt::transparent);

	//绘制球场边界
	QPainterPath groundPath;
	groundPath.moveTo(710, 110);
	groundPath.lineTo(10, 110);
	groundPath.lineTo(10, 485);
	groundPath.lineTo(710, 485);
	groundPath.moveTo(660, 485);
	groundPath.lineTo(660, 535);
	groundPath.lineTo(610, 535);
	groundPath.lineTo(610, 485);
	groundPath.moveTo(710, 485);
	groundPath.lineTo(710, 110);
	groundPath.moveTo(10, 110);
	groundPath.lineTo(10, 10);
	painter.drawPath(groundPath);

	//中圈线
	QPainterPath centerPath;
	centerPath.moveTo(620, 110);
	centerPath.arcTo(620, 20, 180, 180, 180, 90);
	centerPath.moveTo(580, 110);
	centerPath.arcTo(580, -20, 260, 260, 180, 90);
	centerPath.moveTo(540, 110);
	centerPath.arcTo(540, -60, 340, 340, 180, 90);
	painter.drawPath(centerPath);

	//三分线
	QPainterPath threePath;
	threePath.moveTo(10, 437.5);
	threePath.lineTo(173.1, 437.5);
	threePath.arcTo(-248.75, -227.5, 675, 675, 284, 166);
	painter.drawPath(threePath);

	//罚球线
	QPainterPath freeThrowPath;
	freeThrowPath.moveTo(210, 110);
	freeThrowPath.arcTo(210, 20, 180, 180, 180, 360);
	painter.drawPath(freeThrowPath);

	//投篮边线
	QPainterPath basketLinePath;
	basketLinePath.moveTo(10, 171.64);
	basketLinePath.arcTo(-11.25, 10, 200, 200, 218, 284);
	painter.drawPath(basketLinePath);

	//底线置球位
	QPainterPath endBallPath;
	endBallPath.moveTo(97.5, 460);
	endBallPath.lineTo(60, 460);
	painter.drawPath(endBallPath);

	//篮筐
	QPainterPath basketPath;
	basketPath.moveTo(88.75, 85);
	basketPath.lineTo(88.75, 135);
	painter.setPen(Qt::red);
	painter.drawPath(basketPath);
}

void scene::showMapRight()
{
	QPainter painter(this);
	painter.fillRect(rect(), QColor(Qt::gray));

	//绘制球场边界
	QPainterPath groundPath;
	groundPath.moveTo(10, 110);
	groundPath.lineTo(710, 110);
	groundPath.lineTo(710, 485);
	groundPath.lineTo(10, 485);
	groundPath.lineTo(10, 110);

	groundPath.moveTo(60, 485);
	groundPath.lineTo(60, 535);
	groundPath.lineTo(110, 535);
	groundPath.lineTo(110, 485);

	groundPath.moveTo(60, 110);
	groundPath.lineTo(60, 60);
	groundPath.lineTo(110, 60);
	groundPath.lineTo(110, 110);

	groundPath.moveTo(235, 110);
	groundPath.lineTo(235, 110 + 37.5);
	groundPath.lineTo(235 + 125, 110 + 37.5);
	groundPath.lineTo(235 + 125, 110);

	groundPath.moveTo(235, 485);
	groundPath.lineTo(235, 485 - 37.5);
	groundPath.lineTo(235 + 125, 485 - 37.5);
	groundPath.lineTo(235 + 125, 485);

	painter.drawPath(groundPath);

	//中圈线
	QPainterPath centerPath;
	centerPath.moveTo(235, 147.5);
	centerPath.arcTo(10, 147.5, 250, 250, 0, 360);
	painter.drawPath(centerPath);

	//三分线
	QPainterPath threePath;
	threePath.moveTo(631.25, -227.5);
	threePath.arcTo(293.75, -227.5, 675, 675, 90, 166);
	threePath.lineTo(710, 437.5);
	painter.drawPath(threePath);

	//罚球线
	QPainterPath freeThrowPath;
	freeThrowPath.moveTo(330, 110);
	freeThrowPath.arcTo(330, 20, 180, 180, 180, 360);
	painter.drawPath(freeThrowPath);

	//投篮边线
	QPainterPath basketLinePath;
	basketLinePath.moveTo(710, 48.36);
	basketLinePath.arcTo(531.25, 10, 200, 200, 38, 284);
	painter.drawPath(basketLinePath);

	//底线置球位
	QPainterPath endBallPath;
	endBallPath.moveTo(622.5, 460);
	endBallPath.lineTo(660, 460);
	painter.drawPath(endBallPath);

	//篮筐
	QPainterPath basketPath;
	basketPath.moveTo(631.25, 85);
	basketPath.lineTo(631.25, 135);
	painter.setPen(Qt::red);
	painter.drawPath(basketPath);

}

void scene::paintEvent(QPaintEvent * event)
{
	switch (map)
	{
	case Right:
		showMapRight();
		break;
	case Left:
		showMapLeft();
		break;
	case CLear:
	{
		QPainter painter(this);
		painter.fillRect(rect(), QColor(Qt::gray));
		break;
	}

	default:
		break;
	}

}

#pragma once

#include <QObject>

class robot : public QObject
{
	Q_OBJECT

public:
	robot(QObject *parent);
	~robot();
};

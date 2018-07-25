#include "MyMainWindow.h"

//#include "cradar.h"

MyMainWindow::MyMainWindow(QWidget *parent)
	: QMainWindow(parent),
	scene(new QGraphicsScene(this)),
	view(new QGraphicsView(scene, this))
{
	ui.setupUi(this);

	currentSerialPort = new QSerialPort(this);
	uartReceive = new Receive(currentSerialPort);
	receiveThread = new QThread(this);
	uartReceive->moveToThread(receiveThread);
	
	bRobot = new robot(currentSerialPort);

	robotRadar = new radar(bRobot, ui.widget_radar);
	radarThread = new QThread(this);
	robotRadar->moveToThread(radarThread);
	ui.widget_radar->moveToThread(radarThread);

	//��ʾ����
	showTimerId = startTimer(200);

	showMapInit();
	uartInit();
	qDebug() << QThread::currentThread() << endl;
	//���ڽ��ճɹ�����ʾ��Ϣ
	connect(uartReceive, &Receive::RecSuccess, this, &MyMainWindow::robotDataUpdate);
	//�״￪ʼ
	connect(this, &MyMainWindow::startRadar, robotRadar, &radar::startScan);
	//�״ﱨ��
	connect(robotRadar, &radar::reportError, this, [this](QString err) {QMessageBox::critical(this, tr("Error"), err); });
	//�״��ͼ
	//connect(robotRadar, &radar::completeScan, ui.widget_radar, &CRadar::showUpdate);
	//���ڹرպ�ֹͣ�߳�
	connect(this, &QObject::destroyed, this, &MyMainWindow::stopThread);
}

MyMainWindow::~MyMainWindow(void)
{
	currentSerialPort->deleteLater();
	uartReceive->deleteLater();
	receiveThread->deleteLater();
	bRobot->deleteLater();
	robotRadar->deleteLater();
	uartReceive->deleteLater();
}

void MyMainWindow::timerEvent(QTimerEvent * event)
{
	if (showTimerId == event->timerId())
	{
		showRobotData();
		//uartSendCommand('r', bRobot->Radar.Angle, bRobot->Radar.Distance, 0);
	}
}
//���ڳ�ʼ��
void MyMainWindow::uartInit(void)
{
	currentUartState = UartState::OFF;
	radarUartState = UartState::OFF;
	/* ���е�ǰ���õĴ��� */
	ui.comboBox_com->clear();
	ui.comboBox_com_radar->clear();
	foreach(auto const &info, QSerialPortInfo::availablePorts())
	{
		ui.comboBox_com->addItem(info.portName() + ": " + info.description());
		ui.comboBox_com_radar->addItem(info.portName() + ": " + info.description());
	}

	ui.comboBox_com->setCurrentIndex(0);
	ui.comboBox_com->setToolTip(ui.comboBox_com->currentText());

	ui.comboBox_com_radar->setCurrentIndex(0);
	ui.comboBox_com_radar->setToolTip(ui.comboBox_com->currentText());
}

void MyMainWindow::showMapInit()
{
	//Ĭ�����Ͻ�
	view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	view->setFixedSize(725, 550);
	//�����������view
	ui.horizontalLayout_11->addWidget(view);
	//����scene��С
	scene->setSceneRect(0, 0, 720, 545);
	//����view����
	pixmap = new QPixmap(720, 545);
	QPainter p(pixmap);
	p.setBrush(QBrush(Qt::gray));
	p.drawRect(0, 0, 720, 545);
	view->setBackgroundBrush(QBrush(*pixmap));
}

void MyMainWindow::showMapLeft()
{
	//�������pixmap
	QPixmap *pPixmap;
	pPixmap = pixmap;
	pixmap = new QPixmap(720, 545);
	pPixmap->~QPixmap();

	QPainter painter(pixmap);
	//���ñ���ɫ
	painter.setPen(Qt::gray);
	painter.setBrush(Qt::gray);
	painter.drawRect(0, 0, 720, 545);

	//����������ɫ
	painter.setPen(Qt::black);
	painter.setBrush(Qt::transparent);

	//�����򳡱߽�
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

	//��Ȧ��
	QPainterPath centerPath;
	centerPath.moveTo(620, 110);
	centerPath.arcTo(620, 20, 180, 180, 180, 90);
	centerPath.moveTo(580, 110);
	centerPath.arcTo(580, -20, 260, 260, 180, 90);
	centerPath.moveTo(540, 110);
	centerPath.arcTo(540, -60, 340, 340, 180, 90);
	painter.drawPath(centerPath);

	//������
	QPainterPath threePath;
	threePath.moveTo(10, 437.5);
	threePath.lineTo(173.1, 437.5);
	threePath.arcTo(-248.75, -227.5, 675, 675, 284, 166);
	painter.drawPath(threePath);

	//������
	QPainterPath freeThrowPath;
	freeThrowPath.moveTo(210, 110);
	freeThrowPath.arcTo(210, 20, 180, 180, 180, 360);
	painter.drawPath(freeThrowPath);

	//Ͷ������
	QPainterPath basketLinePath;
	basketLinePath.moveTo(10, 171.64);
	basketLinePath.arcTo(-11.25, 10, 200, 200, 218, 284);
	painter.drawPath(basketLinePath);

	//��������λ
	QPainterPath endBallPath;
	endBallPath.moveTo(97.5, 460);
	endBallPath.lineTo(60, 460);
	painter.drawPath(endBallPath);

	//����
	QPainterPath basketPath;
	basketPath.moveTo(88.75, 85);
	basketPath.lineTo(88.75, 135);
	painter.setPen(Qt::red);
	painter.drawPath(basketPath);


	view->setBackgroundBrush(QBrush(*pixmap));
}

void MyMainWindow::showMapRight()
{
	//�������pixmap
	QPixmap *pPixmap;
	pPixmap = pixmap;
	pixmap = new QPixmap(720, 545);
	pPixmap->~QPixmap();

	QPainter painter(pixmap);
	//���ñ���ɫ
	painter.setPen(Qt::gray);
	painter.setBrush(Qt::gray);
	painter.drawRect(0, 0, 720, 545);

	//����������ɫ
	painter.setPen(Qt::black);
	painter.setBrush(Qt::transparent);

	//�����򳡱߽�
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

	//��Ȧ��
	QPainterPath centerPath;
	centerPath.moveTo(235, 147.5);
	centerPath.arcTo(10, 147.5, 250, 250, 0, 360);
	painter.drawPath(centerPath);

	//������
	QPainterPath threePath;
	threePath.moveTo(631.25, -227.5);
	threePath.arcTo(293.75, -227.5, 675, 675, 90, 166);
	threePath.lineTo(710, 437.5);
	painter.drawPath(threePath);

	//������
	QPainterPath freeThrowPath;
	freeThrowPath.moveTo(330, 110);
	freeThrowPath.arcTo(330, 20, 180, 180, 180, 360);
	painter.drawPath(freeThrowPath);

	//Ͷ������
	QPainterPath basketLinePath;
	basketLinePath.moveTo(710, 48.36);
	basketLinePath.arcTo(531.25, 10, 200, 200, 38, 284);
	painter.drawPath(basketLinePath);

	//��������λ
	QPainterPath endBallPath;
	endBallPath.moveTo(622.5, 460);
	endBallPath.lineTo(660, 460);
	painter.drawPath(endBallPath);

	//����
	QPainterPath basketPath;
	basketPath.moveTo(631.25, 85);
	basketPath.lineTo(631.25, 135);
	painter.setPen(Qt::red);
	painter.drawPath(basketPath);


	view->setBackgroundBrush(QBrush(*pixmap));
}

void MyMainWindow::showRobotData()
{
	ui.lineEdit_m1->setText(QString::number(bRobot->v[0]));
	ui.lineEdit_m2->setText(QString::number(bRobot->v[1]));
	ui.lineEdit_m3->setText(QString::number(bRobot->v[2]));

	ui.lineEdit_pwm1->setText(QString::number(bRobot->v[0]));
	ui.lineEdit_pwm2->setText(QString::number(bRobot->v[1]));
	ui.lineEdit_pwm3->setText(QString::number(bRobot->v[2]));

	ui.lineEdit_x->setText(QString::number(bRobot->X));
	ui.lineEdit_y->setText(QString::number(bRobot->Y));
	ui.lineEdit_row->setText(QString::number(bRobot->ThetaD));

	ui.lineEdit_Vx->setText(QString::number(bRobot->Vx));
	ui.lineEdit_Vy->setText(QString::number(bRobot->Vy));
	ui.lineEdit_Vw->setText(QString::number(bRobot->W));

	ui.lineEdit_radar_angle->setText(QString::number(bRobot->Radar.Angle));
	ui.lineEdit_radar_d->setText(QString::number(bRobot->Radar.Distance));

}


/*��λ������λ������Э�飨����Ϊ��������PWM��
*	��ʼ1	��ʼ2	������	����1	����1	����2	����2	����3	����3	У���
*	@(0x40) ^(0x5E)	cmd		H1		L2		H2		L2		H3		L3		sum
* SUM = 0x40 + 0x5E + cmd + H1 + L1 + H2 + L2 + H3 + L3
*/
//void MyMainWindow::uartSendCommand(char cmd, int pwm1, int pwm2, int pwm3)
//{
//	char sendData[10];
//	sendData[0] = '@';
//	sendData[1] = '^';
//	sendData[2] = cmd;
//	sendData[3] = (pwm1>>8) & 0xff;
//	sendData[4] = pwm1 & 0xff;
//	sendData[5] = (pwm2 >> 8) & 0xff;
//	sendData[6] = pwm2 & 0xff;
//	sendData[7] = (pwm2 >> 8) & 0xff;
//	sendData[8] = pwm3 & 0xff;
//	sendData[9] = 0;
//	for (int i = 0; i < 9; i++)
//		sendData[9] += sendData[i];
//	qDebug() << int(sendData[9]) << endl;
//	currentSerialPort->write(sendData,10);
//}

//��or�رմ���
void MyMainWindow::on_pushButton_uart_sw_clicked()
{
	if (currentUartState == UartState::ON) 
	{
		currentSerialPort->close();
		currentUartState = UartState::OFF;
		ui.pushButton_uart_sw->setText(QString::fromUtf8(u8"�򿪴���"));

		/*if (receiveThread->isRunning())
		{
			receiveThread->quit();
			receiveThread->wait();
		}*/

		ui.comboBox_com->setEnabled(true);
		ui.comboBox_baud->setEnabled(true);
	}
	else
	{
		currentSerialPort->setPortName(ui.comboBox_com->currentText().split(':').at(0));
		currentSerialPort->setBaudRate(ui.comboBox_baud->currentText().toInt());
		//Ĭ�ϲ�������
		currentSerialPort->setFlowControl(QSerialPort::NoFlowControl);// ��������
		currentSerialPort->setDataBits(QSerialPort::Data8);//����Ϊ 8
		currentSerialPort->setStopBits(QSerialPort::OneStop);//ֹͣλһλ
		currentSerialPort->setParity(QSerialPort::NoParity);//��У��λ
		currentSerialPort->setReadBufferSize(10); //���ջ���10���ֽ�

		if (currentSerialPort->open(QSerialPort::ReadWrite)) 
		{
			currentUartState = UartState::ON;
			//�����߳̿�ʼ
			receiveThread->start();
			//���Ӳ��ź� ����
			connect(currentSerialPort, &QSerialPort::readyRead, uartReceive, &Receive::ReceiveUartData);
			ui.pushButton_uart_sw->setText(u8"�رմ���");
			ui.comboBox_com->setEnabled(false);
			ui.comboBox_baud->setEnabled(false);
		}
		else {
			QMessageBox::critical(this, tr("Error"), tr("Fail to turn on this device!"));
		}
	}
}
//������Ϣˢ��
void MyMainWindow::on_pushButton_uart_rfresh_clicked()
{
	if (currentUartState == UartState::ON ||radarUartState == UartState::ON)
		QToolTip::showText(QCursor::pos(), tr("Please turn off the current device first."));
	else
		uartInit();
}
//����combox������Ϣ�ı�
void MyMainWindow::on_comboBox_com_currentTextChanged(const QString &arg1)
{
	ui.comboBox_com->setToolTip(ui.comboBox_com->currentText());
}
//���Ƹ�λ
void MyMainWindow::on_pushButton_ctrl_rst_clicked()
{
	if (currentUartState == UartState::OFF)
		QToolTip::showText(QCursor::pos(), u8"���ȴ򿪴���");
	else
	{
		ui.comboBox_ball->setEnabled(true);
		ui.comboBox_prg->setEnabled(true);
		ui.comboBox_place->setEnabled(true);
		ui.comboBox_prg->clear();
		ui.comboBox_prg->insertItems(0, QStringList()
			<< QApplication::translate("MyMainWindowClass", "0\357\274\232\346\265\213\350\257\225", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "1\357\274\232\347\254\254\344\270\200\345\233\236\345\220\210", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "2\357\274\232\347\254\254\344\272\214\345\233\236\345\220\210", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "3\357\274\232\347\254\254\344\270\211\345\233\236\345\220\210", Q_NULLPTR)
		);
		ui.comboBox_ball->clear();
		ui.comboBox_ball->insertItems(0, QStringList()
			<< QApplication::translate("MyMainWindowClass", "0", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "1", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "2", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "3", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "4", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "5", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "6", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "7", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "8", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "9", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "10", Q_NULLPTR)
		);
		ui.comboBox_place->clear();
		ui.comboBox_place->insertItems(0, QStringList()
			<< QString()
			<< QApplication::translate("MyMainWindowClass", "\345\267\246\345\234\272\345\234\260", Q_NULLPTR)
			<< QApplication::translate("MyMainWindowClass", "\345\217\263\345\234\272\345\234\260", Q_NULLPTR)
		);

		showMapInit();
		//����λ������������

		bRobot->sendCommand(0, 0, 0, 0);
	}
	
}
//����ȷ�ϲۺ���
void MyMainWindow::on_pushButton_ctrl_cfm_clicked()
{
	if (currentUartState == UartState::OFF)
		QToolTip::showText(QCursor::pos(), u8"���ȴ򿪴���");
		//QMessageBox::critical(this, tr("Error"), tr(u8"���ȴ򿪴���"));
	else
	{
		if (ui.comboBox_place->currentText() == u8"�󳡵�")
			showMapLeft();
		else if (ui.comboBox_place->currentText() == u8"�ҳ���")
			showMapRight();

		ui.comboBox_ball->setEnabled(false);
		ui.comboBox_prg->setEnabled(false);
		ui.comboBox_place->setEnabled(false);
		//����λ��������������
		bRobot->sendCommand(4,100,2,3);
	}

}
//��ʾ������Ϣ
void MyMainWindow::robotDataUpdate()
{
	switch (uartReceive->Type)
	{
	case Receive::ENCODER:
		bRobot->v[0] = uartReceive->getData()[0];
		bRobot->v[1] = uartReceive->getData()[1];
		bRobot->v[2] = uartReceive->getData()[2];
		break;

	case Receive::PWM:
		for (int i = 0; i < 3; i++)
			bRobot->PWM[i] = uartReceive->getData()[i];
		break;

	case Receive::POSITION:
		bRobot->setPosion((uartReceive->getData()[0] - 14000) / 1000.0, (uartReceive->getData()[1] - 14000) / 1000.0, uartReceive->getData()[2]);
		break;

	case Receive::VELOCITY:
		bRobot->setRobotV(uartReceive->getData()[0], uartReceive->getData()[1], uartReceive->getData()[2]);
		break;

	default:
		break;
	}
	
	
	
	//if (uartReceive->Type == Receive::ENCODER)
	//{
	//	
	//	bRobot->v[0] = uartReceive->getData()[0];	
	//	bRobot->v[1] = uartReceive->getData()[1];
	//	bRobot->v[2] = uartReceive->getData()[2];

	//	/*ui.lineEdit_m1->setText(QString::number(bRobot->v[0]));
	//	ui.lineEdit_m2->setText(QString::number(bRobot->v[1]));
	//	ui.lineEdit_m3->setText(QString::number(bRobot->v[2]));*/
	//}
	//else if (uartReceive->Type == Receive::PWM)
	//{
	//	for (int i = 0; i < 3; i++)		
	//		bRobot->v[i] = uartReceive->getData()[i];

	//	/*ui.lineEdit_pwm1->setText(QString::number(bRobot->v[0]));
	//	ui.lineEdit_pwm2->setText(QString::number(bRobot->v[1]));
	//	ui.lineEdit_pwm3->setText(QString::number(bRobot->v[2]));*/
	//}
	//else if (uartReceive->Type == Receive::POSITION)
	//{		
	//	bRobot->setPosion((uartReceive->getData()[0]-14000)/1000.0, (uartReceive->getData()[1] - 14000) / 1000.0, uartReceive->getData()[2]);

	//	/*ui.lineEdit_x->setText(QString::number(bRobot->X));
	//	ui.lineEdit_y->setText(QString::number(bRobot->Y));
	//	ui.lineEdit_row->setText(QString::number(bRobot->ThetaD));*/
	//}
	//else if (uartReceive->Type == Receive::VELOCITY)
	//{
	//	bRobot->setRobotV(uartReceive->getData()[0], uartReceive->getData()[1], uartReceive->getData()[2]);

	//	/*ui.lineEdit_Vx->setText(QString::number(bRobot->Vx));
	//	ui.lineEdit_Vy->setText(QString::number(bRobot->Vy));
	//	ui.lineEdit_Vw->setText(QString::number(bRobot->W));*/
	//}

}
//���߳�ֹͣ
void MyMainWindow::stopThread()
{
	if (receiveThread->isRunning())
	{
		receiveThread->quit();
		receiveThread->wait();	
	}
	if (radarThread->isRunning())
	{
		robotRadar->setStop(true);
		radarThread->quit();
		radarThread->wait();
	}
}

void MyMainWindow::on_pushButton_uart_rfresh_r_clicked()
{
	if (currentUartState == UartState::ON || radarUartState == UartState::ON)
		QToolTip::showText(QCursor::pos(), tr("Please turn off the current device first."));
	else
		uartInit();	
}
//�״�����or�ر�
void MyMainWindow::on_pushButton_uart_sw_r_clicked()
{
	if (radarUartState == UartState::ON)
	{
		radarUartState = UartState::OFF;
		ui.pushButton_uart_sw_r->setText(QString::fromUtf8(u8"��ʼ"));

		ui.comboBox_com_radar->setEnabled(true);
		//�ر��߳�
		if (radarThread->isRunning())
		{
			robotRadar->setStop(true);
			radarThread->quit();
			radarThread->wait();
		}
	}
	else
	{
		qDebug() << ui.comboBox_com_radar->currentText().split(':').at(0);
		radarUartState = UartState::ON;

		//robotRadar->startScan(ui.comboBox_com_radar->currentText().split(':').at(0));	
		//�����߳̿�ʼ
		radarThread->start();
		robotRadar->setStop(false);
		emit startRadar(ui.comboBox_com_radar->currentText().split(':').at(0));
		
		//robotRadar->setCom()

		ui.pushButton_uart_sw_r->setText(u8"ֹͣ");
		ui.comboBox_com_radar->setEnabled(false);

	}
}

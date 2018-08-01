#include "MyMainWindow.h"

//#include "cradar.h"

MyMainWindow::MyMainWindow(QWidget *parent)
	: QMainWindow(parent),
	scene(new QGraphicsScene(this)),
	view(new QGraphicsView(scene, this))
{
	ui.setupUi(this);

	ui.playingGround->showMap(scene::CLear);

	currentSerialPort = new QSerialPort(this);
	uartReceive = new Receive(currentSerialPort);
	receiveThread = new QThread(this);
	uartReceive->moveToThread(receiveThread);
	
	bRobot = new robot();
	robotThread = new QThread(this);
	bRobot->moveToThread(robotThread);
	bRobot->Control_Init();

	robotRadar = new radar(bRobot, ui.widget_radar);
	radarThread = new QThread(this);
	robotRadar->moveToThread(radarThread);
	ui.widget_radar->moveToThread(radarThread);

	//显示数据
	showTimerId = startTimer(200);

	uartInit();
	qDebug() << QThread::currentThread() << endl;
	//串口接收成功后显示信息
	connect(uartReceive, &Receive::RecSuccess, this, &MyMainWindow::robotDataUpdate);
	//雷达开始
	connect(this, &MyMainWindow::startRadar, robotRadar, &radar::startScan);
	//雷达报错
	connect(robotRadar, &radar::reportError, this, [this](QString err) {QMessageBox::critical(this, tr("Error"), err); });
	//雷达处理完成
	connect(robotRadar, &radar::sendNearestPoint, this,&MyMainWindow::uartSendCommand);
	//雷达绘图
	//connect(robotRadar, &radar::completeScan, ui.widget_radar, &CRadar::showUpdate);
	//窗口关闭后停止线程
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
//串口初始化
void MyMainWindow::uartInit(void)
{
	currentUartState = UartState::OFF;
	radarUartState = UartState::OFF;
	/* 所有当前可用的串口 */
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

void MyMainWindow::showRobotData()
{
	ui.lineEdit_m1->setText(QString::number(bRobot->v[0]));
	ui.lineEdit_m2->setText(QString::number(bRobot->v[1]));
	ui.lineEdit_m3->setText(QString::number(bRobot->v[2]));

	ui.lineEdit_pwm1->setText(QString::number(bRobot->Velocity[0]));
	ui.lineEdit_pwm2->setText(QString::number(bRobot->Velocity[1]));
	ui.lineEdit_pwm3->setText(QString::number(bRobot->Velocity[2]));

	ui.lineEdit_x->setText(QString::number(bRobot->X));
	ui.lineEdit_y->setText(QString::number(bRobot->Y));
	ui.lineEdit_row->setText(QString::number(bRobot->ThetaD));

	/*ui.lineEdit_Vx->setText(QString::number(bRobot->Vx));
	ui.lineEdit_Vy->setText(QString::number(bRobot->Vy));
	ui.lineEdit_Vw->setText(QString::number(bRobot->W));*/

	ui.lineEdit_radar_angle->setText(QString::number(bRobot->Radar.Angle));
	ui.lineEdit_radar_d->setText(QString::number(bRobot->Radar.Distance));

}


/*上位机给下位机发送协议（数据为三个轮子PWM）
*	开始1	开始2	控制字	数据1	数据1	数据2	数据2	数据3	数据3	校验和
*	@(0x40) ^(0x5E)	cmd		H1		L2		H2		L2		H3		L3		sum
* SUM = 0x40 + 0x5E + cmd + H1 + L1 + H2 + L2 + H3 + L3
*/
void MyMainWindow::uartSendCommand(char cmd, int pwm1, int pwm2, int pwm3)
{
	char sendData[10];
	sendData[0] = '@';
	sendData[1] = '^';
	sendData[2] = cmd;
	sendData[3] = (pwm1>>8) & 0xff;
	sendData[4] = pwm1 & 0xff;
	sendData[5] = (pwm2 >> 8) & 0xff;
	sendData[6] = pwm2 & 0xff;
	sendData[7] = (pwm2 >> 8) & 0xff;
	sendData[8] = pwm3 & 0xff;
	sendData[9] = 0;
	for (int i = 0; i < 9; i++)
		sendData[9] += sendData[i];
	qDebug() << int(sendData[9]) << endl;
	currentSerialPort->write(sendData,10);
}

//打开or关闭串口
void MyMainWindow::on_pushButton_uart_sw_clicked()
{
	if (currentUartState == UartState::ON) 
	{
		currentSerialPort->close();
		currentUartState = UartState::OFF;
		ui.pushButton_uart_sw->setText(QString::fromUtf8(u8"打开串口"));

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
		//默认参数设置
		currentSerialPort->setFlowControl(QSerialPort::NoFlowControl);// 无流控制
		currentSerialPort->setDataBits(QSerialPort::Data8);//数据为 8
		currentSerialPort->setStopBits(QSerialPort::OneStop);//停止位一位
		currentSerialPort->setParity(QSerialPort::NoParity);//无校验位
		currentSerialPort->setReadBufferSize(10); //接收缓存10个字节

		if (currentSerialPort->open(QSerialPort::ReadWrite)) 
		{
			currentUartState = UartState::ON;
			//接收线程开始
			receiveThread->start();
			//连接槽信号 接收
			connect(currentSerialPort, &QSerialPort::readyRead, uartReceive, &Receive::ReceiveUartData);
			ui.pushButton_uart_sw->setText(u8"关闭串口");
			ui.comboBox_com->setEnabled(false);
			ui.comboBox_baud->setEnabled(false);
		}
		else {
			QMessageBox::critical(this, tr("Error"), tr("Fail to turn on this device!"));
		}
	}
}
//串口信息刷新
void MyMainWindow::on_pushButton_uart_rfresh_clicked()
{
	if (currentUartState == UartState::ON ||radarUartState == UartState::ON)
		QToolTip::showText(QCursor::pos(), tr("Please turn off the current device first."));
	else
		uartInit();
}
//串口combox悬浮信息改变
void MyMainWindow::on_comboBox_com_currentTextChanged(const QString &arg1)
{
	ui.comboBox_com->setToolTip(ui.comboBox_com->currentText());
}
//控制复位
void MyMainWindow::on_pushButton_ctrl_rst_clicked()
{
	if (currentUartState == UartState::OFF)
		QToolTip::showText(QCursor::pos(), u8"请先打开串口");
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

		ui.playingGround->showMap(scene::CLear);
		//给下位机发重启命令

		//uartSendCommand(0, 0, 0, 0);
	}
	
}
//控制确认槽函数
void MyMainWindow::on_pushButton_ctrl_cfm_clicked()
{
	if (currentUartState == UartState::OFF)
		QToolTip::showText(QCursor::pos(), u8"请先打开串口");
		//QMessageBox::critical(this, tr("Error"), tr(u8"请先打开串口"));
	else
	{
		if (ui.comboBox_place->currentText() == u8"左场地")
			ui.playingGround->showMap(scene::Left);
		else if (ui.comboBox_place->currentText() == u8"右场地")
			//showMapRight();
			ui.playingGround->showMap(scene::Right);

		ui.comboBox_ball->setEnabled(false);
		ui.comboBox_prg->setEnabled(false);
		ui.comboBox_place->setEnabled(false);
		//给下位机发送启动命令
		//uartSendCommand(4,100,2,3);
		//bRobot->setRobotV(ui.lineEdit_Vx->text().toFloat(), ui.lineEdit_Vy->text().toFloat(), ui.lineEdit_Vw->text().toFloat());
		bRobot->GetMotorVelocity_Self(ui.lineEdit_Vx->text().toFloat(), ui.lineEdit_Vy->text().toFloat(), ui.lineEdit_Vw->text().toFloat());
	}

}
//显示机器信息
void MyMainWindow::robotDataUpdate()
{
	switch (uartReceive->Type)
	{
	case Receive::ENCODER:
		bRobot->v[0] = uartReceive->getData()[0]- 30000;
		bRobot->v[1] = uartReceive->getData()[1] - 30000;
		bRobot->v[2] = uartReceive->getData()[2] - 30000;
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
//子线程停止
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
//雷达启动or关闭
void MyMainWindow::on_pushButton_uart_sw_r_clicked()
{
	if (currentUartState == UartState::OFF)
		QToolTip::showText(QCursor::pos(), u8"请先打开通信串口");
	else
	{
		if (radarUartState == UartState::ON)
		{
			radarUartState = UartState::OFF;
			ui.pushButton_uart_sw_r->setText(QString::fromUtf8(u8"开始"));

			ui.comboBox_com_radar->setEnabled(true);
			//关闭线程
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
			//接收线程开始
			radarThread->start();
			robotRadar->setStop(false);
			emit startRadar(ui.comboBox_com_radar->currentText().split(':').at(0));

			//robotRadar->setCom()

			ui.pushButton_uart_sw_r->setText(u8"停止");
			ui.comboBox_com_radar->setEnabled(false);

		}
	}
}

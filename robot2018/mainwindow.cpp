#include "mainwindow.h"
#include "robotcontroller.h"
#include "ui_mainwindow.h"
#include "tcpsocket.h"
#include "thread.h"

int socketStat = 0;//socket����״̬ 0-δ������1-����
int port;
Tcpserver *server;
QByteArray lidar;
QByteArray shijue;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	scene(new QGraphicsScene(this)),
	view(new QGraphicsView(scene, this)),
	controller(new RobotController(*scene, this)),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//�����������view
	ui->horizontalLayout->addWidget(view);
	//����scene��С
	scene->setSceneRect(0, 0, 720, 545);
	//Ĭ�����Ͻ�
	view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	view->setFixedSize(725, 550);

	//����view����
	pixmap = new QPixmap(720, 545);
	QPainter p(pixmap);
	p.setBrush(QBrush(Qt::gray));
	p.drawRect(0, 0, 720, 545);
	view->setBackgroundBrush(QBrush(*pixmap));

	//��ȡCOM����Ϣ
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
		ui->comComboBox->addItem(info.portName());
	}


	//Ĭ�ϳ�ʼ��
	ui->xLineEdit->setText("0");
	ui->yLineEdit->setText("0");
	ui->thetaLineEdit->setText("0");
	mapType = 0;//�������ͣ�0-��볡��1-�Ұ볡
	comStat = 0;

}

MainWindow::~MainWindow()
{
	delete ui;
}

/* paintEvent
* ������ui���������¼�
* ���룺QPaintEvent -
* �������
*/
void MainWindow::paintEvent(QPaintEvent *)
{
	//showMapLeft();
}

/* showMapLeft
* ������������볡��ͼ
* ���룺��
* �������
*/
void MainWindow::showMapLeft()
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

/* showMapRight
* �������Ұ볡��ͼ����
* ���룺��
* �������
*/
void MainWindow::showMapRight()
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
	groundPath.moveTo(60, 485);
	groundPath.lineTo(60, 535);
	groundPath.lineTo(110, 535);
	groundPath.lineTo(110, 485);
	groundPath.moveTo(10, 485);
	groundPath.lineTo(10, 110);
	groundPath.moveTo(710, 110);
	groundPath.lineTo(710, 10);
	painter.drawPath(groundPath);

	//��Ȧ��
	QPainterPath centerPath;
	centerPath.moveTo(10, 200);
	centerPath.arcTo(-80, 20, 180, 180, 270, 90);
	centerPath.moveTo(10, 240);
	centerPath.arcTo(-120, -20, 260, 260, 270, 90);
	centerPath.moveTo(10, 280);
	centerPath.arcTo(-160, -60, 340, 340, 270, 90);
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

/* on_restartButton_clicked
* ���������ð�ť���
* ���룺��
* �������
*/
void MainWindow::on_restartButton_clicked()
{
	ui->xLineEdit->setText("0");
	ui->yLineEdit->setText("0");
	ui->thetaLineEdit->setText("0");

	switch (mapType) {
	case 0:
		showMapLeft();
		controller->setMapType(0);
		controller->robotInit();
		break;
	case 1:
		showMapRight();
		controller->setMapType(1);
		controller->robotInit();
		break;
	default:
		break;
	}
}

/* on_leftGroundButton_clicked
* ������������볡��ť����¼�
* ���룺��
* �������
*/
void MainWindow::on_leftGroundButton_clicked()
{
	showMapLeft();
	mapType = 0;
	controller->setMapType(0);
	controller->robotInit();
}

/* on_rightGroundButton_clicked
* �����������Ұ볡��ť����¼�
* ���룺��
* �������
*/
void MainWindow::on_rightGroundButton_clicked()
{
	showMapRight();
	mapType = 1;
	controller->setMapType(1);
	controller->robotInit();
}

/* on_handPositionButton_clicked
* �������ֶ����û�����λ�ð�ť����¼�
* ���룺��
* �������
*/
void MainWindow::on_handPositionButton_clicked()
{
	float x, y, theta;
	x = ui->xLineEdit->text().toFloat();
	y = ui->yLineEdit->text().toFloat();
	theta = ui->thetaLineEdit->text().toFloat();

	controller->setRobotCoordinate(x, y, theta);
}


/* on_serverButton_clicked
* ����������udp��server�˼���
* ���룺��
* �������
*/

void MainWindow::on_serverButton_clicked()
{

	if (socketStat == 0)//����״̬Ϊδ����
	{
		//��ȡ�˿�
		port = ui->portLineEdit->text().toInt();
		if (port == 0)
			port = 65432;
		ui->portLineEdit->setText(QString::number(port));

		//ui���ֵ���
		ui->serverButton->setText(u8"Server�ر�");
		ui->portLineEdit->setEnabled(false);
		socketStat = 1;
		server = new Tcpserver;
		server->getlisten();
		//����tcp������ui����
		connect(server, SIGNAL(renew_ui()), this, SLOT(ui_rplidarData()));
	}
	else
	{
		//ui����
		ui->serverButton->setText(u8"Server��");
		ui->portLineEdit->setEnabled(true);
		socketStat = 0;
		server->getlisten();
	}
}




/*listenConnection
*����:tcp�����ۺ���
*����
*���
*
*/
void Tcpserver::listenConnection()
{
	if (socketStat == 1)
	{
		server->listen(QHostAddress::Any, port);
		connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
	}

	else
	{
		disconnect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
		delete server;
	}




}

/* acceptConnection
* ������tcp���Ӳۺ���
* ���룺��
* �������
*/
void Tcpserver::acceptConnection()
{
	if (rplidarConnection)
	{
		shijueConnection = server->nextPendingConnection();
		connect(shijueConnection, SIGNAL(readyRead()), this, SLOT(readwriteClient()));
	}

	else
	{
		rplidarConnection = server->nextPendingConnection();
		connect(rplidarConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
	}


}


/* readClient
* ������tcp���ղۺ������������߳� �״�
* ���룺��
* �������
*/
void Tcpserver::readClient()

{
	lidar = rplidarConnection->readAll();

	emit renew_ui(); // �����ź�->����socketLineEditer

	Thread1 *newthread1 = new Thread1;
	newthread1->start();
}

/* sockSend
* ������socket���Ͳۺ��� �Ӿ�
* ���룺��
* �������
*/

void Tcpserver::sockSend()
{
	shijueConnection->write(shijue);
}

/* readwriteClient
* ������tcp���ղۺ������������߳� �Ӿ�
* ���룺��
* �������
*/
void Tcpserver::readwriteClient()
{
	shijue = shijueConnection->readAll();
	Thread2 *newthread2 = new Thread2;
	newthread2->start();
	connect(newthread2, SIGNAL(sendData()), this, SLOT(sockSend()));

}
/* ui_tcpData
* ������ui����socket���͵�����
* ���룺��
* �������
*/
void MainWindow::ui_rplidarData()
{
	ui->socketLineEditer->setText(lidar);
}

/* on_comButton_clicked
* ����������򿪴���
* ���룺��
* �������
*/
void MainWindow::on_comButton_clicked()
{
	if (comStat == 0)
	{
		//��ȡѡ��Ĳ�����
		int baudId = ui->baudRateComboBox->currentIndex();
		QSerialPort::BaudRate baudRate;
		switch (baudId) {
		case 0:
			baudRate = QSerialPort::Baud1200;
			break;
		case 1:
			baudRate = QSerialPort::Baud2400;
			break;
		case 2:
			baudRate = QSerialPort::Baud4800;
			break;
		case 3:
			baudRate = QSerialPort::Baud9600;
			break;
		case 4:
			baudRate = QSerialPort::Baud19200;
			break;
		case 5:
			baudRate = QSerialPort::Baud38400;
			break;
		case 6:
			baudRate = QSerialPort::Baud57600;
			break;
		case 7:
			baudRate = QSerialPort::Baud115200;
			break;
		default:
			QMessageBox::warning(NULL, "����", "��Ч�����ʣ�", QMessageBox::Yes);
			break;
		}

		//��ȡ����λ
		int dataBitsId = ui->dataBitsComboBox->currentIndex();
		QSerialPort::DataBits dataBits;
		switch (dataBitsId) {
		case 0:
			dataBits = QSerialPort::Data5;
			break;
		case 1:
			dataBits = QSerialPort::Data6;
			break;
		case 2:
			dataBits = QSerialPort::Data7;
			break;
		case 3:
			dataBits = QSerialPort::Data8;
			break;
		default:
			QMessageBox::warning(NULL, "����", "��Ч����λ��", QMessageBox::Yes);
			break;
		}

		//��ȡУ��λ
		int parityId = ui->parityComboBox->currentIndex();
		QSerialPort::Parity parity;
		switch (parityId) {
		case 0:
			parity = QSerialPort::NoParity;
			break;
		case 1:
			parity = QSerialPort::EvenParity;
			break;
		case 2:
			parity = QSerialPort::OddParity;
			break;
		case 3:
			parity = QSerialPort::SpaceParity;
			break;
		case 4:
			parity = QSerialPort::MarkParity;
			break;
		default:
			QMessageBox::warning(NULL, "����", "��ЧУ��λ��", QMessageBox::Yes);
			break;
		}

		//��ȡֹͣλ
		int stopBitsId = ui->stopBitsComboBox->currentIndex();
		QSerialPort::StopBits stopBits;
		switch (stopBitsId) {
		case 0:
			stopBits = QSerialPort::OneStop;
			break;
		case 1:
			stopBits = QSerialPort::OneAndHalfStop;
			break;
		case 2:
			stopBits = QSerialPort::TwoStop;
			break;
		default:
			QMessageBox::warning(NULL, "����", "��Чֹͣλ��", QMessageBox::Yes);
			break;
		}

		QString comName = ui->comComboBox->currentText();

		//�򿪴���
		comPort = new QSerialPort(comName);
		if (comPort->open(QIODevice::ReadWrite))
		{
			comPort->setBaudRate(baudRate);
			comPort->setStopBits(stopBits);
			comPort->setParity(parity);
			comPort->setDataBits(dataBits);
			comPort->setFlowControl(QSerialPort::NoFlowControl);        //û������

			comPort->clearError();
			comPort->clear();
			connect(comPort, SIGNAL(readyRead()), this, SLOT(com_readData()));
			Thread3 *newthread3 = new Thread3(controller);
			newthread3->start();
			timer = new QTimer;
			connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
			timer->start(50);
			//connect(comPort,SIGNAL(close()),timer,SLOT(Stop()));




			//�޸�UI
			ui->comButton->setText("�رմ���");
			ui->baudRateComboBox->setEnabled(false);
			ui->dataBitsComboBox->setEnabled(false);
			ui->parityComboBox->setEnabled(false);
			ui->stopBitsComboBox->setEnabled(false);
			ui->comComboBox->setEnabled(false);
			ui->comRefreshButton->setEnabled(false);
			comStat = 1;
		}
		else
		{
			//�򿪴���ʧ��
			QMessageBox::warning(NULL, "����", "�򿪴���ʧ��", QMessageBox::Yes);
			delete comPort;
		}

	}
	else
	{
		//�رմ���
		comPort->close();
		delete comPort;
		//ui����
		ui->comButton->setText("�򿪴���");
		ui->baudRateComboBox->setEnabled(true);
		ui->dataBitsComboBox->setEnabled(true);
		ui->parityComboBox->setEnabled(true);
		ui->stopBitsComboBox->setEnabled(true);
		ui->comComboBox->setEnabled(true);
		ui->comRefreshButton->setEnabled(true);
		comStat = 0;
	}

}

/* com_readData
* ������COM�����ݶ����
* ���룺��
* �������
*/
void MainWindow::com_readData()
{
	QByteArray arr = comPort->readAll();
	unsigned char *data = (unsigned char *)arr.data();
	QPalette palette;

	if (data[0] == 0xA5 && data[1] == 0x5A)
	{
		if (comCheckSum(data, arr.size()))
		{
			palette.setColor(QPalette::Text, Qt::black);
			//У��ͨ����ͼ�����
			float x, y, theta;
			x = data[2] / 100.0f;
			y = data[3] / 100.0f;
			theta = data[4] / 100.0f;
			controller->setRobotSpeedFromArm(x, y, theta);
			controller->getRobotCoordinate(&x, &y, &theta);
			ui->xLineEdit->setText(QString::number(x));
			ui->yLineEdit->setText(QString::number(y));
			ui->thetaLineEdit->setText(QString::number(theta));
		}
		else
			palette.setColor(QPalette::Text, Qt::red);
	}
	else
	{
		palette.setColor(QPalette::Text, Qt::red);
	}

	ui->comLineEdit->setPalette(palette);
	ui->comLineEdit->setText(arr.data());
}

/* on_comRefreshButton_clicked
* ������ˢ�°�ť���£�ˢ��com����Ϣ
* ���룺��
* �������
*/
void MainWindow::on_comRefreshButton_clicked()
{
	//���ԭ������
	ui->comComboBox->clear();
	//�������ô��ں�
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
		ui->comComboBox->addItem(info.portName());
	}
}

/* on_shotButton_clicked
* ���������俪�أ�����ʱ�������ڷ���
* ���룺��
* �������
*/
void MainWindow::on_shotButton_clicked()
{
	if (comStat == 1)
	{
		comPort->clearError();
		comPort->write("hello");

		if (comPort->error() != QSerialPort::NoError)
			QMessageBox::warning(NULL, "����", "���ݷ���ʧ�ܣ�", QMessageBox::Yes);
		comPort->clearError();
	}
}

/* comCheckSum
* ���������ڽ������ݺ�У��
* ���룺*data - ��������ָ��
*      size - ���ݳ���
* �����У����
*/


bool MainWindow::comCheckSum(unsigned char *data, int size)
{
	unsigned char checksum = 0;
	for (int i = 1; i < size; i++) {
		checksum += *data++;
	}

	if (checksum == *data)
		return true;
	else
		return false;
}


void MainWindow::timer_timeout()
{
	comPort->write(Data);
}


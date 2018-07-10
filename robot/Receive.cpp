#include "Receive.h"

Receive::Receive(QSerialPort* p):receiveSerialPort(p)
{
}

Receive::~Receive()
{
	receiveSerialPort->deleteLater();
}


/*��λ������λ������Э��
 *	��ʼ1	��ʼ2	������	����1	����1	����2	����2	����3	����3	У���
 *	@(0x40)	^(0x5E)	cmd		H1		L2		H2		L2		H3		L3		sum
 *SUM = 0x40 + 0x5E +cmd+H1+L1+H2+L2+H3+L3
*/ 
void Receive::ReceiveUartData()
{
	qDebug() << QThread::currentThread()<<endl;
	QByteArray buf;

	while (receiveSerialPort->bytesAvailable())
	{
		buf = receiveSerialPort->read(1);
		if ('@' == buf.at(0) && Start == false)
			Start = true, Success = false;

		if (Start)
		{
			qDebug() << u8"���տ�ʼ\n";
			originalData += buf;

			if (originalData.size() == 2)
			{
				//�ڶ������� ^ ���½���
				if (originalData.at(1) != '^')
				{
					receiveFail();
					break;
				}
			}
			if (originalData.size() == 10)
			{
				qDebug() << QString::number(Sum, 16) << endl;
				//���ճɹ�
				if (Sum == originalData.at(9))
				{
					qDebug() << originalData << endl;
				
					receiveSuccessful();

				}
				//����ʧ��
				else
					receiveFail();
			}
			else
				Sum += buf.at(0);
		}
		//����ʧ��
		else
			receiveFail();
	}
}

bool Receive::isSuccess()
{
	return Success;
}

bool Receive::isStart()
{
	return Start;
}

QByteArray Receive::getData()
{
	return Data;
}

void Receive::receiveFail()
{
	Start = false;
	Success = false;
	Data.clear();
	originalData.clear();
	Sum = 0;
}

void Receive::receiveSuccessful(void)
{
	Data.clear();

	Data += originalData[4];
	Data += originalData[6];
	Data += originalData[8];

	Success = true;
	Start = false;
	Type = RECTYPE(originalData.at(2));
	Sum = 0;
	originalData.clear();

	emit RecSuccess(); 
}

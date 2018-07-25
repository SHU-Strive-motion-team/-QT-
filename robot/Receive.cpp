#include "Receive.h"

Receive::Receive(QSerialPort* p):receiveSerialPort(p)
{
}

Receive::~Receive()
{
	receiveSerialPort->deleteLater();
	originalData.clear();
	delete Data;
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

int * Receive::getData()
{
	return Data;
}

void Receive::receiveFail()
{
	Start = false;
	Success = false;
	originalData.clear();
	Sum = 0;
}

void Receive::receiveSuccessful(void)
{
	for (int i = 0; i < 3; i++)
	{
		Data[i] = 0;
	}
	
	Data[0] = ((originalData.at(3) << 8) | (originalData.at(4) & 0xff)) & 0xffff;
	Data[1] = ((originalData.at(5) << 8) | (originalData.at(6) & 0xff)) & 0xffff;
	Data[2] = ((originalData.at(7) << 8) | (originalData.at(8) & 0xff)) & 0xffff;
	qDebug() << QString::number(originalData.at(8),16) << endl;
	qDebug() << QString::number(Data[2],10) << endl;
	Success = true;
	Start = false;
	Type = RECTYPE(originalData.at(2));
	Sum = 0;
	originalData.clear();

	emit RecSuccess(); 
}

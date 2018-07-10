#include "Receive.h"

Receive::Receive(QSerialPort* p):receiveSerialPort(p)
{
}

Receive::~Receive()
{
	receiveSerialPort->deleteLater();
}


/*下位机给上位机发送协议
 *	开始1	开始2	控制字	数据1	数据1	数据2	数据2	数据3	数据3	校验和
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
			qDebug() << u8"接收开始\n";
			originalData += buf;

			if (originalData.size() == 2)
			{
				//第二个不是 ^ 重新接收
				if (originalData.at(1) != '^')
				{
					receiveFail();
					break;
				}
			}
			if (originalData.size() == 10)
			{
				qDebug() << QString::number(Sum, 16) << endl;
				//接收成功
				if (Sum == originalData.at(9))
				{
					qDebug() << originalData << endl;
				
					receiveSuccessful();

				}
				//接收失败
				else
					receiveFail();
			}
			else
				Sum += buf.at(0);
		}
		//接收失败
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

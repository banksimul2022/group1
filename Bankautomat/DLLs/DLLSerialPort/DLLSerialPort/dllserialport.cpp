#include "dllserialport.h"
#include <QDebug>

DLLSerialPort::DLLSerialPort() : serial(new QSerialPort)
{
    serial->setPortName("COM3");
    serial->setBaudRate(9600);
    serial->setDataBits(QSerialPort::DataBits(8));
    serial->setParity(QSerialPort::Parity(0));
    serial->setStopBits(QSerialPort::StopBits(1));
    serial->setFlowControl(QSerialPort::FlowControl(0));

    if(!serial->open(QIODevice::ReadWrite)){
        qDebug() << serial->errorString();
    }
}

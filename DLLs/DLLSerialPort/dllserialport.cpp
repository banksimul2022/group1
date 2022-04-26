#include "dllserialport.h"

DLLSerialPort::DLLSerialPort(QObject* parent) : QObject(parent)
{
    qDebug() << "Serial DLL Initializer called";
    serial = new QSerialPort;
    serial->setPortName("COM3");
    serial->setBaudRate(9600);
    serial->setDataBits(QSerialPort::DataBits(8));
    serial->setParity(QSerialPort::Parity(0));
    serial->setStopBits(QSerialPort::StopBits(1));
    serial->setFlowControl(QSerialPort::FlowControl(0));

    if(serial->open(QIODevice::ReadWrite)){
        qDebug() << serial->errorString();
    }else {
        qDebug() << "Serial port opened";
    }
}

DLLSerialPort::~DLLSerialPort()
{
    delete serial;
}

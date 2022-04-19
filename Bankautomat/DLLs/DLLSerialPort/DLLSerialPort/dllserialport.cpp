#include "dllserialport.h"

DLLSerialPort::DLLSerialPort()
{
    serial->setPortName("COM1");
        serial->setBaudRate(9600);
        serial->setDataBits(QSerialPort::DataBits);
        //We will chose the parity bits
        serial->setParity(QSerialPort::Parity);
        //We will chose the stop bits
        serial->setStopBits(QSerialPort::StopBits);
        //We will chose the Flow controls
        serial->setFlowControl(QSerialPort::FlowControl);
}

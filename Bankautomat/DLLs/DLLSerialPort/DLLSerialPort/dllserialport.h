#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include "DLLSerialPort_global.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class DLLSERIALPORT_EXPORT DLLSerialPort
{
public:
    DLLSerialPort();

private:
    QSerialPort *serial = nullptr;
};

#endif // DLLSERIALPORT_H

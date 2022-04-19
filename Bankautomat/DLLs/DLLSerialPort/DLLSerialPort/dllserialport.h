#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include "DLLSerialPort_global.h"
#include <QtSerialPort/QSerialPort>

class DLLSERIALPORT_EXPORT DLLSerialPort
{
public:
    DLLSerialPort();

private:
    QSerialPort *serial;
};

#endif // DLLSERIALPORT_H

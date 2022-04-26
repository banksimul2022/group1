#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include "DLLSerialPort_global.h"
#include <QObject>
#include <QDebug>
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class DLLSERIALPORT_EXPORT DLLSerialPort : public QObject
{
    Q_OBJECT

public:
    DLLSerialPort(QObject* parent = nullptr);
    ~DLLSerialPort();

private:
    QSerialPort *serial = nullptr;
};

#endif // DLLSERIALPORT_H

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
    QSerialPortInfo *serialInfo = nullptr;
    void sendCommand(QString input);
    QString readBuffer();
    void flushBuffer();
    bool testForModule();

public slots:
    void readCard();

signals:
    void cardRead(qint64);

};

#endif // DLLSERIALPORT_H

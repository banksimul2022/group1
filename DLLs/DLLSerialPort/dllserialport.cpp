#include "dllserialport.h"

DLLSerialPort::DLLSerialPort(QObject* parent) : QObject(parent)
{
    qDebug() << "Serial DLL Initializer called";
    serial = new QSerialPort;
    serialInfo = new QSerialPortInfo;
    serial->setBaudRate(9600);
    serial->setDataBits(QSerialPort::DataBits(8));
    serial->setParity(QSerialPort::Parity(0));
    serial->setStopBits(QSerialPort::StopBits(1));
    serial->setFlowControl(QSerialPort::FlowControl(0));

    QList<QSerialPortInfo> ports = serialInfo->availablePorts();                    // Get list of COM ports available on system

    for (int i = 0; (!serial->isOpen() || !readerFound) && i < ports.size(); i++) {
        serial->setPort(ports.at(i));                                               // Select next available port
        qDebug() << "SERIAL: Attempting to open port" << serial->portName();
        if(serial->open(QIODevice::ReadWrite))                                      // Test selected port
            qDebug() << "SERIAL: Error on port open:" << serial->errorString();
        else
            qDebug() << "SERIAL: Port opened OK";
        testForModule();
    }

    if(!readerFound){
        qDebug() << "ERROR: RFID READER NOT FOUND";
        errorState = true;
    } else {
        sendCommand("mc50");
        sendCommand("ml1");
        flushBuffer();
    }

    QObject::connect(serial, &QSerialPort::readyRead, this, &DLLSerialPort::readCard);
}

void DLLSerialPort::sendCommand(QString input){
    qDebug() << "SERIAL: TX called with " << input;
    if(errorState){
        qDebug() << "SERIAL: Could not execute command due to error state";
        return;
    }

    serial->write(input.toUtf8() + '\r');
    if(serial->waitForBytesWritten(1000))                                           // Try writing to port
        qDebug() << "SERIAL: TX OK";
    else
        qDebug() << "SERIAL: TX timeout";
}

QString DLLSerialPort::readBuffer(){
    qDebug() << "SERIAL: RX called";
    if(errorState){
        qDebug() << "SERIAL: Could not execute command due to error state";
        return "";
    }

    if (serial->waitForReadyRead(1000)) {                                           // Check for received bytes
        qDebug() << "SERIAL: RX OK, read data:";
    } else {
        qDebug() << "SERIAL: RX timeout";
        return "";
    }

    QByteArray responseData = serial->readAll();
    while (serial->waitForReadyRead(10))                                            //Wait for response to be finished
        responseData += serial->readAll();

    qDebug() << responseData;
    return QString::fromUtf8(responseData);
}

void DLLSerialPort::flushBuffer(){
    qDebug() << "SERIAL: Buffer flush called";
    if(errorState){
        qDebug() << "SERIAL: Could not execute command due to error state";
        return;
    }
    while(serial->waitForReadyRead(100));
    qDebug() << "SERIAL: Flushing" << serial->bytesAvailable() << "bytes";
    serial->skip(serial->bytesAvailable());
}

bool DLLSerialPort::testForModule(){
    qDebug() << "SERIAL: Module test called";

    sendCommand("i");
    const QString response = readBuffer();                                          // Read device response
    const QString trimmed = response.left(14);                                      // Trim response for testing step

    if(trimmed.compare("i\r\nMOD-RFID125", Qt::CaseSensitivity(false)) == 0){       // Check for correct response
        qDebug() << "SERIAL: RFID module found at" << serial->portName();
        readerFound = true;
        return 1;                                                                   // All checks passed, return 1
    } else {
        qDebug() << "SERIAL:" << serial->portName() << "tested, no module found";
        if(serial->isOpen())
            serial->close();
        return 0;
    }
}

void DLLSerialPort::readCard(){
    qDebug() << "SERIAL: Executing card read";
    if(errorState){
        qDebug() << "SERIAL: Could not execute command due to error state";
        return;
    }
    QString input = readBuffer().mid(3, 10);
    input = input.rightJustified(16, '0');
    qint64 value = input.toLongLong(nullptr, 16);
    qDebug() << "SERIAL: Read tag with hex value" << input;
    emit cardRead(value);
}

DLLSerialPort::~DLLSerialPort(){
    qDebug() << "SERIAL: Destructor called";
    QObject::disconnect(serial, &QSerialPort::readyRead, this, &DLLSerialPort::readCard);
    sendCommand("ms00");
    sendCommand("ml0");
    flushBuffer();
    if(serial->isOpen())
        serial->close();
    delete serial;
}

#include "serialcomms.h"

serialcomms::serialcomms(QObject *parent)
    : QObject{parent}
{
    serialPort = new QSerialPort(this);
    connect(serialPort, &QSerialPort::readyRead, this, &serialcomms::handleReadyRead);
}

serialcomms:: ~serialcomms(){
    delete serialPort;
}

bool serialcomms::isConnected() const {
    return serialPort->isOpen();
}

bool serialcomms::connectTo(const QString &portName, qint32 baudRate){
    serialPort->setBaudRate(baudRate);
    serialPort->setPortName(portName);

    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);

    if(serialPort->open(QIODevice::ReadWrite))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void serialcomms::disconnectFrom(){
    if(serialPort->isOpen()){
        serialPort->close();
    }
}

void serialcomms::dataSend(const QByteArray &data){
    if(serialPort->isOpen())
    {
        serialPort->write(data);
        serialPort->flush();
    }
}

void serialcomms::handleReadyRead(){
    QByteArray data = serialPort->readLine();
    emit dataReceived(data);
}

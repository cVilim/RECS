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
    buffer.append(serialPort->readAll());
    if(buffer.contains('\n')){
        QStringList dataList = QString(buffer).split('\n', Qt::SkipEmptyParts);
        for(const QString &line : dataList){
            QString cleanLine = line;
            cleanLine.remove('\r');
            QStringList stringValues = cleanLine.split('|');

            QVector<double> sensorValue;

            for(const QString &stringValue : stringValues){
                bool isOk;
                double value = stringValue.toDouble(&isOk);
                if(isOk){
                    sensorValue.append(value);
                }
                else{
                    qWarning() << "Conversion to double failed for value:" << stringValue;
                }
            }
            emit dataReceived(sensorValue);
        }
        buffer.clear();
    }
}

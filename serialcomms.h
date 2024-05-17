#ifndef SERIALCOMMS_H
#define SERIALCOMMS_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>

class serialcomms : public QObject
{
    Q_OBJECT
public:
    explicit serialcomms(QObject *parent = nullptr);
    ~serialcomms();

    bool isConnected() const;
    bool connectTo(const QString &portName, qint32 baudRate);
    void disconnectFrom();
    void dataSend(const QByteArray &data);

signals:
    void dataReceived(const QVector<double> &data);

private slots:
    void handleReadyRead();
private:
    QSerialPort *serialPort;
    QByteArray buffer;
};

#endif // SERIALCOMMS_H

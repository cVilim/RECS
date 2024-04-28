#include "mainwindow.h"
#include "serialcomms.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial() // Initialize serial here
{
    ui->setupUi(this);
    serial.connectTo("COM3", 115200);
    if(serial.isConnected())
    {
        QMessageBox::warning(this, "Connection status", "Connected to serial port!");
    }
    else{
        QMessageBox::warning(this, "Error 1", "Unable to connect to serial port\nCheck if the device is connected!");
    }
    connect(&serial, &serialcomms::dataReceived, this, &MainWindow::handleSerialData);
}

MainWindow::~MainWindow()
{
    delete ui;
    void disconnectFrom();
}

void MainWindow::handleSerialData(const QByteArray &data){
    qDebug() << data;
}

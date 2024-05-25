#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphhandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial()
{
    ui->setupUi(this);

    serial.connectTo("COM3", 115200);

    QSharedPointer<QCPAxisTickerTime> ticker = timeTickerDisplay();

    GraphSetup::setupGraph(ui->pressures, "Relative timestamp", "Pressure(bar)", ticker);
    ui->pressures->yAxis->setRange(-50, 100);

    GraphSetup::setupGraph(ui->temps, "Relative timestamp", "Temperatures °C", ticker);
    ui->temps->yAxis->setRange(-200, 500);

    for (int i = 0; i < 4; ++i) {
        QCPGraph* graph = ui->pressures->addGraph();
        graph->setPen(QPen(globals::graphColors[i], 2));
        graph->setBrush(QBrush(globals::graphBrushes[i]));
        graph->setName(QString("Pressure %1").arg(i+1));
    }

    if (!serial.isConnected()) {
        QMessageBox::warning(this, "Error 1", "Unable to connect to serial port\n-Check if the device is connected!");
    }

    graphHandler = new GraphHandler(ui->pressures, serial, this);

}

MainWindow::~MainWindow() {
    delete ui;
    serial.disconnectFrom();
    delete graphHandler;
}

QSharedPointer<QCPAxisTickerTime> MainWindow::timeTickerDisplay() {
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%m:%s:%ms");
    return timeTicker;
}

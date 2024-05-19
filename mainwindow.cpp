#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GraphSetup.h"

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
    }

    if (!serial.isConnected()) {
        QMessageBox::warning(this, "Error 1", "Unable to connect to serial port\n-Check if the device is connected!");
    }

    connect(&serial, &serialcomms::dataReceived, this, &MainWindow::handleSerialData);
}

MainWindow::~MainWindow() {
    delete ui;
    serial.disconnectFrom();
}

QSharedPointer<QCPAxisTickerTime> MainWindow::timeTickerDisplay() {
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%m:%s:%ms");
    return timeTicker;
}

void MainWindow::handleSerialData(const QVector<double> &data) {
    static QTime time(QTime::currentTime());
    double key = time.msecsTo(QTime::currentTime()) / 1000.0;
    const int maxDataPoints = 50;
    const int smoothingWindow = 5;
    static QVector<QVector<double>> buffers(4, QVector<double>(maxDataPoints, 0));

    for (int i = 0; i < data.size(); ++i) {
        buffers[i].push_back(data[i]);
        if (buffers[i].size() > maxDataPoints) {
            buffers[i].removeFirst();
        }
    }
    static QElapsedTimer timer;
    if (!timer.isValid() || timer.elapsed() > 20) {
        for (int i = 0; i < 4; ++i) {
            QCPGraph* graph = ui->pressures->graph(i);
            double sum = 0.0;
            int count = qMin(smoothingWindow, buffers[i].size());
            for (int j = buffers[i].size() - count; j < buffers[i].size(); ++j) {
                sum += buffers[i][j];
            }
            double average = sum / count;

            graph->addData(key, average);

            if (graph->data()->size() > maxDataPoints) {
                graph->data()->removeBefore(key - maxDataPoints);
            }
        }

        ui->pressures->xAxis->setRange(key, 8, Qt::AlignRight);
        ui->pressures->replot();

        timer.restart();
    }
}

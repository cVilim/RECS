#include "graphhandler.h"

GraphHandler::GraphHandler(QCustomPlot* plot, serialcomms &serial, QObject *parent)
    : QObject(parent), plot(plot), serial(serial)
{
    connect(&serial, &serialcomms::dataReceived, this, &GraphHandler::handleSerialData);
}

void GraphHandler::handleSerialData(const QVector<double> &data)
{
    static QTime time(QTime::currentTime());
    double key = time.msecsTo(QTime::currentTime()) / 1000.0;
    const int maxDataPoints = 10;
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
            QCPGraph* graph = plot->graph(i);
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

        plot->xAxis->setRange(key, 8, Qt::AlignRight);
        plot->replot();

        timer.restart();
    }
}

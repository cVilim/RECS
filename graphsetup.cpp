#include "graphsetup.h"

GraphSetup::GraphSetup() {}

void GraphSetup::setupGraph(QCustomPlot *customPlot, const QString &xlabel, const QString &ylabel, QSharedPointer<QCPAxisTickerTime> ticker) {
    globals::gridCol.setAlpha(150);
    customPlot->setBackground(globals::bgCol);

    customPlot->xAxis->setLabel(xlabel);
    customPlot->xAxis->setLabelColor(Qt::white);
    customPlot->xAxis->setTicker(ticker);

    customPlot->yAxis->setLabel(ylabel);
    customPlot->yAxis->setLabelColor(Qt::white);

    customPlot->xAxis->setBasePen(QPen(globals::penCol));
    customPlot->xAxis->setTickPen(QPen(globals::penCol));
    customPlot->xAxis->setSubTickPen(QPen(globals::penCol));
    customPlot->xAxis->setTickLabelColor(globals::penCol);

    customPlot->yAxis->setBasePen(QPen(globals::penCol));
    customPlot->yAxis->setTickPen(QPen(globals::penCol));
    customPlot->yAxis->setSubTickPen(QPen(globals::penCol));
    customPlot->yAxis->setTickLabelColor(globals::penCol);

    customPlot->legend->setVisible(true);
    QFont legendFont("Helevetica", 9);
    customPlot->legend->setFont(legendFont);
    customPlot->legend->setBrush(QColor(102, 102, 102, 150));
}

void GraphSetup::realTimeDataSlot(QCustomPlot *customPlot, QVector<double> data, int NUM){
    static QTime time(QTime::currentTime());
    double key = time.msecsTo(QTime::currentTime()) / 1000;
    static double lastPointKey = 0;
    if(key-lastPointKey > 0.05){
        customPlot->graph(NUM)->addData(key, data[NUM]);
        lastPointKey = key;
    }
}

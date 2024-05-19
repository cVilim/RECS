#ifndef GRAPHSETUP_H
#define GRAPHSETUP_H
#include "QCustomPlot.h"
#include <QSharedPointer>
#include "globals.h"

class GraphSetup
{
public:
    GraphSetup();
    static void setupGraph(QCustomPlot *customPlot, const QString &xlabel, const QString &ylabel, QSharedPointer<QCPAxisTickerTime> ticker);
    void realTimeDataSlot(QCustomPlot *customPlot, QVector<double> data, int NUM);
};

#endif // GRAPHSETUP_H

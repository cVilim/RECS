#ifndef GRAPHHANDLER_H
#define GRAPHHANDLER_H

#include <QObject>
#include <QVector>
#include <qcustomplot.h>
#include <QElapsedTimer>
#include <QTime>
#include "serialcomms.h"

class GraphHandler : public QObject
{
    Q_OBJECT
public:
    explicit GraphHandler(QCustomPlot *plot, serialcomms &serial, QObject *parent = nullptr);

private slots:
    void handleSerialData(const QVector<double> &data);

private:
    QCustomPlot* plot;
    serialcomms &serial;

signals:
};

#endif // GRAPHHANDLER_H

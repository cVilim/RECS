#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtWidgets>
#include <serialcomms.h>
#include <QThread>
#include "qcustomplot.h"
#include "globals.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleSerialData(const QVector<double> &data);

private:
    Ui::MainWindow *ui;
    serialcomms serial; // Assuming serialcomms is a custom class

    QSharedPointer<QCPAxisTickerTime> timeTickerDisplay();
    void graphSetupPressures(const QString &xlabel, const QString &ylabel, QSharedPointer<QCPAxisTickerTime> ticker);
    void graphSetupTemps(const QString &xlabel, const QString &ylabel, QSharedPointer<QCPAxisTickerTime> ticker);
    void setupGraph(QCustomPlot *customPlot, const QString &xlabel, const QString &ylabel, QSharedPointer<QCPAxisTickerTime> ticker);
};
#endif // MAINWINDOW_H

#include "globals.h"

globals::globals() {}
QColor globals::bgCol = QColor(30, 30, 30);
QColor globals::gridCol = QColor(140, 140, 140);
QColor globals::penCol = QColor(199, 203, 205);
QVector<QColor> globals::graphColors = {
    QColor(48, 174, 50),
    QColor(245, 190, 23),
    QColor(0, 191, 255),
    QColor(255, 127, 80),
    QColor(0, 250, 154),
    QColor(30, 144, 255),
    QColor(222, 151, 53),
    QColor(255, 183, 81)
};
QVector<QColor> globals::graphBrushes{
    QColor(48, 174, 50, 50),
    QColor(245, 190, 23, 50),
    QColor(0, 191, 255, 50),
    QColor(255, 127, 80, 50),
    QColor(0, 250, 154, 50),
    QColor(30, 144, 255, 50),
    QColor(222, 151, 53, 50),
    QColor(255, 183, 81, 50)
};

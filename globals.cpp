#include "globals.h"

globals::globals() {}
QColor globals::bgCol = QColor(30, 30, 30);
QColor globals::gridCol = QColor(140, 140, 140);
QColor globals::penCol = QColor(199, 203, 205);
QVector<QColor> globals::graphColors = {
    QColor(48, 174, 50),
    QColor(245, 190, 23),
    QColor(81, 195, 225),
    QColor(255, 183, 81),
    QColor(255, 111, 81)
};
QVector<QColor> globals::graphBrushes{
    QColor(48, 174, 50, 50),
    QColor(245, 190, 23, 50),
    QColor(81, 195, 225, 50),
    QColor(255, 183, 81, 50),
    QColor(255, 111, 81, 50)
};

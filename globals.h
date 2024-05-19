#ifndef GLOBALS_H
#define GLOBALS_H
#include <QColor>
class globals
{
public:
    globals();
    static QColor bgCol;
    static QColor gridCol;
    static QColor penCol;
    static QVector<QColor> graphColors;
    static QVector<QColor> graphBrushes;
};
#endif // GLOBALS_H

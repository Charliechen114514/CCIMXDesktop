#ifndef LABELSTYLEREADER_H
#define LABELSTYLEREADER_H

#include <QLabel>
#include <QFont>
#include <QColor>

class LabelStyleReader {
public:
    static QFont font(const QLabel* label);
    static int fontSize(const QLabel* label);
    static QColor textColor(const QLabel* label);
};


#endif // LABELSTYLEREADER_H

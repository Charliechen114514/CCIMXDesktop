#include "DateIcon.h"
#include <QDate>
#include <QPainter>
#include <QPixmap>

DateIcon::DateIcon(QWidget* parent)
    : QWidget { parent }
    , handling_date(QDate::currentDate()) {
    QSizePolicy p(QSizePolicy::Preferred, QSizePolicy::Preferred);
    p.setHeightForWidth(true);
    setSizePolicy(p);
}

int DateIcon::heightForWidth(int w) const {
    return w;
}

QPixmap DateIcon::generateCalendarIcon(int width, int height,
                                       const QDate& date,
                                       bool darkMode) {
    QString weekday = date.toString("ddd");
    int dayNumber = date.day();

    QPixmap pm(width, height);
    pm.fill(Qt::transparent);

    QPainter p(&pm);
    p.setRenderHint(QPainter::Antialiasing);

    QColor bg = darkMode ? QColor(30, 30, 30) : Qt::white;
    QColor header = QColor(239, 75, 66);
    QColor weekdayColor = header;
    QColor dayColor = darkMode ? Qt::white : Qt::black;

    QRectF rect(0, 0, width, height);
    p.setBrush(bg);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect, width * 0.1, height * 0.1);

    QRectF headerRect(0, 0, width, height * 0.25);
    p.setBrush(header);
    p.drawRoundedRect(headerRect, width * 0.1, height * 0.1);

    QFont wf("Helvetica", width / 10);
    wf.setBold(false);
    p.setFont(wf);
    p.setPen(weekdayColor);
    p.drawText(headerRect, Qt::AlignCenter, weekday);

    QRectF dayRect(0, height * 0.25, width, height * 0.75);
    QFont df("Helvetica", width / 2, QFont::Bold);
    p.setFont(df);
    p.setPen(dayColor);
    p.drawText(dayRect, Qt::AlignCenter, QString::number(dayNumber));

    return pm;
}

void DateIcon::paintEvent(QPaintEvent* event [[maybe_unused]]) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const int W = width(), H = height();
    QColor bg = Qt::white;
    QColor header = QColor(239, 75, 66);
    QColor weekdayColor = header;
    QColor dayColor = Qt::black;

    p.setBrush(bg);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(0, 0, W, H, W * 0.1, H * 0.1);

    QRectF hr(0, 0, W, H * 0.25);
    p.setBrush(header);
    p.drawRoundedRect(hr, W * 0.1, H * 0.1);

    QFont wf("Helvetica", W / 10);
    p.setFont(wf);
    p.setPen(weekdayColor);
    p.drawText(hr, Qt::AlignCenter, handling_date.toString("ddd"));

    QRectF dr(0, H * 0.25, W, H * 0.75);
    QFont df("Helvetica", W / 2, QFont::Bold);
    p.setFont(df);
    p.setPen(dayColor);
    p.drawText(dr, Qt::AlignCenter, handling_date.toString("dd"));
}

QSize DateIcon::sizeHint() const {
    int s = qMin(width(), height());
    return QSize(s, s);
}

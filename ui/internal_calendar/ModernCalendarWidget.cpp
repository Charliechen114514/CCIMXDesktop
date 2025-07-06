#include "ModernCalendarWidget.h"
#include <QDate>
#include <QLocale>
#include <QPainter>
#include <QStyleOptionComplex>
#include <QToolButton>
ModernCalendarWidget::ModernCalendarWidget(QWidget* parent)
    : QCalendarWidget(parent) {
    setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    setNavigationBarVisible(true);
    setFirstDayOfWeek(Qt::Sunday);
    styleNavigationBar();
    setStyleSheet(global_mode_qss());
}

void ModernCalendarWidget::setDarkMode(bool darkMode) {
    this->darkMode = darkMode;
    setStyleSheet(global_mode_qss(darkMode));
    update();
}

void ModernCalendarWidget::setColorForDate(const QDate& date, const QColor& color) {
    dateColors[date] = color;
    updateCell(date);
}

void ModernCalendarWidget::popColorForData(const QDate& date) {
    dateColors.remove(date);
    updateCell(date);
}

void ModernCalendarWidget::styleNavigationBar() {
    // 左右按钮
    QToolButton* prevBtn = this->findChild<QToolButton*>("qt_calendar_prevmonth");
    QToolButton* nextBtn = this->findChild<QToolButton*>("qt_calendar_nextmonth");

    QWidget* navBar = this->findChild<QWidget*>("qt_calendar_navigationbar");

    if (navBar) {
        navBar->setStyleSheet(R"(
            QWidget {
                background-color: transparent;
                border: none;
            }
        )");
    }

    if (prevBtn && nextBtn) {
        prevBtn->setIcon(QIcon(":/icons/left_arrow.png"));
        nextBtn->setIcon(QIcon(":/icons/right_arrow.png"));

        prevBtn->setStyleSheet(R"(
            QToolButton {
                border: none;
                background: transparent;
                padding: 4px;
            }
        )");
        nextBtn->setStyleSheet(prevBtn->styleSheet());
    }

    QToolButton* monthBtn = this->findChild<QToolButton*>("qt_calendar_monthbutton");
    QToolButton* yearBtn = this->findChild<QToolButton*>("qt_calendar_yearbutton");

    if (monthBtn && yearBtn) {
        QString buttonStyle = R"(
            QToolButton {
                color: #3F51B5;
                font: bold 16px;
                background: transparent;
                border: none;
            }
        )";
        monthBtn->setStyleSheet(buttonStyle);
        yearBtn->setStyleSheet(buttonStyle);
    }
}

void ModernCalendarWidget::paintCell(QPainter* painter, const QRect& rect, const QDate date) const {
    painter->save();

    const bool isToday = date == QDate::currentDate();
    const bool isSelected = date == selectedDate();
    const QColor eventColor = dateColors.value(date, Qt::transparent);
    const int radius = std::min(rect.width(), rect.height());
    const QPointF center = rect.center(); // 提前计算中心点

    // 1. 颜色和尺寸预计算
    const QColor baseBgColor = darkMode ? QColor(30, 30, 30) : QColor(240, 240, 240);
    const QColor todayOutlineColor = QColor(0x3F51B5);
    const QColor selectedFgColor = Qt::white;
    const QColor defaultFgColor = darkMode ? QColor(220, 220, 220) : Qt::black;

    // 2. 背景绘制 (所有单元格都需要)
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(baseBgColor);
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(rect.adjusted(4, 4, -4, -4), 8, 8);

    // 3. 状态指示器 (优先顺序: 选中 > 事件 > 今天)
    if (isSelected) {
        painter->setBrush(todayOutlineColor);
        painter->drawEllipse(center, radius / 2.3, radius / 2.3);
    } else if (eventColor != Qt::transparent) {
        painter->setBrush(eventColor);
        painter->drawEllipse(center, radius / 2.8, radius / 2.8);
    } else if (isToday) {
        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(todayOutlineColor, 1.5));
        painter->drawEllipse(center, radius / 2.5, radius / 2.5);
    }

    // 4. 文本绘制优化 (统一处理字体和颜色)
    QFont font = painter->font();
    if (isSelected)
        font.setBold(true); // 仅当选中时设置粗体
    painter->setFont(font);
    painter->setPen(isSelected ? selectedFgColor : defaultFgColor);

    // 根据状态决定文本内容
    if (isToday && !isSelected && eventColor == Qt::transparent) {
        // 今天状态特殊处理
        painter->drawText(rect.adjusted(0, 4, 0, rect.height() / 3),
                          Qt::AlignCenter, "Today");
    } else {
        // 常规日期文本
        painter->drawText(rect.adjusted(0, 4, 0, 0),
                          Qt::AlignCenter, QString::number(date.day()));
    }

    painter->restore();
}

QString ModernCalendarWidget::global_mode_qss(bool isDarkMode) {
    return isDarkMode ?
                      R"(
QCalendarWidget QWidget {
    alternate-background-color: transparent;
}
QCalendarWidget QAbstractItemView {
    background-color: #121212;
    color: #eeeeee;
    border: 1px solid #333;
    selection-background-color: #3F51B5;
    selection-color: white;
    font: 14px 'Segoe UI';
}
QCalendarWidget QToolButton:hover {
    background-color: #1E1E1E;
    border-radius: 4px;
}
QCalendarWidget QToolButton::menu-indicator {
    image: none;
}
QCalendarWidget QMenu {
    background-color: #1E1E1E;
    border: 1px solid #333;
    color: #eee;
    font: 14px 'Segoe UI';
}
QCalendarWidget QMenu::item:selected {
    background-color: #3F51B5;
    color: white;
}
        )" ///< darkMode
                      :

                      R"(
QCalendarWidget QWidget {
    alternate-background-color: transparent;
}
QCalendarWidget QAbstractItemView {
    selection-background-color: transparent;
    outline: none;
    gridline-color: transparent;
    font-size: 15px;
}
QCalendarWidget QToolButton:hover {
    background-color: #E3F2FD;
    border-radius: 4px;
}

QCalendarWidget QAbstractItemView {
    background-color: white;
    color: #333;
    font: 14px 'Segoe UI';
    border: 1px solid #C5CAE9;
    selection-background-color: #3F51B5;
    selection-color: white;
    outline: none;
    padding: 4px;
}

QCalendarWidget QToolButton::menu-indicator {
    image: none;
}

QCalendarWidget QMenu {
    background-color: white;
    border: 1px solid #C5CAE9;
    padding: 4px;
    font: 14px 'Segoe UI';
    color: #333;
}

QCalendarWidget QMenu::item:selected {
    background-color: #3F51B5;
    color: white;
}
    )";
}

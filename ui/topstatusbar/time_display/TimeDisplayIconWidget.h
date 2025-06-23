#ifndef TIMEDISPLAYICONWIDGET_H
#define TIMEDISPLAYICONWIDGET_H

#include "../StatusBarIconWidget.h"
#include <QTime>
#include <QWidget>
namespace Ui {
class TimeDisplayIconWidget;
}
class QLabel;

class TimeDisplayIconWidget : public StatusBarIconWidget {
	Q_OBJECT

public:
    explicit TimeDisplayIconWidget(QWidget* parent = nullptr);
	~TimeDisplayIconWidget();
    QLabel* displayedLabel() const;
public slots:
    void update_displayTime(QTime time);

private:
    Ui::TimeDisplayIconWidget* ui;
};

#endif // TIMEDISPLAYICONWIDGET_H

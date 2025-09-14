#ifndef TOOLSBAR_H
#define TOOLSBAR_H

#include "alarmynotifier.h"
#include <QWidget>

namespace Ui {
class ToolsBar;
}
class EditTimeWidget;
class ToolsBar : public QWidget {
	Q_OBJECT

public:
    explicit ToolsBar(AlarmyNotifier* notifier, QWidget* parent = nullptr);
    void installNewEditTimeWidget(const QTime time);
    void removeNewEditTimeWidget(const QTime time);
	~ToolsBar();

private:
    AlarmyNotifier* notifier;
    Ui::ToolsBar* ui;
    QList<EditTimeWidget*> widgets;
};

#endif // TOOLSBAR_H

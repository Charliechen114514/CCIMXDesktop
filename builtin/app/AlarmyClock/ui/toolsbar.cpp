#include "toolsbar.h"
#include "alarmynote.h"
#include "ui_toolsbar.h"
#include "edittimewidget.h"
#include <QTime>
#include <stdexcept>
#include "alarmynotifier.h"
ToolsBar::ToolsBar(AlarmyNotifier *notifier, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ToolsBar), notifier(notifier) {
    if(!notifier){
        throw std::invalid_argument("Notifier is NULL!"
                                    "This should never happens...");
    }
	ui->setupUi(this);
}

void ToolsBar::installNewEditTimeWidget(const QTime time)
{
    auto new_widget = new EditTimeWidget(this);
    connect(new_widget, &EditTimeWidget::timeChanged,
            notifier, [this](QTime oldTime, QTime newTime){
                auto notes = notifier->searchWithTime(oldTime);
                if(!notes){
                    qCritical() << "Error in find notes";
                    return;
                }
                notes->setTimer(newTime);
            });
    new_widget->setTime(time);
    widgets.emplaceBack(new_widget);
    ui->verticalLayout->addWidget(new_widget);
}

void ToolsBar::removeNewEditTimeWidget(const QTime time)
{
    auto it = std::find_if(widgets.begin(), widgets.end(), [time](const EditTimeWidget* w){
        return w->time() == time;
    });

    if(it == widgets.end()){
        qCritical() << "Error in find widgets!";
        return;
    }

    // get the widgets
    EditTimeWidget* widget = *it;
    widget->setAlarmEnabled(false);

    auto notes = notifier->searchWithTime(widget->time());
    notifier->removeAlarmyTime(notes);
    widgets.removeAll(widget);
    ui->verticalLayout->removeWidget(widget);
    widget->deleteLater(); // Delete this
}

ToolsBar::~ToolsBar() {
	delete ui;
}

#ifndef DATENOTER_H
#define DATENOTER_H
#include "panel_widget/PanelWidget.h"
#include <QDate>
#include <QWidget>
namespace Ui {
class DateNoter;
}
class NoteInfo;
class DateNoter : public PanelWidget {
	Q_OBJECT

public:
    explicit DateNoter(QWidget* parent = nullptr);
	~DateNoter();
    void setDisplayingDate(const QDate& date, NoteInfo* info);

private:
    Ui::DateNoter* ui;
    QDate current_date_handling { QDate::currentDate() };
    NoteInfo* info { nullptr };
};

#endif // DATENOTER_H

#ifndef DATENOTER_H
#define DATENOTER_H

#include "panel_widget/PanelWidget.h"
#include <QDate>
#include <QWidget>

namespace Ui {
class DateNoter;
}

class NoteInfo;

/**
 * @class DateNoter
 * @brief A panel widget for displaying and editing date notes
 *
 * Provides an interface for viewing and modifying notes associated
 * with specific dates.
 */
class DateNoter : public PanelWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a DateNoter widget
     * @param parent The parent widget
     */
    explicit DateNoter(QWidget* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~DateNoter();

    /**
     * @brief Sets the date and note to display
     * @param date The date to display
     * @param info The note information to display
     */
    void setDisplayingDate(const QDate& date, NoteInfo* info);

private:
    Ui::DateNoter* ui; /**< The UI components */
    QDate current_date_handling { QDate::currentDate() }; /**< The currently displayed date */
    NoteInfo* info { nullptr }; /**< The currently displayed note */
};

#endif // DATENOTER_H

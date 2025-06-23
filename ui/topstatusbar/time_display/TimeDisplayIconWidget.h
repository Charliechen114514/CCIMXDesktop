#ifndef TIMEDISPLAYICONWIDGET_H
#define TIMEDISPLAYICONWIDGET_H

#include "../StatusBarIconWidget.h"
#include <QTime>
#include <QWidget>

namespace Ui {
class TimeDisplayIconWidget;
}

class QLabel;

/**
 * @brief Widget for displaying time in the status bar.
 *
 * Shows current time and updates it periodically.
 */
class TimeDisplayIconWidget : public StatusBarIconWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the time display widget.
     * @param parent Parent widget (optional)
     */
    explicit TimeDisplayIconWidget(QWidget* parent = nullptr);
    
    /**
     * @brief Destroys the time display widget.
     */
    ~TimeDisplayIconWidget();
    
    /**
     * @brief Gets the label used for time display.
     * @return Pointer to the display label
     */
    QLabel* displayedLabel() const;

public slots:
    /**
     * @brief Updates the displayed time.
     * @param time New time to display
     */
    void update_displayTime(QTime time);

private:
    Ui::TimeDisplayIconWidget* ui;  ///< UI components for the widget
};

#endif // TIMEDISPLAYICONWIDGET_H
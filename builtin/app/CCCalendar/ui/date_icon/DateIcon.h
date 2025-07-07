#ifndef DATEICON_H
#define DATEICON_H

#include <QDate>
#include <QWidget>

/**
 * @class DateIcon
 * @brief A widget that displays a date in an icon-like format
 *
 * Generates a calendar-style icon showing the specified date.
 */
class DateIcon : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Constructs a DateIcon widget
     * @param parent The parent widget
     */
    explicit DateIcon(QWidget* parent = nullptr);

    /**
     * @brief Gets the recommended size for the widget
     * @return The recommended size
     */
    QSize sizeHint() const override;

    /**
     * @brief Calculates height for a given width
     * @param width The width to calculate height for
     * @return The appropriate height
     */
    int heightForWidth(int width) const override;

    /**
     * @brief Generates a calendar icon pixmap
     * @param width The desired width
     * @param height The desired height
     * @param date The date to display
     * @param darkMode Whether to use dark mode colors
     * @return The generated pixmap
     */
    static QPixmap generateCalendarIcon(int width, int height,
                                        const QDate& date,
                                        bool darkMode = false);

    /**
     * @brief Sets the date to display
     * @param date The date to display
     */
    void setHandleDate(const QDate& date) { handling_date = date; }

    /**
     * @brief Gets the current display date
     * @return The current date
     */
    QDate handleDate() const { return handling_date; }

protected:
    /**
     * @brief Handles paint events
     * @param event The paint event
     */
    void paintEvent(QPaintEvent* event) override;

private:
    QDate handling_date; /**< The date being displayed */
};

#endif // DATEICON_H

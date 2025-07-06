#ifndef MODERNCALENDARWIDGET_H
#define MODERNCALENDARWIDGET_H
#include <QCalendarWidget>
#include <QColor>
#include <QDate>
#include <QMap>

class ModernCalendarWidget : public QCalendarWidget {
    Q_OBJECT
public:
    /**
     * @brief ModernCalendarWidget
     * @param parent
     */
    explicit ModernCalendarWidget(QWidget* parent = nullptr);
    /**
     * @brief setDarkMode set the calendar as the darkMode
     * @param darkMode isDarkMode
     */
    void setDarkMode(bool darkMode);
    /**
     * @brief isDarkMode
     * @return isDarkMode
     */
    bool isDarkMode() const { return darkMode; }
    /**
     * @brief setColorForDate marking for the date
     * @param date
     * @param color
     */
    void setColorForDate(const QDate& date, const QColor& color);
    void popColorForData(const QDate& date);

protected:
    /**
     * @brief paintCell
     * @param painter
     * @param rect
     * @param date
     */
    void paintCell(QPainter* painter, const QRect& rect, const QDate date) const override;

private:
    QMap<QDate, QColor> dateColors; ///< data color mappings
    bool darkMode { false };
    /**
     * @brief styleNavigationBar
     *  process the navigationBar beautify
     */
    void styleNavigationBar();
    /**
     * @brief global_mode_qss
     * @param isDarkMode
     * @return
     */
    QString global_mode_qss(bool isDarkMode = false);
};

#endif // MODERNCALENDARWIDGET_H

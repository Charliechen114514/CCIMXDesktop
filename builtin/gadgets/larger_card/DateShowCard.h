#ifndef DATESHOWCARD_H
#define DATESHOWCARD_H

#include <QWidget>
class QLabel;
/**
 * @brief The DateShowCard class
 */
class DateShowCard : public QWidget {
	Q_OBJECT
public:
    explicit DateShowCard(QWidget* parent = nullptr); ///< constructor
    /**
     * @brief setDate setTheDate
     * @param dayOfMonth day in month
     * @param fullDateText
     * @param title
     */
    void setDate(int dayOfMonth, const QString& fullDateText, const QString& title);

private:
    QLabel* titleLabel; ///< title label
    QLabel* dayLabel; ///< day label
    QLabel* fullTextLabel; ///< fullText Label
};

#endif // DATESHOWCARD_H

#ifndef DATEICON_H
#define DATEICON_H
#include <QDate>
#include <QWidget>

class DateIcon : public QWidget {
	Q_OBJECT
public:
    explicit DateIcon(QWidget* parent = nullptr);
    QSize sizeHint() const override;
    int heightForWidth(int) const override;
    static QPixmap generateCalendarIcon(int width, int height,
                                        const QDate& date,
                                        bool darkMode = false);
    void setHandleDate(const QDate& date) { handling_date = date; }
    QDate handleDate() const { return handling_date; }

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QDate handling_date;
};

#endif // DATEICON_H

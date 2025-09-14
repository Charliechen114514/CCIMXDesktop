#ifndef EDITTIMEWIDGET_H
#define EDITTIMEWIDGET_H

#include <QWidget>
class QLabel;
class QTimeEdit;
class QCheckBox;


class EditTimeWidget : public QWidget {
    Q_OBJECT
public:
    // 构造函数
    explicit EditTimeWidget(QWidget *parent = nullptr);
    ~EditTimeWidget();

    void setTime(const QTime &time);
    QTime time() const;

    void setAlarmEnabled(bool enabled);
    bool isAlarmEnabled() const;
signals:
    void timeChanged(const QTime old, const QTime &time);
    void alarmEnabledChanged(bool enabled);

private:
    void setupUi();
    void setupStyle();
    QTimeEdit *timeEdit;
    QCheckBox *toggleSwitch;
};

#endif // EDITTIMEWIDGET_H

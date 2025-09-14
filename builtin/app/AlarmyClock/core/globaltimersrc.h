#ifndef GLOBALTIMERSRC_H
#define GLOBALTIMERSRC_H
#include <QTimer>
#include <QObject>

class GlobalTimerSrc : public QObject {
	Q_OBJECT
public:
    explicit GlobalTimerSrc(QObject* parent = nullptr);

signals:
    void updateTime(const QTime time);

private:
    QTimer timer;
};

#endif // GLOBALTIMERSRC_H

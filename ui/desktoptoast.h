#ifndef DESKTOPTOAST_H
#define DESKTOPTOAST_H
#include <QPointer>
#include <QWidget>
#include <QQueue>
class QLabel;
class QPropertyAnimation;
class DesktopToast : public QWidget
{
    Q_OBJECT
public:
    explicit    DesktopToast(QWidget *parent = nullptr);
    /* enqueue the message */
    void        set_message(const QString& message);
signals:
    void        do_show_toast(QString msg);
private:
    void        adjust_place();
    void        start_animation();
    void        start_close_animation();
    /* fetch from pool and display */
    void        set_message_impl(const QString& message);
    QLabel*     label;
    QPoint      startPos, endPos;
    int         animation_maintain_msec{500};
    int         wait_time{1000};
    QPointer<QPropertyAnimation> moveAnimation{nullptr};
    QPointer<QPropertyAnimation> fadeAnimation{nullptr};
    bool isOpening{false};
    bool isHandling{false};
    /*
     * when large amount of messages smash in,
     * pools do the job of Buffering the message
     * warning: Queue itself is not thread safe, add
     * lock if in multithread
     */
    QQueue<QString> pools;
};

#endif // DESKTOPTOAST_H

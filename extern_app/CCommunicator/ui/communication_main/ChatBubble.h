#ifndef CHATBUBBLE_H
#define CHATBUBBLE_H

#include <QWidget>

class ChatBubble : public QWidget {
	Q_OBJECT
public:
    ChatBubble(const QString& text, bool me, QPixmap& avatar, QWidget* parent = nullptr);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;

signals:

private:
    QPixmap avatar;
    QString text;
    bool me;
};

#endif // CHATBUBBLE_H

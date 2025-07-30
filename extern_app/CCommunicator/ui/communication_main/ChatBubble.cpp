#include "ChatBubble.h"
#include <QPainter>
#include <QPainterPath>
namespace {
static constexpr QSize avatarSize = { 40, 40 };
}

ChatBubble::ChatBubble(const QString& text, bool me, QPixmap& avatar, QWidget* parent)
    : QWidget(parent)
    , text(text)
    , me(me)
    , avatar(avatar) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    setMinimumHeight(40);
}

QSize ChatBubble::sizeHint() const {
    int tmp = width() * 0.6;
    int maxWidth = std::min(480, parentWidget() ? tmp : 400);
    QFontMetrics fm(font());
    QRect br = fm.boundingRect(QRect(0, 0, maxWidth, 100000),
                               Qt::TextWordWrap | Qt::AlignLeft, text);
    int h = br.height() + 20; // padding
    h = std::max(h, avatarSize.height());
    return { parentWidget() ? parentWidget()->width() : 400, h + 20 };
}

void ChatBubble::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    int margin = 10;
    int bubblePadding = 10;
    int tmp = width() * 0.6;
    int maxWidth = std::min(480, tmp);

    // avatar
    QRect avatarRect;
    if (me) {
        avatarRect = QRect(width() - avatarSize.width() - margin,
                           margin,
                           avatarSize.width(),
                           avatarSize.height());
    } else {
        avatarRect = QRect(margin,
                           margin,
                           avatarSize.width(),
                           avatarSize.height());
    }

    // text rect
    QFontMetrics fm(font());
    QRect textRect = fm.boundingRect(QRect(0, 0, maxWidth, 100000),
                                     Qt::TextWordWrap | Qt::AlignLeft, text);
    textRect.adjust(-bubblePadding, -bubblePadding, bubblePadding, bubblePadding);
    QSize bubbleSize = textRect.size();

    QRect bubbleRect;
    if (me) {
        bubbleRect = QRect(avatarRect.left() - margin - bubbleSize.width(),
                           avatarRect.top(),
                           bubbleSize.width(),
                           bubbleSize.height());
    } else {
        bubbleRect = QRect(avatarRect.right() + margin,
                           avatarRect.top(),
                           bubbleSize.width(),
                           bubbleSize.height());
    }

    // avatar draw
    if (!avatar.isNull()) {
        QPainterPath path;
        path.addEllipse(avatarRect);
        p.setClipPath(path);
        p.drawPixmap(avatarRect, avatar.scaled(avatarRect.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        p.setClipping(false);
    } else {
        p.setBrush(QColor(0xCCCCCC));
        p.setPen(Qt::NoPen);
        p.drawEllipse(avatarRect);
    }

    // bubble draw
    QColor bg = me ? QColor(0x0099FF) : QColor(0xF1F1F1);
    QColor fg = me ? QColor(0xFFFFFF) : QColor(0x222222);

    p.setBrush(bg);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(bubbleRect, 8, 8);

    // text
    p.setPen(fg);
    p.drawText(bubbleRect.adjusted(bubblePadding, bubblePadding, -bubblePadding, -bubblePadding),
               Qt::TextWordWrap | Qt::AlignLeft | Qt::AlignVCenter, text);
}

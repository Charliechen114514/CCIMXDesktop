#include "SessionDrawDelegate.h"
#include "SessionContextRole.h"
#include <QPainter>
#include <QPainterPath>
namespace {
static constexpr const int contactItemHeight = 64;
static constexpr QSize avatarSize = { 40, 40 };
}

SessionDrawDelegate::SessionDrawDelegate(QObject* parent)
    : QStyledItemDelegate { parent } {
}

void SessionDrawDelegate::paint(QPainter* p, const QStyleOptionViewItem& opt, const QModelIndex& idx) const {
    p->save();
    paintSelectedBkground(p, opt, idx);
    paintAvatar(p, opt, idx);
    paintText(p, opt, idx);
    p->restore();
}

QSize SessionDrawDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const {
    return { 0, contactItemHeight };
}

void SessionDrawDelegate::paintSelectedBkground(QPainter* p, const QStyleOptionViewItem& opt, const QModelIndex& idx) const {
    QRect r = opt.rect;
    bool selected = opt.state & QStyle::State_Selected;

    if (selected) {
        p->fillRect(r, QColor(0x0099FF));
    } else if (opt.state & QStyle::State_MouseOver) {
        p->fillRect(r, QColor(0xF5F5F5));
    }
}

void SessionDrawDelegate::paintAvatar(QPainter* p, const QStyleOptionViewItem& opt, const QModelIndex& idx) const {
    QRect r = opt.rect;
    QRect avatarRect(r.left() + 12, r.top() + (r.height() - avatarSize.height()) / 2, avatarSize.width(), avatarSize.height());
    QPixmap avatar = idx.data(RoleAvatar).value<QPixmap>();
    if (!avatar.isNull()) {
        QPainterPath path;
        path.addEllipse(avatarRect);
        p->setClipPath(path);
        p->drawPixmap(avatarRect, avatar.scaled(avatarRect.size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        p->setClipping(false);
    } else {
        p->setBrush(QColor(0xCCCCCC));
        p->setPen(Qt::NoPen);
        p->drawEllipse(avatarRect);
    }
}

void SessionDrawDelegate::paintText(QPainter* p, const QStyleOptionViewItem& opt, const QModelIndex& idx) const {
    QRect r = opt.rect;
    bool selected = opt.state & QStyle::State_Selected;
    QRect avatarRect(r.left() + 12, r.top() + (r.height() - avatarSize.height()) / 2, avatarSize.width(), avatarSize.height());
    QString name = idx.data(RoleName).toString();
    QString lastMsg = idx.data(RoleLastMsg).toString();
    QString timeStr = idx.data(RoleTime).toString();

    QColor nameColor = selected ? Qt::white : QColor(0x222222);
    QColor lastColor = selected ? QColor(255, 255, 255, 200) : QColor(0x999999);
    QColor timeColor = selected ? Qt::white : QColor(0x999999);

    QFont nameFont = opt.font;
    nameFont.setPointSize(opt.font.pointSize() + 1);
    nameFont.setBold(true);
    QFontMetrics nfm(nameFont);
    QFontMetrics lfm(opt.font);

    int textLeft = avatarRect.right() + 10;
    int textRightPadding = 60;
    QRect nameRect(textLeft, r.top() + 10, r.width() - textLeft - textRightPadding, nfm.height());
    QRect lastRect(textLeft, r.bottom() - 12 - lfm.height(), r.width() - textLeft - textRightPadding, lfm.height());
    QRect timeRect(r.right() - 50, r.top() + 10, 48, nfm.height());

    p->setFont(nameFont);
    p->setPen(nameColor);
    p->drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter, nfm.elidedText(name, Qt::ElideRight, nameRect.width()));

    p->setFont(opt.font);
    p->setPen(lastColor);
    p->drawText(lastRect, Qt::AlignLeft | Qt::AlignVCenter, lfm.elidedText(lastMsg, Qt::ElideRight, lastRect.width()));

    p->setPen(timeColor);
    p->drawText(timeRect, Qt::AlignRight | Qt::AlignVCenter, timeStr);

    int unread = idx.data(RoleUnread).toInt();

    if (unread <= 0)
        return;
    QString badge = unread > 99 ? "99+" : QString::number(unread);
    QFont bf = opt.font;
    bf.setPointSize(bf.pointSize() - 1);
    QFontMetrics bfm(bf);

    int w = std::max(18, bfm.horizontalAdvance(badge) + 10);
    QRect badgeRect(timeRect.right() - w + 2, lastRect.top(), w, 18);

    p->setRenderHint(QPainter::Antialiasing);
    p->setBrush(QColor(0xFF3B30));
    p->setPen(Qt::NoPen);
    p->drawRoundedRect(badgeRect, 9, 9);

    p->setPen(Qt::white);
    p->setFont(bf);
    p->drawText(badgeRect, Qt::AlignCenter, badge);
}

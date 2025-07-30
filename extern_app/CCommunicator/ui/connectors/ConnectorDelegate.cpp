#include "ConnectorDelegate.h"
#include "ConnectorEnumType.h"
#include <QPainter>
#include <QPainterPath>
ConnectorDelegate::ConnectorDelegate(QObject* parent)
    : QStyledItemDelegate { parent } {
}

void ConnectorDelegate::paint(QPainter* p, const QStyleOptionViewItem& opt, const QModelIndex& idx) const {
    p->save();
    QRect r = opt.rect;
    bool selected = opt.state & QStyle::State_Selected;
    if (selected)
        p->fillRect(r, QColor(0x0099FF));
    else if (opt.state & QStyle::State_MouseOver)
        p->fillRect(r, QColor(0xF5F5F5));

    QPixmap avatar = idx.data(RoleAvatar).value<QPixmap>();
    QRect avatarRect(r.left() + 12, r.top() + (r.height() - avatarSize.height()) / 2,
                     avatarSize.width(), avatarSize.height());
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

    QString name = idx.data(RoleName).toString();
    QString status = idx.data(RoleStatus).toString();
    QColor nameColor = selected ? Qt::white : QColor(0x222222);
    QColor statusColor = selected ? QColor(255, 255, 255, 200) : QColor(0x777777);

    QFont fn = opt.font;
    fn.setPointSize(fn.pointSize() + 1);
    fn.setBold(true);
    p->setFont(fn);
    p->setPen(nameColor);
    QRect nameR(avatarRect.right() + 10, r.top() + 12,
                r.width() - avatarRect.right() - 120, fn.pointSize() * 2);
    p->drawText(nameR, Qt::AlignLeft | Qt::AlignVCenter, name);

    p->setFont(opt.font);
    p->setPen(statusColor);
    QRect statusR(nameR.left(), r.bottom() - 20, nameR.width(), 18);
    p->drawText(statusR, Qt::AlignLeft | Qt::AlignVCenter, status);

    p->restore();
}

QSize ConnectorDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const {
    return { 0, contactHeight };
}

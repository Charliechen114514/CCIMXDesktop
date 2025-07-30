#ifndef CONNECTORDELEGATE_H
#define CONNECTORDELEGATE_H

#include <QStyledItemDelegate>

class ConnectorDelegate : public QStyledItemDelegate {
public:
    explicit ConnectorDelegate(QObject* parent = nullptr);
    void paint(QPainter* p, const QStyleOptionViewItem& opt, const QModelIndex& idx) const override;
    QSize sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const override;
};

static const QSize avatarSize(40, 40);
static const int contactHeight = 64;

#endif // CONNECTORDELEGATE_H

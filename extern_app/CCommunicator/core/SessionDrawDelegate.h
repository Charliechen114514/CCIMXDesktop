#ifndef SESSIONDRAWDELEGATE_H
#define SESSIONDRAWDELEGATE_H
#include <QStyledItemDelegate>

class SessionDrawDelegate : public QStyledItemDelegate {
public:
    explicit SessionDrawDelegate(QObject* parent = nullptr);
    void paint(QPainter* p, const QStyleOptionViewItem& opt, const QModelIndex& idx) const override;

    QSize sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const override;

private:
    void paintSelectedBkground(QPainter* p, const QStyleOptionViewItem& opt, const QModelIndex& idx) const;
    void paintAvatar(QPainter* p, const QStyleOptionViewItem& opt, const QModelIndex& idx) const;
    void paintText(QPainter* p, const QStyleOptionViewItem& opt, const QModelIndex& idx) const;
    void paintUnread(QPainter* p, const QStyleOptionViewItem& opt, const QModelIndex& idx) const;
};

#endif // SESSIONDRAWDELEGATE_H

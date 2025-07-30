#ifndef CONNECTORSWIDGET_H
#define CONNECTORSWIDGET_H

#include <QWidget>
class QListView;
class QStandardItemModel;
class AddPanel;

class ConnectorsWidget : public QWidget {
	Q_OBJECT
public:
    explicit ConnectorsWidget(QWidget* parent = nullptr);
    void addContact(const QString& name, const QString& status = QString(),
                    const QPixmap& avatar = QPixmap());

    void clearContacts();
signals:
    void contactClicked(const QString& name, const QPixmap& avatar);
    void request_new_connections(const QString& name, const QString& ip, const int port);

protected:
    bool eventFilter(QObject* watched, QEvent* ev) override;
private slots:
    void onCurrentChanged(const QModelIndex& cur, const QModelIndex&);
    void showAddPanel();
    void onAddSubmitted(const QString& name);

private:
    QListView* listview;
    QStandardItemModel* standard_model;
    QToolButton* btnAdd;
    AddPanel* addPanel;
};

#endif // CONNECTORSWIDGET_H

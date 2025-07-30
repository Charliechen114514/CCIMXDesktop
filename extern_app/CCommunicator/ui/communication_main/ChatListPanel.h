#ifndef CHATLISTPANEL_H
#define CHATLISTPANEL_H
#include "core/ListContextInfo.h"
#include <QWidget>
class QLineEdit;
class QStandardItemModel;
class QListView;
class Session;

class ChatListPanel : public QWidget {
    Q_OBJECT
    static constexpr const unsigned short MAX_WIDTH = 300;

public:
    explicit ChatListPanel(QWidget* parent);
    void append_context(Session* s, const ListContextInfo& info);
    void append_context(Session* s, ListContextInfo&& info);
    bool request_remove(const QString& name);

    ListContextInfo request_info(Session* s) const;

signals:
    void request_search(const QString& target_name);
    void currentContactChanged(Session* s);

private:
    QLineEdit* search_edit;
    QStandardItemModel* standard_model;
    QListView* listview;
    QMap<Session*, ListContextInfo> contextInfos;
    void config_view_and_model();
    void init_searchbar();
    void sync_once();
    void process_new_add(const ListContextInfo& info);
private slots:
    void filterText(const QString& t);
    void onCurrentChanged(const QModelIndex& current, const QModelIndex&);
};

#endif // CHATLISTPANEL_H

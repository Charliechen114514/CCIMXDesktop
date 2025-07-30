#include "ChatListPanel.h"
#include "core/SessionContextRole.h"
#include "core/SessionDrawDelegate.h"
#include "core/sessions/Session.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QStandardItemModel>
ChatListPanel::ChatListPanel(QWidget* parent)
    : QWidget(parent) {
    setMaximumWidth(MAX_WIDTH);
    listview = new QListView(this);
    listview->setItemDelegate(new SessionDrawDelegate(this));
    listview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listview->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    listview->setSelectionMode(QAbstractItemView::SingleSelection);
    listview->setMouseTracking(true);
    listview->setStyleSheet("QListView{"
                            "border:none;"
                            "background:#FFFFFF;"
                            "} "
                            "QListView::item:selected{"
                            "background:#0099FF; "
                            "color:white;"
                            "}");

    standard_model = new QStandardItemModel(this);
    listview->setModel(standard_model);
    auto* root = new QVBoxLayout(this);
    setLayout(root);
    init_searchbar();
    root->addWidget(listview);

    QItemSelectionModel* selectionModel = listview->selectionModel();
    connect(selectionModel, &QItemSelectionModel::currentChanged,
            this, &ChatListPanel::onCurrentChanged);
}

void ChatListPanel::append_context(Session* s, const ListContextInfo& info) {
    auto it = contextInfos.insert(s, info);
    if (it != contextInfos.end()) {
        process_new_add(info);
    } else {
        qWarning() << "Duplicate add!";
    }
}

void ChatListPanel::append_context(Session* s, ListContextInfo&& info) {
    const auto& _info = info;
    auto it = contextInfos.insert(s, info);
    if (it != contextInfos.end()) {
        process_new_add(_info);
    } else {
        qWarning() << "Duplicate add!";
    }
}

bool ChatListPanel::request_remove(const QString& name) {
    const auto it = std::find_if(
        contextInfos.constBegin(), contextInfos.constEnd(),
        [name](const ListContextInfo& info) {
            return info.get_markable_name() == name;
        });

    if (it != contextInfos.constEnd()) {
        contextInfos.erase(it);
        return true;
    }
    return false;
}

ListContextInfo ChatListPanel::request_info(Session* s) const {
    auto finder = contextInfos.find(s);
    if (finder != contextInfos.constEnd()) {
        return finder.value();
    }
    qDebug() << "Can not find the target";
    return { "", s->sessionID() };
}

void ChatListPanel::init_searchbar() {
    auto* searchBar = new QWidget;
    searchBar->setFixedHeight(48);
    auto* hl = new QHBoxLayout(searchBar);
    hl->setContentsMargins(8, 8, 8, 8);

    search_edit = new QLineEdit;
    search_edit->setPlaceholderText("🔍 搜索");
    search_edit->setClearButtonEnabled(true);
    search_edit->setFixedHeight(32);
    search_edit->setStyleSheet("QLineEdit{"
                               "border-radius:16px;"
                               "background:#F2F2F2;"
                               "border:none;"
                               "padding-left:12px;"
                               "}");
    hl->addWidget(search_edit);
    layout()->addWidget(searchBar);
}

void ChatListPanel::sync_once() {
    standard_model->clear();
    for (const auto& each : std::as_const(contextInfos)) {
        process_new_add(each);
    }
}

void ChatListPanel::process_new_add(const ListContextInfo& info) {
    QStandardItem* item = new QStandardItem();
    item->setData(info.avatar(), RoleAvatar);
    item->setData(info.get_markable_name(), RoleName);
    item->setData(info.getDisplayText(), RoleLastMsg);
    item->setData(info.queryDateTime().toString(), RoleTime);
    item->setData(info.getUnread(), RoleUnread);
    item->setData(info.uuid(), RoleUuid);
    standard_model->appendRow(item);
}

void ChatListPanel::filterText(const QString& t) {
    for (int i = 0; i < standard_model->rowCount(); ++i) {
        auto idx = standard_model->index(i, 0);
        bool match = standard_model->data(idx, RoleName).toString().contains(t, Qt::CaseInsensitive);
        listview->setRowHidden(i, !match);
    }
}

void ChatListPanel::onCurrentChanged(const QModelIndex& current, const QModelIndex&) {
    if (!current.isValid())
        return;
    QString uuid = current.data(RoleUuid).toString();
    const auto it = std::find_if(
        contextInfos.constBegin(), contextInfos.constEnd(),
        [uuid](const ListContextInfo& info) {
            return info.uuid() == uuid;
        });

    if (it != contextInfos.constEnd()) {
        qDebug() << "Find Unique!";
        emit currentContactChanged(it.key());
    }
}

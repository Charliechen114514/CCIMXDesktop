#include "ConnectorsWidget.h"
#include "ConnectorDelegate.h"
#include "ConnectorEnumType.h"
#include "connectors/AddPanel.h"
#include <QListView>
#include <QMouseEvent>
#include <QStandardItem>
#include <QToolButton>
#include <QVBoxLayout>
ConnectorsWidget::ConnectorsWidget(QWidget* parent)
    : QWidget { parent } {
    auto* lo = new QVBoxLayout(this);
    lo->setContentsMargins(0, 0, 0, 0);
    lo->setSpacing(0);

    QWidget* toolbar = new QWidget(this);
    lo->addWidget(toolbar, 0);

    auto* hLayout = new QHBoxLayout(toolbar);
    toolbar->setLayout(hLayout);
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);

    btnAdd = new QToolButton(this);
    btnAdd->setText("＋");
    btnAdd->setToolTip("添加联系人");
    btnAdd->setFixedSize(48, 48);
    hLayout->addWidget(btnAdd, 0, Qt::AlignCenter);
    connect(btnAdd, &QToolButton::clicked, this, &ConnectorsWidget::showAddPanel);
    listview = new QListView;
    listview->setItemDelegate(new ConnectorDelegate(this));
    standard_model = new QStandardItemModel(this);
    listview->setModel(standard_model);
    listview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listview->setSelectionMode(QAbstractItemView::SingleSelection);
    listview->setMouseTracking(true);
    listview->setStyleSheet("QListView{border:none;background:#FFFFFF;} "
                            "QListView::item:selected{background:#0099FF;color:white;}");
    lo->addWidget(listview);

    connect(listview->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &ConnectorsWidget::onCurrentChanged);

    addPanel = new AddPanel(this);
    connect(addPanel, &AddPanel::addSubmitted,
            this, &ConnectorsWidget::onAddSubmitted);
    connect(addPanel, &AddPanel::request_new_connection,
            this, &ConnectorsWidget::request_new_connections);
    qApp->installEventFilter(this);
}

void ConnectorsWidget::addContact(const QString& name,
                                  const QString& status,
                                  const QPixmap& avatar) {
    QStandardItem* it = new QStandardItem;
    it->setData(avatar, RoleAvatar);
    it->setData(name, RoleName);
    it->setData(status, RoleStatus);
    standard_model->appendRow(it);
}

void ConnectorsWidget::clearContacts() {
    standard_model->clear();
}

bool ConnectorsWidget::eventFilter(QObject* watched, QEvent* ev) {
    if (addPanel->isVisible() && ev->type() == QEvent::MouseButtonPress) {
        QPoint gp = static_cast<QMouseEvent*>(ev)->globalPosition().toPoint();
        if (!addPanel->geometry().contains(gp)) {
            addPanel->close();
            qApp->removeEventFilter(this);
        }
    }
    return QWidget::eventFilter(watched, ev);
}

void ConnectorsWidget::showAddPanel() {
    QPoint pos = btnAdd->mapToGlobal(QPoint(0, btnAdd->height()));
    addPanel->move(pos);
    addPanel->show();
    addPanel->raise();
    addPanel->setFocus();
}

void ConnectorsWidget::onAddSubmitted(const QString& name) {
    addContact(name, "Waiting...");
    addPanel->hide();
}

void ConnectorsWidget::onCurrentChanged(const QModelIndex& cur, const QModelIndex&) {
    if (!cur.isValid())
        return;
    emit contactClicked(cur.data(RoleName).toString(),
                        cur.data(RoleAvatar).value<QPixmap>());
}

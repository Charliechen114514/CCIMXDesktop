#include "InfoWidget.h"
#include <QHeaderView>
#include <QHostInfo>
#include <QLabel>
#include <QListWidget>
#include <QTableWidget>
#include <QVBoxLayout>
InfoWidget::InfoWidget(QWidget* parent)
    : QWidget { parent } {
    auto* root = new QVBoxLayout(this);
    root->setContentsMargins(20, 20, 20, 20);
    root->setSpacing(16);

    QLabel* titleLabel = new QLabel("Local Info", this);
    titleLabel->setStyleSheet("font-size:44px; font-weight:600;");
    root->addWidget(titleLabel);
    infoTable = new QTableWidget(2, 2);
    infoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    infoTable->setFocusPolicy(Qt::NoFocus);
    infoTable->setSelectionMode(QAbstractItemView::NoSelection);

    infoTable->setHorizontalHeaderLabels({ "Attribute", "Value" });

    infoTable->verticalHeader()->hide();
    infoTable->setShowGrid(false);

    infoTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    infoTable->horizontalHeader()->setStyleSheet(
        "QHeaderView::section { "
        "    background-color: #f0f0f0; "
        "    border: 0px;"
        "    padding: 5px;"
        "}"
        "QHeaderView::section:last { border-right: 0px; }");

    infoTable->setStyleSheet(
        "QTableWidget::item { "
        "font-size: 32px; "
        "padding: 10px; "
        "}");
    root->addWidget(infoTable);
    auto f = infoTable->font();
    f.setBold(true);
    f.setPointSize(18);
    infoTable->setFont(f);

    QString hostname = QHostInfo::localHostName();
    QString ip = "127.0.0.1";

    QTableWidgetItem* nameKey
        = new QTableWidgetItem("Device Name:");
    QTableWidgetItem* nameValue = new QTableWidgetItem(hostname);
    infoTable->setItem(0, 0, nameKey);
    infoTable->setItem(0, 1, nameValue);

    QTableWidgetItem* ipKey = new QTableWidgetItem("Local IP:");
    QTableWidgetItem* ipValue = new QTableWidgetItem(ip);
    infoTable->setItem(1, 0, ipKey);
    infoTable->setItem(1, 1, ipValue);

    portTitle = new QLabel("Open Ports");
    portTitle->setStyleSheet("font-size:32px;"
                             "font-weight:600;");
    root->addWidget(portTitle);

    portList = new QListWidget;
    portList->setFrameShape(QFrame::NoFrame);
    portList->addItems({ "-1" });

    QFont portFont = portList->font();
    portFont.setPointSize(22);
    portList->setFont(portFont);
    portList->setFocusPolicy(Qt::NoFocus);
    // 样式表
    portList->setStyleSheet(R"(
    QListWidget {
        background: #FAFAFA;
        border: 1px solid #E0E0E0;
    }
    QListWidget::item {
        padding: 6px 10px;
    }
    QListWidget::item:selected {
        background: #0099FF;
        color: white;
    }
)");

    root->addWidget(portList, 1);
}

void InfoWidget::show_current_port(const int port) {
    portList->clear();
    portList->addItem(QString::number(port));
}

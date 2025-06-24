#include "ConfigureUiPairs.h"
#include <QMessageBox>
#include <QStackedWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
ConfigureUiPairs::ConfigureUiPairs(QTreeWidget* treeWidget, QStackedWidget* stackedWidget)
    : QObject(treeWidget) {
    this->treeWidget = treeWidget;
    this->stackedWidget = stackedWidget;
    connect(treeWidget, &QTreeWidget::itemClicked,
            this, &ConfigureUiPairs::process_switch_sessions);
}

QTreeWidgetItem* ConfigureUiPairs::install_mappings(
    const QString& itemName, QTreeWidgetItem* parent, QWidget* installed_widgets) {
    QTreeWidgetItem* item;
    // if we provide a parent, bind to the sessions
    item = parent ? new QTreeWidgetItem(parent)
                  : new QTreeWidgetItem(treeWidget);

    item->setText(0, itemName);

    mappings.insert(item, installed_widgets);
    stackedWidget->addWidget(installed_widgets);
    return item;
}

void ConfigureUiPairs::process_switch_sessions(QTreeWidgetItem* item) {

    auto it = mappings.find(item);
    if (it == mappings.end()) {
        QMessageBox::critical(treeWidget, "Configuration Error",
                              "Unable to locate configuration UI for the selected item. "
                              "This may indicate a bug. Please contact the developer.");

        return;
    }
    // now we can handle the switch
    stackedWidget->setCurrentWidget(it.value());
}

#include "ToolLeftWidgets.h"
#include "tools/SimpleTools.h"
#include <QButtonGroup>
#include <QToolButton>
#include <QVBoxLayout>
ToolLeftWidgets::ToolLeftWidgets(QWidget* parent)
    : QWidget { parent } {
    QString qss_str;
    try {
        qss_str = SimpleTools::readQss(":/qss/styles/left_tools.qss");
    } catch (const std::exception& e) {
        qDebug() << e.what();
    }
    this->setStyleSheet(qss_str);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    this->setLayout(layout);
    action_group = new QButtonGroup(this);
    action_group->setExclusive(true);
}

void ToolLeftWidgets::install_toolbuttons(
    const ToolButtonInstallPackage package) {
    auto btn = new QToolButton;
    btn->setIcon(package.icon);
    btn->setText(package.name);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setCheckable(true);
    btn->setEnabled(true);
    btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    action_group->addButton(btn);
    layout()->addWidget(btn);
    connect(btn, &QToolButton::clicked, this, package.callback);
}

#include "ToolPanel.h"
#include <QToolButton>
#include <QVBoxLayout>
namespace {
QToolButton* add_button(const QString& text, const QString& tooltip, QWidget* parent) {
    QToolButton* button = new QToolButton(parent);
    button->setToolTip(tooltip);
    button->setText(text);
    button->setAutoExclusive(true);
    button->setCheckable(true);
    parent->layout()->addWidget(button);

    // set the square size
    int shell_width = parent->width() - 5;
    button->setFixedSize(shell_width, shell_width);
    return button;
}
}

ToolPanel::ToolPanel(QWidget* parent)
    : QWidget { parent } {
    setFixedWidth(ToolsEnums::FIXED_TOOLWIDTH);

    // setlayout
    auto layout = new QVBoxLayout(this);
    setLayout(layout);
    layout->setContentsMargins(0, 8, 0, 8);
    layout->setSpacing(12);
    filled_mappings();
    init_stylesheets();
}

void ToolPanel::init_stylesheets() {
    setStyleSheet(R"(
            LeftBar { background:#F4F4F4; }
            QToolButton {
                border: none; border-radius: 8px; font-size: 20px;
            }
            QToolButton:checked, QToolButton:hover {
                background:#E6E6E6;
            }
        )");
}

void ToolPanel::filled_mappings() {
    mappings.insert(
        add_button("👤", "我的", this), ToolsEnums::Functionality::MINE);

    auto mainChecked = add_button("💬", "消息", this);
    mainChecked->setChecked(true);
    mappings.insert(mainChecked, ToolsEnums::Functionality::MESSAGE);
    mappings.insert(
        add_button("👥", "联系人", this), ToolsEnums::Functionality::CONNECTORS);

    auto vlayout = dynamic_cast<QVBoxLayout*>(layout());
    vlayout->addStretch();
    mappings.insert(add_button("⚙️", "设置", this), ToolsEnums::Functionality::SETTINGS);

    auto keys = mappings.keys();
    for (auto& key : keys) {
        connect(key, &QToolButton::clicked,
                this, [this]() {
                    QToolButton* button = qobject_cast<QToolButton*>(sender());
                    auto functionality = mappings.value(button);
                    emit function_activate(functionality);
                });
    }
}

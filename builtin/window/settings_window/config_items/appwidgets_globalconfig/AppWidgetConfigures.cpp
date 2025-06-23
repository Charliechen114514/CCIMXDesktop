#include "AppWidgetConfigures.h"
#include "appwidget.h"
#include "desktopmainwindow.h"
#include "ui/UiTools/font_info_formater/FontInfoFormarter.h"
#include "ui_AppWidgetConfigures.h"
#include <QColorDialog>
#include <QFontDialog>

void AppWidgetConfigures::process_default_init_load() {
    using namespace UiTools::FontFormater;
    appWidget = new AppWidget(QPixmap(":/icons/sources/def_icon.png"), "Demo", this);
    appWidget->setDummy(true);
    info.font = appWidget->font();
    info.fontColor = Qt::black;
    info.iconSize = appWidget->iconSize();
    ui->display_sessions->layout()->addWidget(appWidget);
    ui->font_label->setPlainText(describeFont(appWidget->currentFont()));
    ui->icon_size_spinbox->setValue(appWidget->iconSize());
    ui->btn_show_color->setStyleSheet(QString(
                                          "background-color: %1;"
                                          "border: 1px solid gray;")
                                          .arg(QColor(0, 0, 0).name()));
}

AppWidgetConfigures::AppWidgetConfigures(DesktopMainWindow* window, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::AppWidgetConfigures) {
	ui->setupUi(this);
    this->window = window;
    process_default_init_load();
    connect(ui->icon_size_spinbox, &QSpinBox::valueChanged,
            this, &AppWidgetConfigures::process_spinbox_change);
    connect(ui->pushButton, &QPushButton::clicked, this, [this]() {
        this->window->process_set_appwidgets_config(info);
    });
}

AppWidgetConfigures::~AppWidgetConfigures() {
	delete ui;
}

void AppWidgetConfigures::process_spinbox_change(int size) {
    appWidget->setIconSize(size);
    info.iconSize = size;
}

void AppWidgetConfigures::on_btn_select_font_clicked() {
    using namespace UiTools::FontFormater;
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (!ok) {
        return;
    }
    appWidget->set_displayed_font(font);
    ui->font_label->setPlainText(describeFont(appWidget->currentFont()));
    info.font = font;
}

void AppWidgetConfigures::on_btn_select_color_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    if (color.isValid()) {
        appWidget->setFontColor(color);
    }
    info.fontColor = color;
    ui->btn_show_color->setStyleSheet(QString(
                                          "background-color: %1;"
                                          "border: 1px solid gray;")
                                          .arg(color.name()));
}

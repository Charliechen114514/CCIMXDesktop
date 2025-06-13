#include "AppWidgetConfigures.h"
#include "appwidget.h"
#include "desktopmainwindow.h"
#include "ui_AppWidgetConfigures.h"
#include <QColorDialog>
#include <QFontDialog>
namespace {
QString describeFont(const QFont& font) {
    QString info;
    info += QString("Family: %1\n").arg(font.family());
    info += QString("Point size: %1\n").arg(font.pointSizeF());

    if (font.weight() > QFont::Normal)
        info += "Bold\n";
    if (font.italic())
        info += "Italic\n";
    if (font.underline())
        info += "Underline\n";
    if (font.strikeOut())
        info += "Strikeout\n";
    if (font.fixedPitch())
        info += "Monospaced\n";

    if (font.letterSpacing() != 0.0)
        info += QString("Letter spacing: %1\n").arg(font.letterSpacing());
    if (font.wordSpacing() != 0.0)
        info += QString("Word spacing: %1\n").arg(font.wordSpacing());

    return info;
}

}

void AppWidgetConfigures::process_default_init_load() {
    appWidget = new AppWidget(QPixmap(":/icons/sources/def_icon.png"), "Demo", this);
    appWidget->setDummy(true);
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
    connect(ui->pushButton, &QPushButton::clicked, this, [&, this]() {
        window->process_set_appwidgets_config(info);
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

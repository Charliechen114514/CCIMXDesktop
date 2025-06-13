#include "FixedOptionWidget.h"
#include "core/coretools.h"
#include "core/wallpaper/WallPaperUtilsColliections.h"
#include "ui_FixedOptionWidget.h"
#include <QFileDialog>
FixedOptionWidget::FixedOptionWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FixedOptionWidget) {
	ui->setupUi(this);
}

void FixedOptionWidget::setPixmap(const QPixmap& pixmap) {
    ui->pixmap_label->setPixmap(pixmap);
}

QPixmap FixedOptionWidget::get_pixmap() const {
    return ui->pixmap_label->pixmap();
}

FixedOptionWidget::~FixedOptionWidget() {
	delete ui;
}

void FixedOptionWidget::handle_new_selections() {
    QStringList prefix;
    for (const auto& each : WallPaperUtilsColliections::PREFIX) {
        prefix << each;
    }
    QString path = QFileDialog::getOpenFileName(this, "Select a fixed pixmap", ".", CoreTools::fromFiltersToFilterString(prefix));
    setPixmap(QPixmap(path));
}

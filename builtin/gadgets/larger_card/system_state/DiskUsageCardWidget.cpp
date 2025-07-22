#include "DiskUsageCardWidget.h"
#include "library/platforms/DiskUsage.h"
#include "ui/gauge_widget/GaugeWidget.h"
#include "ui_DiskUsageCardWidget.h"
#include <QGraphicsDropShadowEffect>

namespace {
static constexpr const unsigned long long KB = 1024;
static constexpr const unsigned long long MB = 1024 * KB;
static constexpr const unsigned long long GB = 1024 * MB;

QString format_size(quint64 sizeInBytes) {
    if (sizeInBytes < KB)
        return QString("%1 Bytes").arg(sizeInBytes);
    else if (sizeInBytes < MB)
        return QString::number(sizeInBytes / static_cast<double>(KB), 'f', 2) + " KB";
    else if (sizeInBytes < GB)
        return QString::number(sizeInBytes / static_cast<double>(MB), 'f', 2) + " MB";
    else
        return QString::number(sizeInBytes / static_cast<double>(GB), 'f', 2) + " GB";
}

}

DiskUsageCardWidget::DiskUsageCardWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DiskUsageCardWidget) {
	ui->setupUi(this);
    gaugeWidget = new GaugeWidget(this);
    gaugeWidget->setRange(0, 100);
    gaugeWidget->setTitle("Disk");
    gaugeWidget->setUnit("%");
    ui->displayer_widget->layout()->addWidget(gaugeWidget);

    setAttribute(Qt::WA_StyledBackground);
    setAutoFillBackground(true);
    auto* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(12);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 160));
    setGraphicsEffect(shadow);

    setStyleSheet(R"(
        #DiskUsageCardWidget {
            border-radius: 16px;
            background: qlineargradient(
                x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #5D6D7E,
                stop: 1 #2C3E50
            );
        }

        #title_label {
            color: #ECF0F1;
            font-size: 32px;
            font-weight: bold;
        }

        #display_label {
            color: #ECF0F1;
            font-size: 24px;
            font-weight: bold;
        }
    )");
    qDebug() << "Attempty to refresh disk usage";
    refresh_once();
    qDebug() << "DiskUsage Card is created ready!";
}

DiskUsageCardWidget::~DiskUsageCardWidget() {
	delete ui;
}

void DiskUsageCardWidget::refresh_once() {
    DiskUsage::MetaInfo info = DiskUsage::queryOnce();
    qDebug().nospace() << "Get the MetaInfo: { "
                       << "total: " << info.total << ", "
                       << "free: " << info.free << ", "
                       << "available: " << info.available
                       << " }";
    int percentage = 100 - info.available * 100 / info.total;
    gaugeWidget->update_value(percentage);

    QString infoString = QString("Total: %1\nAvaiable: %2\nFree: %3\nUsed: %4")
                             .arg(
                                 format_size(info.total),
                                 format_size(info.available),
                                 format_size(info.free),
                                 format_size(info.total - info.free));
    ui->display_label->setText(infoString);
    qInfo().noquote() << "Refresh with disk info:\n"
                      << infoString << "free disk info Percentage: " << gaugeWidget->value();
}

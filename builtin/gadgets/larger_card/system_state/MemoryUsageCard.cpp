#include "MemoryUsageCard.h"
#include "library/platforms/MemoryStateQuery.h"
#include "ui_MemoryUsageCard.h"
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

MemoryUsageCard::MemoryUsageCard(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MemoryUsageCard) {
	ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    setAutoFillBackground(true);
    auto* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(12);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 160));
    setGraphicsEffect(shadow);
    refresh_once();
    qDebug() << "Memory Usage Card is created ready!";
}

MemoryUsageCard::~MemoryUsageCard() {
	delete ui;
}

void MemoryUsageCard::refresh_once() {
    MemoryState::MemState st = MemoryState::queryOnce();
    int usagePercent = 100 - 100 * st.avail_phys_memory / st.total_phys_memory;
    ui->memory_usage_bar->setValue(usagePercent);
    QString infoText = QString("Available Memory: %1\n➡ Total Memory: %2\n")
                           .arg(format_size(st.avail_phys_memory), format_size(st.total_phys_memory));
    ui->label->setText(infoText);
    ui->percenatge_label->setText(QString("%1%").arg(QString::number(usagePercent)));
    qInfo().noquote() << "Refresh with disk info:\n"
                      << infoText << "free disk info Percentage: " << usagePercent << "%";
}

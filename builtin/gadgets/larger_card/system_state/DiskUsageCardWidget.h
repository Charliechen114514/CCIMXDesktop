#ifndef DISKUSAGECARDWIDGET_H
#define DISKUSAGECARDWIDGET_H

#include <QWidget>
class GaugeWidget;
namespace Ui {
class DiskUsageCardWidget;
}

/**
 * @brief The DiskUsageCardWidget class
 */
class DiskUsageCardWidget : public QWidget {
	Q_OBJECT

public:
    explicit DiskUsageCardWidget(QWidget* parent = nullptr); ///< constructor
    ~DiskUsageCardWidget(); ///< erase
    void refresh_once(); ///< refresh once

private:
    Ui::DiskUsageCardWidget* ui;
    GaugeWidget* gaugeWidget;
};

#endif // DISKUSAGECARDWIDGET_H

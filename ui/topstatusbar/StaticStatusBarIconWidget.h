#ifndef STATICSTATUSBARICONWIDGET_H
#define STATICSTATUSBARICONWIDGET_H

#include "StatusBarIconWidget.h"

namespace Ui {
class StaticStatusBarIconWidget;
}

class StaticStatusBarIconWidget : public StatusBarIconWidget {
	Q_OBJECT

public:
    explicit StaticStatusBarIconWidget(QString name, QWidget* parent = nullptr);
	~StaticStatusBarIconWidget();
    QPixmap icon();
    void setIcon(const QPixmap& map);
    void adjustSelfHeight(int height) override;

private:
    Ui::StaticStatusBarIconWidget* ui;
};

#endif // STATICSTATUSBARICONWIDGET_H

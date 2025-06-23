#ifndef STATICSTATUSBARICONWIDGET_H
#define STATICSTATUSBARICONWIDGET_H

#include "StatusBarIconWidget.h"

namespace Ui {
class StaticStatusBarIconWidget;
}

/**
 * @brief   the static sessions widgets, using in
 *          display statically
 * 
 */
class StaticStatusBarIconWidget : public StatusBarIconWidget {
	Q_OBJECT

public:
    /**
     * @brief Construct a new Static Status Bar Icon Widget object
     * 
     * @param name 
     * @param parent 
     */
    explicit StaticStatusBarIconWidget(QString name, QWidget* parent = nullptr);
	~StaticStatusBarIconWidget();
    /**
     * @brief get the icons
     * 
     * @return QPixmap 
     */
    QPixmap icon();
    /**
     * @brief Set the Icon object
     * 
     * @param map 
     */
    void setIcon(const QPixmap& map);
    /**
     * @brief adjust the icons size
     * 
     * @param height 
     */
    void adjustSelfHeight(int height) override;

private:
    Ui::StaticStatusBarIconWidget* ui;
};

#endif // STATICSTATUSBARICONWIDGET_H

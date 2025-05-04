#ifndef APPCARDWIDGET_H
#define APPCARDWIDGET_H

#include <QWidget>

class DesktopToast;

namespace Ui {
class AppCardWidget;
}

/* App Card Widgets is simple lighted widget that is
 * only post messages to the Toast
 */
class AppCardWidget : public QWidget
{
    Q_OBJECT

public:
    Q_DISABLE_COPY(AppCardWidget);
    AppCardWidget() = delete;
    explicit AppCardWidget(DesktopToast* toast, QWidget *parent = nullptr);

    /* Icons for the current */
    virtual void setCurrentIcon(const QPixmap& icons);

    /* when system starts, app cards are supposed to do their actions
     * and if not, then do nothing
     */
    virtual void invoke_preLaunch_work(void) = 0;

    ~AppCardWidget();

protected:
    /* each concrete app is required to reset the app status */
    virtual void       postAppCardWidget() = 0;
    DesktopToast*      binding_toast;
    Ui::AppCardWidget*  ui;
    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // APPCARDWIDGET_H

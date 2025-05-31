#ifndef APPCARDWIDGET_H
#define APPCARDWIDGET_H

#include <QWidget>

class DesktopToast;

namespace Ui {
class AppCardWidget;
}

/**
 * @brief AppCardWidget is a lightweight widget used to post messages to a DesktopToast.
 *
 * This is an abstract base class representing an application card UI component.
 * It is responsible for handling pre-launch work and posting messages via toast notifications.
 */
class AppCardWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Disable copy constructor and assignment operator.
     */
    Q_DISABLE_COPY(AppCardWidget);

    /**
     * @brief Default constructor deleted to force usage of parameterized constructor.
     */
    AppCardWidget() = delete;

    /**
     * @brief Constructs an AppCardWidget.
     * @param toast Pointer to the DesktopToast object used to show messages.
     * @param parent Optional parent widget.
     */
    explicit AppCardWidget(DesktopToast* toast, QWidget* parent = nullptr);

    /**
     * @brief Virtual destructor.
     */
    ~AppCardWidget();

    /**
     * @brief Set the current icon for the app card.
     *
     * This function allows derived classes to customize the app card icon
     * by providing a QPixmap.
     *
     * @param icons The pixmap to be used as the icon.
     */
    virtual void setCurrentIcon(const QPixmap& icons);

    /**
     * @brief Abstract method to invoke pre-launch operations.
     *
     * Derived classes should implement this to perform necessary
     * preparations before the system starts or the app card becomes active.
     */
    virtual void invoke_preLaunch_work() = 0;

protected:
    /**
     * @brief Abstract method to post messages to the bound DesktopToast.
     *
     * Derived classes implement this to send notifications or status updates
     * through the toast system.
     */
    virtual void postAppCardWidget() = 0;

    DesktopToast* binding_toast;  ///< Pointer to the toast widget used for posting messages.
    Ui::AppCardWidget* ui;         ///< UI object generated from the Qt Designer form.

public:
    /**
     * @brief Event filter to handle user interaction events.
     * @param watched The QObject being watched.
     * @param event The event being filtered.
     * @return true if the event was handled, otherwise false.
     */
    bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // APPCARDWIDGET_H

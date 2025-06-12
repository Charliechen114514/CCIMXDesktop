#ifndef APPWIDGET_H
#define APPWIDGET_H

#include <QIcon>
#include <QWidget>

class ApplicationWrapper;

namespace Ui {
class AppWidget;
}

/**
 * @brief The AppWidget class represents an application widget placed on the desktop.
 *
 * It displays an icon and app name, manages the underlying ApplicationWrapper,
 * and handles launching and status updates.
 */
class AppWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs an AppWidget with the given icon and app name.
     * @param icon The icon to display.
     * @param name The application name.
     * @param parent Optional parent widget.
     */
    explicit AppWidget(const QPixmap& icon, const QString& name, QWidget* parent = nullptr);

    /**
     * @brief Bind an ApplicationWrapper instance to this widget.
     * @param wrapper Pointer to the ApplicationWrapper.
     */
    void bindApp(ApplicationWrapper* wrapper);

    /**
     * @brief Get the bound ApplicationWrapper.
     * @return Pointer to the ApplicationWrapper.
     */
    ApplicationWrapper* get_app() const;

    /**
     * @brief Set the icon displayed by this widget.
     * @param icon The pixmap to set as icon.
     */
    void setIcon(const QPixmap& icon) noexcept;

    /**
     * @brief Set the application name displayed by this widget.
     * @param name The name string.
     */
    void setAppName(const QString& name) noexcept;

    /**
     * @brief Set this widget as dummy mode.
     *
     * When set to dummy, the widget is visible but does not respond
     * to any real interaction or launch requests.
     * @param dummy True to enable dummy mode; false to disable.
     */
    void setDummy(bool dummy);

    /**
     * @brief Get the current icon pixmap.
     * @return The icon pixmap.
     */
    QPixmap icon() const;

    void setIconSize(int iconSize);

    /**
     * @brief iconSize
     * @return icon size
     */
    int iconSize() const;

    /**
     * @brief Show or hide only the icon (hides other UI elements).
     * @param st True to show icon only; false to show full widget.
     */
    void showIconOnly(bool st);

    /**
     * @brief Get the application name.
     * @return The app name string.
     */
    QString app_name() const;

    /**
     * @brief set_displayed_font setFonts of displayed label
     * @param f
     */
    void set_displayed_font(const QFont& f);

    /**
     * @brief currentFont get the current displaying font
     * @return displaying font
     */
    QFont currentFont() const;

    /**
     * @brief setFontColor set the font color
     * @param color
     */
    void setFontColor(const QColor& color);

    /**
     * @brief Destructor.
     */
    ~AppWidget();

    /**
     * @brief Enum representing the application status.
     */
    enum class AppStatus {
        AppOk, ///< Application is running or available.
        AppNonExsits ///< Application does not exist.
    };

signals:
    /**
     * @brief Signal emitted to notify about the application status.
     * @param status The current status of the app.
     */
    void postAppStatus(AppWidget::AppStatus status);

protected:
    /**
     * @brief Event filter to handle user interaction events.
     * @param watched The object being watched.
     * @param event The event being filtered.
     * @return true if the event was handled, false otherwise.
     */
    bool eventFilter(QObject* watched, QEvent* event) override;

    /**
     * @brief Dispatch the application via the ApplicationWrapper.
     */
    virtual void do_daptch();

private:
    Ui::AppWidget* ui; ///< ui handling
    bool dummy_state { false }; ///< Whether the widget is in dummy mode (non-interactive).
    ApplicationWrapper* app_internal { nullptr }; ///< The application wrapper bound to this widget.
    int icon_size;
};

#endif // APPWIDGET_H

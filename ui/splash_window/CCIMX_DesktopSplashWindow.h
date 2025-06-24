#ifndef CCIMX_DESKTOPSPLASHWINDOW_H
#define CCIMX_DESKTOPSPLASHWINDOW_H

#include <QSplashScreen>

class DesktopMainWindow;
class QProgressBar;

/**
 * @brief The CCIMX_DesktopSplashWindow class
 * class handles the init stage displays
 */
class CCIMX_DesktopSplashWindow : public QSplashScreen {
	Q_OBJECT
public:
    /**
     * @brief CCIMX_DesktopSplashWindow
     * @param holdingWindow
     */
    explicit CCIMX_DesktopSplashWindow(
        DesktopMainWindow* holdingWindow);
    /**
     * @brief close called when the init comes to the end
     */
    void close();
private slots:
    /**
     * @brief handle_accessment handle the accessiments
     * @param message
     * @param value
     */
    void handle_accessment(const QString& message, const int value);

protected:
    /**
     * @brief drawContents
     * @param painter
     */
    void drawContents(QPainter* painter) override;
    QProgressBar* progressBar; ///< progress sessions

private:
    DesktopMainWindow* holdingWindow; ///< holding window
};

#endif // CCIMX_DESKTOPSPLASHWINDOW_H

#ifndef CCIMX_DESKTOPSPLASHWINDOW_H
#define CCIMX_DESKTOPSPLASHWINDOW_H

#include <QSplashScreen>

class DesktopMainWindow;
class QProgressBar;
class QPropertyAnimation;

/**
 * @brief The CCIMX_DesktopSplashWindow class
 * class handles the init stage displays
 */
class CCIMX_DesktopSplashWindow : public QSplashScreen {
	Q_OBJECT
    static constexpr const unsigned int CLOSE_DURATION = 500;

public:
    /**
     * @brief CCIMX_DesktopSplashWindow
     */
    CCIMX_DesktopSplashWindow();
    /**
     * @brief close called when the init comes to the end
     */
    void close();
public slots:
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
    QPropertyAnimation* progressAnim = nullptr; ///< processing bars
private:
    int progressValue; ///< processing value
    QString currentMessage; ///< current displaying
};

#endif // CCIMX_DESKTOPSPLASHWINDOW_H

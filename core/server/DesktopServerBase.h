#ifndef DESKTOPSERVERBASE_H
#define DESKTOPSERVERBASE_H
#include "library/simple_gerseter/simple_getseter.hpp"
#include <QObject>

/**
 * @brief The DesktopServerBase class
 * notifies the backend Server for desktop
 * with eventloop engaged in desktop with no
 * thread depatchable
 */
class DesktopServerBase : public QObject {
public:
    /**
     * @brief DesktopServerBase
     * @param parent
     */
    explicit DesktopServerBase(QObject* parent)
        : QObject(parent) {
    }
    virtual ~DesktopServerBase() = default;

    __PROPERTY_GETSET(bool, enabled); ///< server en/disable
    __PROPERTY_GETSET(QString, serverName); ///< server name

signals:
    void server_ready(); ///< server ready
    void server_unload(); ///< server unloaded
    void server_dead(); ///< server dead

protected:
    bool enabled { true };

private:
    QString serverName;
};

#endif // DESKTOPSERVERBASE_H

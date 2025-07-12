#ifndef DESKTOPSERVERBASE_H
#define DESKTOPSERVERBASE_H
#include "library/simple_gerseter/simple_getseter.hpp"
#include <QObject>
class DesktopServerBase : public QObject {
public:
    explicit DesktopServerBase(QObject* parent)
        : QObject(parent) {
    }
    virtual ~DesktopServerBase() = default;

    __PROPERTY_GETSET(bool, enabled); ///< property getset

protected:
    bool enabled { true };
};

#endif // DESKTOPSERVERBASE_H

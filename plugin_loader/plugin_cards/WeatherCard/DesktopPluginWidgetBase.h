#pragma once
#include <QtPlugin>
class QWidget;
/**
 * @brief The DesktopPluginWidgetBase class
 * is such a simple interface class marking in
 * Dynamic Loadable Library, which is simply interfacable
 */
struct DesktopPluginWidgetBase {
    virtual ~DesktopPluginWidgetBase() = default;
    /**
     * @brief factorize_widget simply fetch a holding widget
     * listing in factory
     * @param parentWidget widget binding for parent
     * @return the widget created as newed out!
     */
    virtual QWidget* factorize_widget(QWidget* parentWidget) = 0;
};

// exported
Q_DECLARE_INTERFACE(
    DesktopPluginWidgetBase,
    "com.DesktopPluginWidgetBase.DesktopPluginWidgetBase/1.0");

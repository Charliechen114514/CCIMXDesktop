#ifndef TOOLLEFTWIDGETS_H
#define TOOLLEFTWIDGETS_H

#include <QWidget>

class QButtonGroup;

/**
 * @brief The ToolLeftWidgets class
 * A custom widget for displaying a vertical tool button panel.
 */
class ToolLeftWidgets : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Callback function type for tool buttons
     */
    using ToolButtonCallBack = std::function<void(void)>;

    /**
     * @brief Construct a new ToolLeftWidgets object
     * @param parent The parent QWidget
     */
    explicit ToolLeftWidgets(QWidget* parent = nullptr);

    /**
     * @brief ToolButtonInstallPackage
     * Structure for packaging a tool button's configuration
     */
    struct ToolButtonInstallPackage {
        const QString& name;              ///< Button name or label
        const QIcon& icon;                ///< Button icon
        ToolButtonCallBack callback;      ///< Callback function triggered on button press
    };

    /**
     * @brief Install a tool button into the widget
     * @param package A package containing name, icon, and callback
     */
    void install_toolbuttons(const ToolButtonInstallPackage package);

private:
    /**
     * @brief Group managing exclusive selection of buttons
     */
    QButtonGroup* action_group;
};

#endif // TOOLLEFTWIDGETS_H

#ifndef TOOLLEFTWIDGETS_H
#define TOOLLEFTWIDGETS_H

#include <QWidget>
class QButtonGroup;
class ToolLeftWidgets : public QWidget {
	Q_OBJECT
public:
    using ToolButtonCallBack = std::function<void(void)>;
    explicit ToolLeftWidgets(QWidget* parent = nullptr);

    struct ToolButtonInstallPackage {
        const QString& name;
        const QIcon& icon;
        ToolButtonCallBack callback;
    };
    void install_toolbuttons(const ToolButtonInstallPackage package);

private:
    QButtonGroup* action_group;
};

#endif // TOOLLEFTWIDGETS_H

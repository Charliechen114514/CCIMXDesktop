#ifndef TOOLPANEL_H
#define TOOLPANEL_H
#include "ToolsEnum.h"
#include <QWidget>

class ToolPanel : public QWidget {
	Q_OBJECT
public:
    explicit ToolPanel(QWidget* parent = nullptr);

signals:
    void function_activate(ToolsEnums::Functionality functionality);

private:
    QMap<QToolButton*, ToolsEnums::Functionality> mappings;
    void init_stylesheets();
    void filled_mappings();
};

#endif // TOOLPANEL_H

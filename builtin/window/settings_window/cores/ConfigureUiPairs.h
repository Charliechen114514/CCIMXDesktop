#ifndef CONFIGUREUIPAIRS_H
#define CONFIGUREUIPAIRS_H
#include <QMap>
#include <QObject>
class QTreeWidget;
class QStackedWidget;
class QTreeWidgetItem;
class QWidget;
struct ConfigureUiPairs : public QObject {
    ConfigureUiPairs() = delete;
    Q_DISABLE_COPY_MOVE(ConfigureUiPairs);
    ConfigureUiPairs(QTreeWidget* treeWidget, QStackedWidget* stackedWidget);
    QTreeWidgetItem* install_mappings(const QString& itemName, QTreeWidgetItem* parent, QWidget* installed_widgets);
private slots:
    void process_switch_sessions(QTreeWidgetItem* item);

private:
    QMap<QTreeWidgetItem*, QWidget*> mappings;
    QTreeWidget* treeWidget;
    QStackedWidget* stackedWidget;
};

#endif // CONFIGUREUIPAIRS_H

#ifndef UITOOLS_H
#define UITOOLS_H
#include <QDebug>
#include <QString>
class QGridLayout;
class QWidget;

/**
 * @brief Tools for Ui Sessions
 *
 */
namespace UiTools {

/**
 * @brief append to a gridlayout
 *
 * @param layout gridlayout
 * @param newWidget widget waiting added
 * @param columnCount maxCount
 */
void addWidgetToGridTail(QGridLayout* layout, QWidget* newWidget, int columnCount);

/**
 * @brief openIfUnvisible
 * @param window
 * @param windowName
 */
template <typename WindowType>
void openIfUnvisible(WindowType* window, const QString& windowName) {
    if (window->isVisible()) {
        qDebug() << windowName << "is already visible";
        return;
    }
    window->show();
}
};

#endif // UITOOLS_H

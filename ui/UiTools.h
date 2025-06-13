#ifndef UITOOLS_H
#define UITOOLS_H
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

};

#endif // UITOOLS_H

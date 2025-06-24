#include "UiTools.h"
#include <QDebug>
#include <QGridLayout>
namespace {
int getNextGridPosition(QGridLayout* layout, int columnCount, int& outRow, int& outCol) {
    int count = layout->count();
    outRow = 0;
    outCol = 0;
    if (count == 0)
        return 0;

    int maxIndex = count;
    outRow = maxIndex / columnCount;
    outCol = maxIndex % columnCount;
    return maxIndex;
}
}
void UiTools::addWidgetToGridTail(QGridLayout* layout, QWidget* newWidget, int columnCount) {
    int row = 0, col = 0;
    getNextGridPosition(layout, columnCount, row, col);
    layout->addWidget(newWidget, row, col);
}

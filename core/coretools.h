#ifndef CORETOOLS_H
#define CORETOOLS_H
#include <QStringList>
class QWidget;
namespace CoreTools {

/**
 * @brief enumeratefiles really enum the files with accept nameFilters
 * @param path path to the scany directory
 * @param nameFilters path To the accept file name filters
 * @return the files functions scans
 */
QStringList enumeratefiles(const QString& path, const QStringList& nameFilters);

/**
 * @brief random_float returns the random float number between min and max
 * that is Min <= random_float <= Max
 * @param min the min value
 * @param max the max value
 * @return the random float number
 * @note Min <= random_float <= Max!!!
 */
float random_float(const float min, const float max);

/**
 * @brief random_int returns the random int number between min and max
 * that is Min <= random_int <= Max
 * @param min the min value
 * @param max the max value
 * @return the random int number
 * @note Min <= random_int <= Max!!!
 */
int random_int(const int min, const int max);

/**
 * @brief fromFiltersToFilterString
 * transfer to the filters string
 * @param l
 * @return result
 */
QString fromFiltersToFilterString(const QStringList& l);

/**
 * @brief getExecutableFile sync query executables
 * @param parent
 * @return
 */
QString getExecutableFile(QWidget* parent = nullptr);

}

#endif // CORETOOLS_H

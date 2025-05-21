#ifndef MEDIAENABLESELECTFACTORY_H
#define MEDIAENABLESELECTFACTORY_H
#include <QString>
class QWidget;

/**
 * @brief The MediaEnableSelectFactory namespace provides the tools
 * @note MediaEnableSelectFactory provides some
 * using tools to select medias from file system
 * in dialog levels
 */
namespace MediaEnableSelectFactory {
/**
 * @brief get_enabled_select_medias_fromdialog
 * @details this will invoke the file dialog sync
 * @param parent parent widgets where dialogs can docked
 * @param title the title of the dialog
 * @return the selected media
 */
QString get_enabled_select_medias_fromdialog(QWidget* parent, const QString& title);

/**
 * @brief generateMediaEnableFilter
 * @details this will generate the media filter
 * @return the media filter
 */
QString generateMediaEnableFilter();

/**
 * @brief get_enabled_select_medias_fromdialog
 * @details this will invoke the file dialog sync
 * @param parent parent widgets where dialogs can docked
 * @param title the title of the dialog
 * @return the selected media
 */
QStringList get_all_enabled_select_medias_fromdialog(QWidget* parent, const QString& title);
}

#endif // MEDIAENABLESELECTFACTORY_H

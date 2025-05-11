#ifndef MEDIAENABLESELECTFACTORY_H
#define MEDIAENABLESELECTFACTORY_H
#include <QString>
class QWidget;
namespace MediaEnableSelectFactory {
/* call this to invoke sync filedialog */
QString get_enabled_select_medias_fromdialog(QWidget* parent, const QString& title);
/* generate the media file enabled */
QString generateMediaEnableFilter();
}

#endif // MEDIAENABLESELECTFACTORY_H

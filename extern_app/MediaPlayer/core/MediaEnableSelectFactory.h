#ifndef MEDIAENABLESELECTFACTORY_H
#define MEDIAENABLESELECTFACTORY_H
#include <QString>
class QWidget;
namespace MediaEnableSelectFactory {
/* call this to invoke sync filedialog */
QString get_enabled_select_medias_fromdialog(QWidget* parent, const QString& title);
/* generate the media file enabled */
QString generateMediaEnableFilter();

/* call this to invoke selecting dirents */
QStringList get_all_enabled_select_medias_fromdialog(QWidget* parent, const QString& title);
}

#endif // MEDIAENABLESELECTFACTORY_H

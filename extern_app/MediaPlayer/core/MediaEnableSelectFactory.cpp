#include "MediaEnableSelectFactory.h"
#include <QFileDialog>
#include <QMap>

QString MediaEnableSelectFactory::generateMediaEnableFilter() {
	QStringList filters;
	static const QMap<QString, QStringList> map = {
		{ "Video Files", { "mp4", "avi", "mkv" } },
		{ "Music File", { "mp3", "wav" } },
	};
	for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
		const QString& category = it.key();
		const QStringList& extensions = it.value();

		QStringList extWithWildcard;
		for (const QString& ext : extensions) {
			extWithWildcard.append("*." + ext);
		}

		filters.append(QString("%1 (%2)").arg(category, extWithWildcard.join(" ")));
	}

	return filters.join(";;");
}

QString
MediaEnableSelectFactory::
    get_enabled_select_medias_fromdialog(
        QWidget* parent, const QString& title) {
    return QFileDialog::getOpenFileName(
        parent, title, ".",
        generateMediaEnableFilter());
}

QStringList MediaEnableSelectFactory::get_all_enabled_select_medias_fromdialog(QWidget* parent, const QString& title) {
	return QFileDialog::getOpenFileNames(
		parent, title, ".",
		generateMediaEnableFilter());
}

#ifndef FILENAMEPROVIDERS_H
#define FILENAMEPROVIDERS_H
#include "FileInfoProvider.h"
#include <QColor>
#include <QMap>

class FileNameProviders : public FileInfoProvider {
public:
	FileNameProviders(CCIMXFileSystemModel* models);
	Q_DISABLE_COPY(FileNameProviders);
	inline QString provide_section_name() override {
		return "FileName";
	}
	std::pair<bool, QVariant> data(const QModelIndex& index, int role) override;
	using FileExtension = QString;
	using ColorPairs = std::pair<FileExtension, QColor>;
	void registerColorPairs(const ColorPairs& pairs);
	void inline register_special_dircolor(const QColor& t) {
		dirent_color = t;
	}

private:
	std::pair<bool, QVariant> handle_extension_color(const QModelIndex& index);
	QMap<FileExtension, QColor> mappings;
	QColor dirent_color { Qt::darkMagenta };
};

#endif // FILENAMEPROVIDERS_H

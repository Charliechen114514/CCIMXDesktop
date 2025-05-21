#ifndef FILENAMEPROVIDERS_H
#define FILENAMEPROVIDERS_H
#include "FileInfoProvider.h"
#include <QColor>
#include <QMap>

class FileNameProviders : public FileInfoProvider {
public:
	FileNameProviders(CCIMXFileSystemModel* models);
	Q_DISABLE_COPY(FileNameProviders);
	~FileNameProviders() override = default;
	/**
	 * @brief provide_section_name means everything in the name lol
	 * @return the section name
	 */
	inline QString provide_section_name() override {
		return "FileName";
	}
	/**
	 * @brief data provide the data to the views
	 * @param index the model index
	 * @param role the role of the index
	 * @return returns the file name of the index, if the data is not
	 * available, it will return with {false, {}}
	 */
	std::pair<bool, QVariant> data(const QModelIndex& index, int role) override;
	using FileExtension = QString;
	using ColorPairs = std::pair<FileExtension, QColor>;

	/**
	 * @brief registerColorPairs assigned the color shows
	 * @param pairs the pairs of the file extension and the color
	 */
	void registerColorPairs(const ColorPairs& pairs);
	/**
	 * @brief register_special_dircolor register the special dirent color
	 * @note this is the default color for the dirent
	 * @param t the color to be registered
	 */
	void inline register_special_dircolor(const QColor& t) {
		dirent_color = t;
	}

private:
	std::pair<bool, QVariant>
	handle_extension_color(const QModelIndex& index); ///< handle the extension color
	QMap<FileExtension, QColor> mappings; ///< the mappings of the color
	QColor dirent_color { Qt::darkMagenta }; ///< the color for the dirent
};

#endif // FILENAMEPROVIDERS_H

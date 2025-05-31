#ifndef FILETYPEINFO_H
#define FILETYPEINFO_H

#include "FileInfoProvider.h"

class FileTypeInfo : public FileInfoProvider {
public:
	/**
	 * @brief Construct a new File Type Info object
	 * 
	 * @param model 
	 */
	FileTypeInfo(CCIMXFileSystemModel* model);
	/**
	 * @brief Construct a new File delete defaulty
	 * 
	 */
	FileTypeInfo() = delete;
	/**
	 * @brief disable copy object
	 * 
	 */
	Q_DISABLE_COPY(FileTypeInfo);
	~FileTypeInfo() override = default;

	/**
	 * @brief provide_section_name means everything in the name lol
	 * @return the section name
	 */
	inline QString provide_section_name() override {
		return "File Type";
	}
	/**
	 * @brief data provide the data to the views
	 * @param index the model index
	 * @param role the role of the index
	 * @return returns the file type of the index, if the data is not
	 * available, it will return with {false, {}}
	 */
	std::pair<bool, QVariant> data(const QModelIndex& index, int role) override;
	/**
	 * @brief registerTypeInfo register the type info
	 * @param suffix the file suffix
	 */
	QString typeInfo(const QString& suffix) { return mappings.value(suffix); };

private:
	QMap<QString, QString> mappings;
};

#endif // FILETYPEINFO_H

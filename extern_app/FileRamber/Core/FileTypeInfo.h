#ifndef FILETYPEINFO_H
#define FILETYPEINFO_H

#include "FileInfoProvider.h"

class FileTypeInfo : public FileInfoProvider {
public:
	FileTypeInfo(CCIMXFileSystemModel* model);
	inline QString provide_section_name() override {
		return "File Type";
	}
	std::pair<bool, QVariant> data(const QModelIndex& index, int role) override;
	QString typeInfo(const QString& suffix) { return mappings.value(suffix); };

private:
	QMap<QString, QString> mappings;
};

#endif // FILETYPEINFO_H

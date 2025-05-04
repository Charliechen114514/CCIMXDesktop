#ifndef FILEINFOPROVIDER_H
#define FILEINFOPROVIDER_H
#include <QModelIndex>
#include <QString>
#include <QtClassHelperMacros>

class CCIMXFileSystemModel;
/* Interfaces are provided in virtual class */
class FileInfoProvider {
public:
	Q_DISABLE_COPY(FileInfoProvider);
	FileInfoProvider(CCIMXFileSystemModel* models) {
		this->models = models;
	};
	virtual ~FileInfoProvider() = default;
	virtual inline QString provide_section_name() = 0;
	inline void setCurrentHandlePath(const QString& path) { cached_path = path; }
	inline QString currentHandlePath() { return cached_path; }
	virtual std::pair<bool, QVariant> data(const QModelIndex& index, int role) = 0;

protected:
	CCIMXFileSystemModel* models;

private:
	QString cached_path {};
};

#endif // FILEINFOPROVIDER_H

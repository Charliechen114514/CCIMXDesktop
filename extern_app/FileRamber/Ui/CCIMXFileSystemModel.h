#ifndef CCIMXFILESYSTEMMODEL_H
#define CCIMXFILESYSTEMMODEL_H
#include <QFileSystemModel>
class FileInfoProvider;
class CCIMXFileSystemModel : public QFileSystemModel {
public:
	explicit CCIMXFileSystemModel(QObject* parent = nullptr);
	void bindProviders(QList<FileInfoProvider*>& providers) {
		this->providers = providers;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	const QList<FileInfoProvider*>& get_providers() const { return providers; }

private:
	QList<FileInfoProvider*> providers;
};

#endif // CCIMXFILESYSTEMMODEL_H

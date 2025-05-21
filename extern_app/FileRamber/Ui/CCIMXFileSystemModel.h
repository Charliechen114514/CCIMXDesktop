#ifndef CCIMXFILESYSTEMMODEL_H
#define CCIMXFILESYSTEMMODEL_H
#include <QFileSystemModel>
class FileInfoProvider;
class CCIMXFileSystemModel : public QFileSystemModel {
public:
	explicit CCIMXFileSystemModel(QObject* parent = nullptr);
	/**
	 * @brief bindProviders bind the providers to the model
	 * @param providers
	 */
	void bindProviders(QList<FileInfoProvider*>& providers) {
		this->providers = providers;
	}

	/**
	 * @brief provide_section_name provide the section name
	 * @return the section name
	 */
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	/**
	 * @brief provide_section_name provide the section name
	 * @return the section name
	 */
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	/**
	 * @brief get_providers provide the providers installed in the model
	 * @return the providers
	 */
	const QList<FileInfoProvider*>& get_providers() const { return providers; }

private:
	QList<FileInfoProvider*> providers; ///< the providers
};

#endif // CCIMXFILESYSTEMMODEL_H

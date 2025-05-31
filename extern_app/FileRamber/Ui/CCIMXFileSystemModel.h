#ifndef CCIMXFILESYSTEMMODEL_H
#define CCIMXFILESYSTEMMODEL_H

#include <QFileSystemModel>

class FileInfoProvider;

/**
 * @brief The CCIMXFileSystemModel class
 * Extends QFileSystemModel to support additional information providers.
 * Providers can add custom data for files/directories.
 */
class CCIMXFileSystemModel : public QFileSystemModel {
public:
    /**
     * @brief Constructor with optional parent.
     * @param parent Pointer to the QObject parent, default nullptr.
     */
    explicit CCIMXFileSystemModel(QObject* parent = nullptr);

    /**
     * @brief bindProviders
     * Binds a list of FileInfoProvider instances to this model.
     * @param providers List of pointers to FileInfoProvider.
     */
    void bindProviders(QList<FileInfoProvider*>& providers) {
        this->providers = providers;
    }

    /**
     * @brief data
     * Overrides QFileSystemModel::data to provide custom data from providers.
     * @param index Model index.
     * @param role Data role.
     * @return QVariant containing the data for the given index and role.
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    /**
     * @brief headerData
     * Overrides QFileSystemModel::headerData to provide custom header names.
     * @param section Section index.
     * @param orientation Horizontal or Vertical.
     * @param role Data role.
     * @return QVariant containing header text.
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /**
     * @brief get_providers
     * Returns the list of currently bound providers.
     * @return const reference to the QList of FileInfoProvider pointers.
     */
    const QList<FileInfoProvider*>& get_providers() const { return providers; }

private:
    QList<FileInfoProvider*> providers; ///< List of custom information providers.
};

#endif // CCIMXFILESYSTEMMODEL_H

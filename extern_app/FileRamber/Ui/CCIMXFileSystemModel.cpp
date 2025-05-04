#include "CCIMXFileSystemModel.h"
#include "Core/FileInfoProvider.h"
CCIMXFileSystemModel::CCIMXFileSystemModel(QObject* parent)
	: QFileSystemModel { parent } {
}

QVariant CCIMXFileSystemModel::data(const QModelIndex& index, int role) const {
	/* remove the invalid issue */
	if (!index.isValid())
		return {};

	/* Others do the defaults */
	if (index.column() >= providers.size()) {
		return QFileSystemModel::data(index, role);
	}

	/* sessions matching as the indexed visit */

	FileInfoProvider* provider = providers.at(index.column());
	if (!provider) {
		return QFileSystemModel::data(index, role);
	}

	auto result = provider->data(index, role);
	return result.first ? result.second : /* yeah, the indications tells we need */
		QFileSystemModel::data(index, role);
}

QVariant CCIMXFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const {

	if (role != Qt::DisplayRole)
		return QFileSystemModel::headerData(section, orientation, role);
	if (orientation != Qt::Horizontal)
		return QFileSystemModel::headerData(section, orientation, role);

	if (section >= providers.size())
		return QFileSystemModel::headerData(section, orientation, role);

	FileInfoProvider* provider = providers.at(section);
	if (!provider)
		return QFileSystemModel::headerData(section, orientation, role);

	return provider->provide_section_name();
}

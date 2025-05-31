#ifndef FILEINFOPROVIDER_H
#define FILEINFOPROVIDER_H
#include <QModelIndex>
#include <QString>
#include <QtClassHelperMacros>

class CCIMXFileSystemModel;
/* Interfaces are provided in virtual class */

/**
 * @brief The FileInfoProvider class is such an abstract class
 * that using in CCIMXFileSystemModel to provide the file information,
 * which, we can modify the file information provide easily in the model
 */
class FileInfoProvider {
public:
	/**
	 * @brief disable copy object
	 * 
	 */
	Q_DISABLE_COPY(FileInfoProvider);
	/**
	 * @brief Construct a new File Info Provider object default is prohibited,
	 * disable this for the default constructor, prevent the non-model register
	 * 
	 */
	FileInfoProvider() = delete;
	/**
	 * @brief Construct a new File Info Provider object, assigned models requires
	 * 
	 * @param models 
	 */
	FileInfoProvider(CCIMXFileSystemModel* models) {
		this->models = models;
	};
	/**
	 * @brief Destroy the File Info Provider object
	 * 
	 */
	virtual ~FileInfoProvider() = default;

	/**
	 * @brief One InfoProvider for one section header name, the function do
	 * the case :)
	 * @return the section name
	 */
	virtual inline QString provide_section_name() = 0;

	/**
	 * @brief setCurrentHandlePath set the current handle path
	 * @param path the path to be set
	 */
	inline void setCurrentHandlePath(const QString& path) { cached_path = path; }

	/**
	 * @brief currentHandlePath get the current handle path
	 * @return the current handle path
	 */
	inline QString currentHandlePath() { return cached_path; }

	/**
	 * @brief functions provide what to display
	 * @param index the model index
	 * @param role the role of the index
	 * @return returns the data of the index, if the data is not
	 * available, it will return with {false, {}}
	 * @note for developers re-develop the sessions, you can modified to the
	 * implements with std::optional<QVariant>, QVariant itself invalid means
	 * something in model that is meaningful, so, QVariant's invalid don't mean
	 * the data itself invalid
	 */
	virtual std::pair<bool, QVariant> data(const QModelIndex& index, int role) = 0;

protected:
	CCIMXFileSystemModel* models; ///< binding models

private:
	QString cached_path {};
};

#endif // FILEINFOPROVIDER_H

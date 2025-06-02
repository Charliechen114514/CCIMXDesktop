#ifndef IMAGEBROWSER_H
#define IMAGEBROWSER_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QImage>
#include <memory>

class ImageCore;
class ImageInfoWindow;

namespace Ui {
class ImageBrowser;
}

/**
 * @brief The ImageBrowser class
 * 
 * Holds the basic interface in UI Level for browsing images.
 */
class ImageBrowser : public QWidget {
	Q_OBJECT

public:
	/**
	 * @brief The ErrorType enum
	 * 
	 * Defines the types of errors that can occur in the image browser.
	 */
	enum class ErrorType {
		IMAGEREQ_OVERFLOW, ///< Overflow request
		IMAGEREQ_UNDERFLOW, ///< Underflow request
		IMAGEREQ_LOST, ///< Image is lost
		IMAGEREQ_EMPTY ///< Images are empty
	};

	/**
	 * @brief Constructs an ImageBrowser object
	 * 
	 * @param parent The parent widget
	 */
	explicit ImageBrowser(QWidget* parent = nullptr);

	/**
	 * @brief Enables directory supports
	 * 
	 * @param where The path of the directory to support
	 */
	void enDirSupports(const QString& where);

	/**
	 * @brief Enables directory supports with file prefixes
	 * 
	 * @param where The path of the directory to support
	 * @param prefixs The list of file prefixes to consider
	 */
	void enDirSupports(const QString& where, const QStringList& prefixs);

	/**
	 * @brief Removes images from the browser based on their names
	 * 
	 * @param names The list of image names to remove
	 */
	void remove_from_name(const QStringList& names);

	/**
	 * @brief Checks if the file view is visible
	 * 
	 * @return true if visible, false otherwise
	 */
	bool is_fileview_visible() const;

	/**
	 * @brief Shows an image based on its name
	 * 
	 * @param name The name of the image to show
	 */
	void show_from_name(const QString& name);

	/**
	 * @brief Shows an image based on its index
	 * 
	 * @param index The index of the image to show
	 */
	void show_from_index(const int index);

	/**
	 * @brief Converts names to paths
	 * 
	 * @param names The list of names
	 * @return The list of corresponding paths
	 */
	QStringList from_name(const QStringList& names);

	/**
	 * @brief Destructor
	 */
	~ImageBrowser();

public slots:
	/**
	 * @brief Toggles the visibility of the file view
	 */
	void oppose_fileview_visible();

	/**
	 * @brief Shows the next image
	 */
	void show_next();

	/**
	 * @brief Shows the first image
	 */
	void show_start();

	/**
	 * @brief Shows the last image
	 */
	void show_end();

	/**
	 * @brief Shows the previous image
	 */
	void show_prev();

	/**
	 * @brief Displays the image information window
	 */
	void show_infoWindow();

	/**
	 * @brief Removes the currently selected image
	 */
	void remove_select();

	/**
	 * @brief Clears the image list
	 */
	void clear();

signals:
	/**
	 * @brief Signal emitted when an error occurs
	 * 
	 * @param e The type of error that occurred
	 */
	void errorOccur(const ImageBrowser::ErrorType e);

private:
	/**
	 * @brief The UI object
	 */
	Ui::ImageBrowser* ui;

	/**
	 * @brief Core image handling object
	 */
	std::unique_ptr<ImageCore> core;

	/**
	 * @brief Mappings from label to file path
	 */
	QMap<QString, QString> mappings;

	/**
	 * @brief Initializes memory
	 */
	void init_memory();

	/**
	 * @brief Initializes connections between signals and slots
	 */
	void init_connections();

	/**
	 * @brief Enables mappings for given paths
	 * 
	 * @param paths The list of paths to enable mappings for
	 */
	void enmappings(const QStringList& paths);

	/**
	 * @brief Disables mappings for given items
	 * 
	 * @param removeWhat The list of items to remove from mappings
	 */
	void demappings(const QStringList& removeWhat);

	/**
	 * @brief Processes and sets images
	 * 
	 * @param images The images to process and set
	 */
	void process_set_images(const QString& images);

	/**
	 * @brief Resets the list widgets
	 */
	void reset_listwidgets();

	/**
	 * @brief The currently displayed image
	 */
	QImage current_image;

	/**
	 * @brief The index of the currently displayed image
	 */
	int current_index { -1 };

	/**
	 * @brief The image information window
	 */
	ImageInfoWindow* infoWindow;
};

#endif // IMAGEBROWSER_H

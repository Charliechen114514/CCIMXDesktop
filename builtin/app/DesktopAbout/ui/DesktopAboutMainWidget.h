#ifndef DESKTOPABOUTMAINWIDGET_H
#define DESKTOPABOUTMAINWIDGET_H

#include <QWidget>

namespace Ui {
class DesktopAboutMainWidget;
}
/**
 * @class DesktopAboutMainWidget
 * @brief A customizable "About" dialog widget for desktop applications.
 *
 * This widget displays application information including logo, title,
 * descriptions, version, and additional information in a standardized format.
 * Inherits from QWidget.
 */
class DesktopAboutMainWidget : public QWidget {
	Q_OBJECT
	/// Constant defining the size (in pixels) for the logo display
	static constexpr const unsigned short PIX_SZ = 300;

public:
	/**
	 * @brief Constructs a DesktopAboutMainWidget
	 * @param parent The parent QWidget (optional)
	 */
	explicit DesktopAboutMainWidget(QWidget* parent = nullptr);

	/**
	 * @brief Sets the application logo
	 * @param icon The QIcon to display as the application logo
	 */
	void setLogo(const QIcon& icon);

	/**
	 * @brief Sets the application title
	 * @param title The title string to display
	 */
	void setTitle(const QString& title);

	/**
	 * @brief Sets the application description text
	 * @param descriptions The description text to display
	 */
	void setDescriptions(const QString& descriptions);

	/**
	 * @brief Sets additional information text
	 * @param info The additional information text to display
	 */
	void setMoreInfo(const QString& info);

	/**
	 * @brief Sets the version string
	 * @param version_string The version information to display
	 */
	void setVersionString(const QString& version_string);

	/**
	 * @brief Destructor
	 */
	~DesktopAboutMainWidget();

private:
	/// Pointer to the UI implementation
	Ui::DesktopAboutMainWidget* ui;
};

#endif // DESKTOPABOUTMAINWIDGET_H

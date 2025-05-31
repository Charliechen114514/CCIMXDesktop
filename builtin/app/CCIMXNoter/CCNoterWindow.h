#ifndef CCNOTERWINDOW_H
#define CCNOTERWINDOW_H

#include <QMainWindow>

class QTextCharFormat;
class QLabel;

QT_BEGIN_NAMESPACE
namespace Ui {
class CCNoterWindow;
}
QT_END_NAMESPACE

/**
 * @class CCNoterWindow
 * @brief CCNoterWindow provides a simple notepad window with basic text formatting.
 *
 * This class represents the main window of the CCNoter application, offering functionality
 * for editing rich text, adjusting font size, and toggling bold/italic styles.
 */
class CCNoterWindow : public QMainWindow {
    Q_OBJECT

public:
	/**
	 * @brief Constructor for CCNoterWindow.
	 * @param parent The parent widget.
	 */
	CCNoterWindow(QWidget* parent = nullptr);

	/**
	 * @brief Load a text file into the editor.
	 */
	void load_file();

	/**
	 * @brief Open a font selection dialog.
	 */
	void chooseFont();

	/**
	 * @brief Save the current text to a file.
	 */
	void save_file();

	/**
	 * @brief Set the font size of the current text.
	 * @param size The desired font size.
	 */
	void set_font_size(int size);

	/**
	 * @brief Destructor for CCNoterWindow.
	 */
	~CCNoterWindow();

private slots:
	/**
	 * @brief Triggered when the italic action is toggled.
	 * @param checked Whether italic is enabled.
	 */
	void on_actionitalic_triggered(bool checked);

	/**
	 * @brief Triggered when the bold action is toggled.
	 * @param checked Whether bold is enabled.
	 */
	void on_actionbold_triggered(bool checked);

private:
	Ui::CCNoterWindow* ui; ///< The UI object for CCNoterWindow.
	QLabel* fontsize_label; ///< Label displaying the current font size.
	QLabel* fontstyle_label; ///< Label displaying the current font family.

	/**
	 * @brief Initialize signal-slot connections.
	 */
	void init_connections();

	/**
	 * @brief Setup the toolbars for the main window.
	 */
	void setup_toolbars();

	/**
	 * @brief Apply the given text format to the current word or selection.
	 * @param format The text format to apply.
	 */
	void mergeFormatOnWordOrSelection(const QTextCharFormat& format);
};

#endif // CCNOTERWINDOW_H

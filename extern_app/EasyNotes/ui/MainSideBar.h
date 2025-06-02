#ifndef MAINSIDEBAR_H
#define MAINSIDEBAR_H

#include <QWidget>
class LeftSideBar;
namespace Ui {
class MainSideBar;
}

/**
 * @brief Main display widgets
 * 
 */
class MainSideBar : public QWidget {
	Q_OBJECT
	/**
	 * @brief default markdown editors
	 * 
	 */
	static constexpr const char* DEF_PLACEHOLDER = "Edit Markdown Text here...";

public:
	/**
	 * @brief Construct a new Main Side Bar object
	 * 
	 * @param parent 
	 */
	explicit MainSideBar(QWidget* parent = nullptr);
	void bind_sidebar(LeftSideBar* s) { sidebar = s; } ///< bind the left sidebar
	/**
	 * @brief make once render
	 * 
	 */
	void process_once_fetch();
	/**
	 * @brief load file from file dialog
	 * 
	 */
	void load_file();
	/**
	 * @brief make request to cached the temp markdown
	 * 
	 */
	void request_cached();
	/**
	 * @brief save the file to the disk
	 * 
	 */
	void save_file();
	void makeBold(); ///< make select bold
	void makeItalic(); ///< make select italic
	void makeUnderline(); ///< make select underline
	void display_temperary(const QString& labels); ///< display the temp label context
	~MainSideBar();

public slots:
	/**
	 * @brief commit_file commit from remote instead of the file dialog
	 * @param fileName filename for load
	 */
	void commit_file(const QString& fileName);
signals:
	/**
	 * @brief signals for submit a history request
	 * 
	 * @param filename 
	 */
	void submit_enhist_request(const QString filename);

private:
	Ui::MainSideBar* ui; ///< ui handle
	LeftSideBar* sidebar; ///< left sidebars
	bool from_already_cached { false }; ///< is current a temp
	/**
	 * @brief run_init_example this will be down at a create sessions
	 */
	void run_init_example();
};

#endif // MAINSIDEBAR_H

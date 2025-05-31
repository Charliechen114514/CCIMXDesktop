#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

class CCIMXFileSystemModel;
class FileInfoProvider;
class QComboBox;
class QLabel;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class QFileSystemModel;
class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	/**
	 * @brief Construct a new Main Window object
	 * 
	 * @param parent 
	 */
	MainWindow(QWidget* parent = nullptr);
	/**
	 * @brief try_goto_parent_view will attempt to switch to the root,
	 * no returns as is uncheckable
	 */
	void try_goto_parent_view();
	/**
	 * @brief switch_to_global_root will attempt to switch to the root
	 * @note Fuck Windows, we have to specify the root driver base to show where to display
	 */
	void switch_to_global_root();
	~MainWindow();

	/**
	 * @brief Info index that shell controlls which lines
	 */
	enum InfoIndex {
		NameProviders, ///< name providers line
		CountProviders, ///< count providers line
		DirSizeProviders, ///< dirent providers line
		TypeInfoProviders, ///< type info providers line
		InfoIndexMax ///< Max
	};

private slots:
	/**
	 * @brief processing_switch_double_click process the hook
	 * of double clicked
	 * @param index at what index?
	 */
	void processing_switch_double_click(const QModelIndex& index);

	/**
	 * @brief processing_filecheck_issue process the hook of
	 * browse the preview
	 * @param index at what index?
	 */
	void processing_filecheck_issue(const QModelIndex& index);

private:
	void setupFileModels();
	void setupUi();
	void setup_connections();
	QList<FileInfoProvider*> providers;
	Ui::MainWindow* ui;
	CCIMXFileSystemModel* file_model { nullptr };
	QComboBox* box { nullptr };
	QLabel* pwd_label { nullptr };
};
#endif // MAINWINDOW_H

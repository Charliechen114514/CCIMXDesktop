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
	MainWindow(QWidget* parent = nullptr);
	void try_goto_parent_view();
	/* Fuck Windows */
	void switch_to_global_root();
	~MainWindow();

	enum InfoIndex {
		NameProviders,
		CountProviders,
		DirSizeProviders,
		TypeInfoProviders,
		InfoIndexMax
	};

private slots:
	void processing_switch_double_click(const QModelIndex& index);
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

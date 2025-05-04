#include "MainWindow.h"
#include "Core/DirentSizeCounter.h"
#include "Core/FileNameProviders.h"
#include "Core/FileTypeInfo.h"
#include "FileCountInfo.h"
#include "Ui/CCIMXFileSystemModel.h"
#include "ui_MainWindow.h"
#include <QComboBox>
#include <QThreadPool>
#include <QtConcurrentRun>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
	ui->setupUi(this);
	setupFileModels();
	setupUi();
	setup_connections();
}

void MainWindow::try_goto_parent_view() {
	QModelIndex parentIndex = file_model->parent(ui->fileTreeView->rootIndex());
	if (parentIndex.isValid()) {
		pwd_label->setText(file_model->filePath(parentIndex));
		ui->fileTreeView->setRootIndex(parentIndex);
	}
}

void MainWindow::switch_to_global_root() {
	QModelIndex root_index = file_model->setRootPath(box->currentText());
	pwd_label->setText(file_model->filePath(root_index));
	ui->fileTreeView->setRootIndex(root_index);
}

void MainWindow::setupFileModels() {
	/* init the providers */
	file_model = new CCIMXFileSystemModel(this);
	providers.reserve(InfoIndex::InfoIndexMax);

	FileInfoProvider* fileNameProviders = new FileNameProviders(file_model);
	providers.insert(InfoIndex::NameProviders, fileNameProviders);

	FileInfoProvider* fileCountInfo = new FileCountInfo(file_model, this);
	providers.insert(InfoIndex::CountProviders, fileCountInfo);

	FileInfoProvider* direntSizeCounter = new DirentSizeCounter(file_model, this);
	providers.insert(InfoIndex::DirSizeProviders, direntSizeCounter);

	FileInfoProvider* fileType = new FileTypeInfo(file_model);
	providers.insert(InfoIndex::TypeInfoProviders, fileType);
	file_model->bindProviders(providers);
	/* set RootPath property */
	file_model->setFilter(
		QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
	file_model->setReadOnly(true);
	file_model->setRootPath(QDir::rootPath());
	file_model->setOption(QFileSystemModel::DontWatchForChanges);

	ui->fileTreeView->setModel(file_model);
	QHeaderView* header = ui->fileTreeView->header();
	header->setSectionResizeMode(0, QHeaderView::Stretch);
}

void MainWindow::setupUi() {
	ui->processing_label->hide();
	ui->toolBar->addSeparator();
	box = new QComboBox(this);
	QList<QFileInfo> drives = QDir::drives();
	for (const QFileInfo& drive : std::as_const(drives)) {
		box->addItem(drive.absoluteFilePath());
	}
	ui->toolBar->addWidget(box);
	pwd_label = new QLabel(this);
	ui->toolBar->addWidget(pwd_label);
	ui->show_widget->bind_models(file_model);
}

void MainWindow::setup_connections() {
	/* go back parent */
	connect(ui->actionbackto_parent, &QAction::triggered,
			this, &MainWindow::try_goto_parent_view);
	/* double clicked to switch root dirent */
	connect(ui->fileTreeView, &QAbstractItemView::doubleClicked,
			this, &MainWindow::processing_switch_double_click);

	/* back to root */
	connect(ui->actionbackto_root, &QAction::triggered,
			this, &MainWindow::switch_to_global_root);
	connect(ui->fileTreeView, &QTreeView::clicked,
			this, &MainWindow::processing_filecheck_issue);

	connect(box, &QComboBox::textActivated,
			this, &MainWindow::switch_to_global_root);
}

MainWindow::~MainWindow() {
	for (auto each : std::as_const(providers)) {
		delete each;
	}
	delete ui;
}

void MainWindow::processing_switch_double_click(const QModelIndex& index) {
	QFileInfo info = file_model->fileInfo(index);

	if (info.isDir()) {
		pwd_label->setText(info.absoluteFilePath());
		file_model->setRootPath(info.absoluteFilePath());
		connect(file_model, &QFileSystemModel::directoryLoaded, this, [=](const QString& path) {
			if (path == info.absoluteFilePath()) {
				ui->fileTreeView->setRootIndex(index);
			}
		});
	}
}

void MainWindow::
	processing_filecheck_issue(const QModelIndex& index) {
	ui->show_widget->setModelIndex(index);
}

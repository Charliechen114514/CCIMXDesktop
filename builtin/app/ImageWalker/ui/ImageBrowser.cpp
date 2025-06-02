#include "ImageBrowser.h"
#include "ImageCore.h"
#include "ImageInfoWindow.h"
#include "ui_ImageBrowser.h"
#include <QDirIterator>
#include <QFileInfo>
#include <QImageReader>

namespace {

QStringList getImageFilesFromDirectory(const QString& dirPath, const QStringList& filters) {
	QStringList imageFiles;
	QDirIterator iter(dirPath, filters,
					  QDir::Files | QDir::Readable,
					  QDirIterator::Subdirectories);
	while (iter.hasNext()) {
		iter.next();
		imageFiles << iter.filePath();
	}

	return imageFiles;
}

QStringList def_imageFilters() {
	QStringList filters;
	const QList<QByteArray> formats = QImageReader::supportedImageFormats();
	for (const QByteArray& fmt : formats)
		filters << "*." + fmt;
	return filters;
}

}

ImageBrowser::ImageBrowser(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ImageBrowser) {
	ui->setupUi(this);
	init_memory();
	init_connections();
}

void ImageBrowser::enDirSupports(const QString& where) {
	enDirSupports(where, def_imageFilters());
}

void ImageBrowser::enDirSupports(const QString& where, const QStringList& prefixs) {
	clear();
	auto paths = getImageFilesFromDirectory(where, prefixs);
	core->enImages(paths);
	enmappings(paths);
	reset_listwidgets();
	show_start();
}

void ImageBrowser::remove_from_name(const QStringList& names) {
	auto paths = from_name(names);
	demappings(names);
	core->removeImages(paths);
	reset_listwidgets();
	show_next();
}

QStringList ImageBrowser::from_name(const QStringList& names) {
	QStringList valueList;
	valueList.reserve(names.size());
	for (const QString& key : names) {
		if (mappings.contains(key)) {
			valueList << mappings.value(key);
		} else {
			valueList << QString(); //
		}
	}
	return valueList;
}
bool ImageBrowser::is_fileview_visible() const {
	return ui->list_view_selections->isVisible();
}

void ImageBrowser::show_from_name(const QString& name) {
	int index = core->index(mappings[name]);
	if (index < 0) {
		emit errorOccur(ErrorType::IMAGEREQ_LOST);
		return;
	}
	show_from_index(index);
}

void ImageBrowser::show_from_index(const int index) {
	if (core->empty()) {
		emit errorOccur(ErrorType::IMAGEREQ_EMPTY);
		return;
	}

	if (index < 0) {
		emit errorOccur(ErrorType::IMAGEREQ_UNDERFLOW);
		return;
	} else if (index >= core->size()) {
		emit errorOccur(ErrorType::IMAGEREQ_OVERFLOW);
		return;
	}

	auto _image_path = core->peek(index);

	if (!_image_path.has_value()) {
		emit errorOccur(ErrorType::IMAGEREQ_LOST);
		return;
	}
	QString image_path = _image_path.value();
	current_index = core->index(image_path);
	infoWindow->set_image_path(image_path);
	process_set_images(image_path);
}

ImageBrowser::~ImageBrowser() {
	delete ui;
}

void ImageBrowser::oppose_fileview_visible() {
	ui->list_view_selections->setVisible(
		!ui->list_view_selections->isVisible());
}

void ImageBrowser::show_next() {
	show_from_index(current_index + 1);
}

void ImageBrowser::show_start() {
	show_from_index(0);
}

void ImageBrowser::show_end() {
	show_from_index(core->size() - 1);
}

void ImageBrowser::show_prev() {
	show_from_index(current_index - 1);
}

void ImageBrowser::show_infoWindow() {
	if (infoWindow->get_image_path().isEmpty()) {
		return;
	}
	infoWindow->show();
}

void ImageBrowser::remove_select() {
	auto items = ui->list_view_selections->selectedItems();
	if (items.empty())
		return;

	QStringList strings;
	for (const auto& each : std::as_const(items)) {
		strings << each->text();
	}

	remove_from_name(strings);
}

void ImageBrowser::clear() {
	ui->list_view_selections->clear();
	current_index = -1;
	core->clear();
}

void ImageBrowser::init_memory() {
	core = std::make_unique<ImageCore>();
	infoWindow = new ImageInfoWindow(this);
}

void ImageBrowser::init_connections() {
	connect(ui->list_view_selections, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) {
		show_from_name(item->text());
	});
}

void ImageBrowser::enmappings(const QStringList& paths) {
	for (const QString& path : paths) {
		QFileInfo fileInfo(path);
		QString fileName = fileInfo.fileName();
		mappings.insert(fileName, path);
	}
}

void ImageBrowser::demappings(const QStringList& removeWhat) {
	for (const QString& key : removeWhat) {
		mappings.remove(key);
	}
}

void ImageBrowser::process_set_images(const QString& images) {
	current_image = QImage(images);
	ui->image_displayer->setImage(current_image);
}

void ImageBrowser::reset_listwidgets() {
	ui->list_view_selections->clear();
	QStringList names = mappings.keys();
	ui->list_view_selections->addItems(names);
}

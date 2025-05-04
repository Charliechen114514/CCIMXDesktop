#include "FileInfoDisplayWidget.h"
#include "CCIMXFileSystemModel.h"
#include "Core/FileRamberTools.h"
#include "ui_FileInfoDisplayWidget.h"
#include <QMimeDatabase>
#include <QMimeType>
#include <QModelIndex>
namespace {
static const QMap<QString, QString> mappings = {
	{ "cpp", "C++ Source File" },
	{ "c", "C Source File" },
	{ "h", "C/C++ Header" },
	{ "hpp", "C++ Header" },
	{ "py", "Python Script" },
	{ "java", "Java Source File" },
	{ "js", "JavaScript File" },
	{ "ts", "TypeScript File" },

	{ "jpg", "JPEG Image" },
	{ "jpeg", "JPEG Image" },
	{ "png", "PNG Image" },
	{ "bmp", "Bitmap Image" },
	{ "gif", "GIF Image" },
	{ "svg", "Scalable Vector Graphics" },
	{ "ico", "Icon File" },

	{ "txt", "Text File" },
	{ "md", "Markdown Document" },
	{ "log", "Log File" },
	{ "csv", "CSV Spreadsheet" },
	{ "ini", "INI Configuration" },
	{ "json", "JSON File" },
	{ "xml", "XML File" },
	{ "yaml", "YAML File" },
	{ "yml", "YAML File" },

	{ "zip", "ZIP Archive" },
	{ "rar", "RAR Archive" },
	{ "7z", "7-Zip Archive" },
	{ "tar", "TAR Archive" },
	{ "gz", "GZip Compressed Archive" },
	{ "bz2", "BZip2 Compressed Archive" },

	{ "mp3", "MP3 Audio" },
	{ "wav", "WAV Audio" },
	{ "flac", "FLAC Audio" },
	{ "mp4", "MP4 Video" },
	{ "avi", "AVI Video" },
	{ "mkv", "Matroska Video" },
	{ "mov", "QuickTime Video" },

	{ "exe", "Executable File" },
	{ "bin", "Binary File" },
	{ "out", "Executable Output" },
	{ "dll", "Dynamic Library" },
	{ "so", "Shared Object" },

	{ "pdf", "PDF Document" },

	{ "doc", "Word Document" },
	{ "docx", "Word Document" },
	{ "xls", "Excel Spreadsheet" },
	{ "xlsx", "Excel Spreadsheet" },
	{ "ppt", "PowerPoint Presentation" },
	{ "pptx", "PowerPoint Presentation" },

	{ "sh", "Shell Script" },
	{ "bash", "Bash Script" },
	{ "run", "Executable File" },
	{ "out", "Executable Output" },
	{ "bin", "Binary File" },
	{ "so", "Shared Library" },
	{ "a", "Static Library" },
	{ "ko", "Kernel Module" },

	{ "conf", "Configuration File" },
	{ "cfg", "Configuration File" },
	{ "service", "Systemd Service File" },
	{ "timer", "Systemd Timer" },
	{ "mount", "Mount Unit File" },
	{ "socket", "Socket Unit File" },

	{ "log", "Log File" },
	{ "pid", "Process ID File" },
	{ "lock", "Lock File" },
	{ "bak", "Backup File" },

	{ "pl", "Perl Script" },
	{ "rb", "Ruby Script" },
	{ "lua", "Lua Script" },

	{ "deb", "Debian Package" },
	{ "rpm", "RPM Package" },
	{ "pkg", "Package File" },
	{ "tar", "TAR Archive" },
	{ "gz", "Gzip Compressed Archive" },
	{ "xz", "XZ Compressed Archive" },
	{ "bz2", "BZip2 Compressed Archive" },
	{ "zst", "Zstandard Archive" },
	{ "img", "Disk Image" },
	{ "iso", "ISO Image" },

	{ "man", "Man Page Source" },
	{ "tex", "LaTeX Document" },
	{ "rst", "reStructuredText File" }
};

bool isImageDisplayable(const QString& suffix) {
	return (suffix == "jpg" || suffix == "jpeg" || suffix == "png" || suffix == "bmp" || suffix == "gif");
}

}

FileInfoDisplayWidget::FileInfoDisplayWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FileInfoDisplayWidget) {
	ui->setupUi(this);
}

void FileInfoDisplayWidget::setModelIndex(const QModelIndex& index) {
	QFileInfo info = models->fileInfo(index);
	QString name = info.fileName();
	QString path = info.absoluteFilePath();
	qint64 size = info.size();
	QString raw_suffix = info.suffix().toLower();
	QString type = info.isDir() ? "Folder" : mappings.value(raw_suffix);
	ui->file_locations->setText("File locations: " + path);
	ui->filename_label->setText("File Name: " + name);
	ui->file_type->setText("File Type: " + type);
	ui->filesize_label->setText(size <= 0 ? "" : "File Size: " + FileRamberTools::formatSize(size));
	QModelIndex primaryIndex = index.sibling(index.row(), 0);
	QIcon icon = models->fileIcon(primaryIndex);

	ui->icon_label->setPixmap(icon.pixmap(
		FileInfoDisplayWidget::ICON_SIZE,
		FileInfoDisplayWidget::ICON_SIZE));

	/* load the file then */
	QMimeDatabase db;
	QMimeType mimeType = db.mimeTypeForFile(path);
	if (mimeType.inherits("text/plain")) {
		QFile file(path);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			/* Thus, switch to the display text */
			ui->image_display->hide();
			ui->textBrowser->show();
			QTextStream in(&file);
			QString content = in.readAll();
			if (raw_suffix == "md") {
				ui->textBrowser->setMarkdown(content);
			} else if (raw_suffix == "html") {
				ui->textBrowser->setHtml(content);
			} else {
				ui->textBrowser->setPlainText(content);
			}
		}
	} else if (isImageDisplayable(raw_suffix)) {
		QImage image(path);

		if (!image.isNull()) {
			ui->textBrowser->hide();
			ui->image_display->show();
			QPixmap pixmap = QPixmap::fromImage(image).scaled(
				ui->image_display->size(),
				Qt::KeepAspectRatio,
				Qt::FastTransformation);
			ui->image_display->setPixmap(pixmap);
			ui->image_display->setAlignment(Qt::AlignCenter);
			ui->image_display->setScaledContents(true);
		}
	}
}

FileInfoDisplayWidget::~FileInfoDisplayWidget() {
	delete ui;
}

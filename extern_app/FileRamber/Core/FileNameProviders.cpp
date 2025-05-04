#include "FileNameProviders.h"
#include "CCIMXFileSystemModel.h"
#include <QFileInfo>

std::pair<bool, QVariant>
FileNameProviders::data(const QModelIndex& index, int role) {
	/* handling the file forground  */
	switch (role) {
	case Qt::ForegroundRole:
		return handle_extension_color(index);
	default:
		return { false, {} };
	}
}

void FileNameProviders::registerColorPairs(const ColorPairs& pairs) {
	mappings.insert(pairs.first, pairs.second);
}

std::pair<bool, QVariant> FileNameProviders::
	handle_extension_color(const QModelIndex& index) {
	QFileInfo info = models->fileInfo(index);
	// qDebug() << index.data().toString() << " " << info.isDir();
	if (info.isDir()) {
		return { true, dirent_color };
	}

	return {
		true, mappings.value(info.suffix().toLower())
	};
}

FileNameProviders::FileNameProviders(CCIMXFileSystemModel* models)
	: FileInfoProvider(models) {
	mappings = {
		{ "cpp", Qt::blue },
		{ "c", Qt::blue },
		{ "h", Qt::blue },
		{ "hpp", Qt::blue },
		{ "py", Qt::blue },
		{ "java", Qt::blue },
		{ "js", Qt::blue },
		{ "ts", Qt::blue },

		{ "jpg", Qt::darkGreen },
		{ "jpeg", Qt::darkGreen },
		{ "png", Qt::darkGreen },
		{ "bmp", Qt::darkGreen },
		{ "gif", Qt::darkGreen },
		{ "svg", Qt::darkGreen },
		{ "ico", Qt::darkGreen },

		{ "txt", Qt::darkCyan },
		{ "md", Qt::darkCyan },
		{ "log", Qt::darkCyan },
		{ "csv", Qt::darkCyan },
		{ "ini", Qt::darkCyan },
		{ "json", Qt::darkCyan },
		{ "xml", Qt::darkCyan },
		{ "yaml", Qt::darkCyan },
		{ "yml", Qt::darkCyan },

		{ "zip", QColor(139, 69, 19) },
		{ "rar", QColor(139, 69, 19) },
		{ "7z", QColor(139, 69, 19) },
		{ "tar", QColor(139, 69, 19) },
		{ "gz", QColor(139, 69, 19) },
		{ "bz2", QColor(139, 69, 19) },

		{ "mp3", QColor(139, 0, 0) },
		{ "wav", QColor(139, 0, 0) },
		{ "flac", QColor(139, 0, 0) },
		{ "mp4", QColor(139, 0, 0) },
		{ "avi", QColor(139, 0, 0) },
		{ "mkv", QColor(139, 0, 0) },
		{ "mov", QColor(139, 0, 0) },

		{ "exe", Qt::red },
		{ "bin", Qt::red },
		{ "out", Qt::red },
		{ "dll", Qt::red },
		{ "so", Qt::red },

		// PDF
		{ "pdf", Qt::darkMagenta },

		{ "doc", QColor(255, 140, 0) },
		{ "docx", QColor(255, 140, 0) },
		{ "xls", QColor(255, 140, 0) },
		{ "xlsx", QColor(255, 140, 0) },
		{ "ppt", QColor(255, 140, 0) },
		{ "pptx", QColor(255, 140, 0) },

		{ "sh", Qt::red },
		{ "bash", Qt::red },
		{ "run", Qt::red },
		{ "out", Qt::red },
		{ "bin", Qt::red },
		{ "so", Qt::red },
		{ "a", Qt::red },
		{ "ko", Qt::red },

		{ "conf", Qt::darkCyan },
		{ "cfg", Qt::darkCyan },
		{ "service", Qt::darkCyan },
		{ "timer", Qt::darkCyan },
		{ "mount", Qt::darkCyan },
		{ "socket", Qt::darkCyan },

		{ "log", QColor(139, 69, 19) },
		{ "pid", QColor(139, 69, 19) },
		{ "lock", QColor(139, 69, 19) },
		{ "bak", QColor(139, 69, 19) },

		{ "pl", Qt::blue },
		{ "rb", Qt::blue },
		{ "lua", Qt::blue },

		{ "deb", QColor(139, 0, 0) },
		{ "rpm", QColor(139, 0, 0) },
		{ "pkg", QColor(139, 0, 0) },
		{ "tar", QColor(139, 0, 0) },
		{ "gz", QColor(139, 0, 0) },
		{ "xz", QColor(139, 0, 0) },
		{ "bz2", QColor(139, 0, 0) },
		{ "zst", QColor(139, 0, 0) },
		{ "img", QColor(139, 0, 0) },
		{ "iso", QColor(139, 0, 0) },

		{ "man", Qt::darkMagenta },
		{ "tex", Qt::darkMagenta },
		{ "rst", Qt::darkMagenta }
	};
}

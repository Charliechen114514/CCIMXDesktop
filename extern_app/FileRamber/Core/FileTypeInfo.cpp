#include "FileTypeInfo.h"
#include "CCIMXFileSystemModel.h"
std::pair<bool, QVariant> FileTypeInfo::
	data(const QModelIndex& index, int role) {

	if (role != Qt::DisplayRole)
		return { false, {} };

	QFileInfo info = models->fileInfo(index);

	if (info.isDir())
		return { true, QString("Folder") };

	QString extension = mappings.value(info.suffix().toLower());
	if (extension.isEmpty()) {
		/* falls to the default action */
		return { true, "File" };
	} else {
		return { true, extension };
	}
}

FileTypeInfo::FileTypeInfo(CCIMXFileSystemModel* model)
	: FileInfoProvider(model) {
	mappings = {
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
}

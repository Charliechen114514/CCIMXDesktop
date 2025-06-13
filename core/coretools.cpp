#include "coretools.h"
#include <QDir>
#include <QFileDialog>
QStringList CoreTools::
    enumeratefiles(
        const QString& path, const QStringList& nameFilters) {
    QDir dir(path);

	QFileInfoList fileInfoList = dir.entryInfoList(
        nameFilters,
        QDir::Files | QDir::NoSymLinks | QDir::Readable);

	QStringList filePaths;
	for (const QFileInfo& fileInfo : std::as_const(fileInfoList)) {
		filePaths << fileInfo.absoluteFilePath();
	}

	return filePaths;
}

#include <random>
float CoreTools::random_float(const float min, const float max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

int CoreTools::random_int(const int min, const int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

QString CoreTools::fromFiltersToFilterString(const QStringList& l) {
    return l.join(";;");
}

QString CoreTools::getExecutableFile(QWidget* parent) {
    QFileDialog dialog(parent);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setOption(QFileDialog::DontUseNativeDialog);
    dialog.setWindowTitle("Select Executables");

#if defined(Q_OS_WIN)
    dialog.setNameFilter("Executables (*.exe *.bat)");
#else
    dialog.setNameFilter("ALL (*)");
#endif

    if (dialog.exec() == QDialog::Accepted) {
        QString selectedFile = dialog.selectedFiles().first();
        QFileInfo info(selectedFile);
#if defined(Q_OS_WIN)
        if (info.suffix().compare("exe", Qt::CaseInsensitive) == 0 || info.suffix().compare("bat", Qt::CaseInsensitive) == 0) {
            return selectedFile;
        }
#else
        if (info.isExecutable() && info.isFile()) {
            return selectedFile;
        }
#endif
    }

    return QString();
}

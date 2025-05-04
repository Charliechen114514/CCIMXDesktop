#ifndef FILEINFODISPLAYWIDGET_H
#define FILEINFODISPLAYWIDGET_H

#include <QWidget>
class CCIMXFileSystemModel;
namespace Ui {
class FileInfoDisplayWidget;
}

class FileInfoDisplayWidget : public QWidget {
	Q_OBJECT

public:
	static constexpr const unsigned short ICON_SIZE = 32;
	explicit FileInfoDisplayWidget(QWidget* parent = nullptr);
	inline void bind_models(CCIMXFileSystemModel* models) { this->models = models; }
	void setModelIndex(const QModelIndex& index);
	~FileInfoDisplayWidget();

private:
	Ui::FileInfoDisplayWidget* ui;
	CCIMXFileSystemModel* models { nullptr };
};

#endif // FILEINFODISPLAYWIDGET_H

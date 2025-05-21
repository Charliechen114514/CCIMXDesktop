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
	/**
	 * @brief bind_models bind the models to the widget
	 * @param models
	 */
	inline void bind_models(CCIMXFileSystemModel* models) { this->models = models; }
	/**
	 * @brief setModelIndex set the model index to be displayed
	 * @param index the model index
	 */
	void setModelIndex(const QModelIndex& index);
	~FileInfoDisplayWidget();

private:
	Ui::FileInfoDisplayWidget* ui;
	CCIMXFileSystemModel* models { nullptr };
};

#endif // FILEINFODISPLAYWIDGET_H

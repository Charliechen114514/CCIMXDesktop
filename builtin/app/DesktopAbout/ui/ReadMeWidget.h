#ifndef READMEWIDGET_H
#define READMEWIDGET_H

#include <QWidget>

namespace Ui {
class ReadMeWidget;
}

class ReadMeWidget : public QWidget {
	Q_OBJECT

public:
	/**
	 * @brief Construct a new Read Me Widget object
	 * 
	 * @param parent 
	 */
	explicit ReadMeWidget(QWidget* parent = nullptr);
	/**
	 * @brief load_file load readme file
	 * @param readme_path path indications
	 */
	void load_file(const QString& readme_path);
	~ReadMeWidget();

private:
	Ui::ReadMeWidget* ui;
};

#endif // READMEWIDGET_H

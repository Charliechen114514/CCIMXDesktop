#ifndef READMEWIDGET_H
#define READMEWIDGET_H

#include <QWidget>

namespace Ui {
class ReadMeWidget;
}

class ReadMeWidget : public QWidget {
	Q_OBJECT

public:
	explicit ReadMeWidget(QWidget* parent = nullptr);
	void load_file(const QString& readme_path);
	~ReadMeWidget();

private:
	Ui::ReadMeWidget* ui;
};

#endif // READMEWIDGET_H

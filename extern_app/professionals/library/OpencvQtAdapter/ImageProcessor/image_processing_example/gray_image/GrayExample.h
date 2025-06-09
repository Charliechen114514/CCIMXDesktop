#ifndef GRAYEXAMPLE_H
#define GRAYEXAMPLE_H

#include <QWidget>

namespace Ui {
class GrayExample;
}

class GrayExample : public QWidget {
	Q_OBJECT

public:
    explicit GrayExample(QWidget* parent = nullptr);
    void process_image_session();
	~GrayExample();

private:
    Ui::GrayExample* ui;
};

#endif // GRAYEXAMPLE_H

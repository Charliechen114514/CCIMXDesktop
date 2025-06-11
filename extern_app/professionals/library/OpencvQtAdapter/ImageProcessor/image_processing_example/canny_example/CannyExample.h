#ifndef CANNYEXAMPLE_H
#define CANNYEXAMPLE_H

#include <QWidget>

namespace Ui {
class CannyExample;
}

class CannyExample : public QWidget {
	Q_OBJECT

public:
    explicit CannyExample(QWidget* parent = nullptr);
	~CannyExample();
    void process_image_session();

private:
    Ui::CannyExample* ui;
};

#endif // CANNYEXAMPLE_H

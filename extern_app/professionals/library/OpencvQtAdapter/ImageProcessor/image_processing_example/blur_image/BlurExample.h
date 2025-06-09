#ifndef BLUREXAMPLE_H
#define BLUREXAMPLE_H

#include <QWidget>

namespace Ui {
class BlurExample;
}

class BlurExample : public QWidget {
	Q_OBJECT
    static constexpr unsigned short MIN_KER_SZ = 1;
    static constexpr unsigned short MAX_KER_SZ = 19;

public:
    explicit BlurExample(QWidget* parent = nullptr);
    void process_blur();
	~BlurExample();

private:
    Ui::BlurExample* ui;
    void process_medianblur();
    void process_guassainblur();
    void process_meanblur();
    void process_filterblur();
};

#endif // BLUREXAMPLE_H

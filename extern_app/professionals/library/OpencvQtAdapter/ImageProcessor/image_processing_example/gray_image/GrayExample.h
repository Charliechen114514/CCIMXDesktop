#ifndef GRAYEXAMPLE_H
#define GRAYEXAMPLE_H

#include <QWidget>

namespace Ui {
class GrayExample;
}

/**
 * @brief The GrayExample class shows the
 * Gray Image Examples
 */
class GrayExample : public QWidget {
	Q_OBJECT

public:
    /**
     * @brief GrayExample
     * @param parent
     */
    explicit GrayExample(QWidget* parent = nullptr);
    /**
     * @brief hooks of the image grey processions
     */
    void process_image_session();
	~GrayExample();

private:
    Ui::GrayExample* ui;
};

#endif // GRAYEXAMPLE_H

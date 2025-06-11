#ifndef CONTOURSQUERYEXAMPLE_H
#define CONTOURSQUERYEXAMPLE_H

#include <QWidget>

namespace Ui {
class ContoursQueryExample;
}

class ContoursQueryExample : public QWidget {
	Q_OBJECT

public:
    explicit ContoursQueryExample(QWidget* parent = nullptr);
    void process_image_session();
	~ContoursQueryExample();

private:
    Ui::ContoursQueryExample* ui;
};

#endif // CONTOURSQUERYEXAMPLE_H

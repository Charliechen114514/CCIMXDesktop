#ifndef TABLET_H
#define TABLET_H

#include <QWidget>

namespace Ui {
class Tablet;
}

class Tablet : public QWidget {
	Q_OBJECT

public:
    explicit Tablet(QWidget* parent = nullptr);
	~Tablet();
public slots:
    void setResult(const QString& v);
    void append_outlayer(const QString& what);
    void process_clear();
    void process_chop();
    void process_evaluate();
private slots:
    // for the simple plain token
    void process_text_according();

private:
    void setup_panel();
    Ui::Tablet* ui;
    QString string_expression;
};

#endif // TABLET_H

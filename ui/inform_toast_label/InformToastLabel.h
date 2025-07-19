#ifndef INFORMTOASTLABEL_H
#define INFORMTOASTLABEL_H

#include <QWidget>

namespace Ui {
class InformToastLabel;
}

class InformToastLabel : public QWidget {
	Q_OBJECT

public:
    explicit InformToastLabel(QWidget* parent = nullptr);
    ~InformToastLabel();

    void setTitle(const QString& title);
    void setText(const QString& text);
    void setIcon(const QString& icons);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::InformToastLabel* ui;
};

#endif // INFORMTOASTLABEL_H

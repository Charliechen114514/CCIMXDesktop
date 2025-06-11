#ifndef BONUSFUNCTOR_H
#define BONUSFUNCTOR_H

#include <QWidget>

namespace Ui {
class BonusFunctor;
}

class BonusFunctor : public QWidget {
	Q_OBJECT

public:
    explicit BonusFunctor(QWidget* parent = nullptr);
	~BonusFunctor();
signals:
    void req_append(const QString& value);
    void req_chop_once();
    void req_clear();

private:
    void setup_panel();
    Ui::BonusFunctor* ui;
};

#endif // BONUSFUNCTOR_H

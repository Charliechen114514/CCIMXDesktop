#ifndef SCROLLINGLABEL_H
#define SCROLLINGLABEL_H
#include <QTimer>
#include <QWidget>
class QPropertyAnimation;
namespace Ui {
class ScrollingLabel;
}

class ScrollingLabel : public QWidget {
	Q_OBJECT

public:
	static constexpr const int ANIMATION_INTERVAL = 100;
	static constexpr const short STEP_SHORT = 2;
	explicit ScrollingLabel(QWidget* parent = nullptr);
	void setText(const QString& text);
	~ScrollingLabel();

protected:
	void resizeEvent(QResizeEvent*) override {
		updateScroll();
	}
private slots:
	void scrollText();
	void updateScroll();

private:
	Ui::ScrollingLabel* ui;
	QTimer timer;
	int offset { 0 };
};

#endif // SCROLLINGLABEL_H

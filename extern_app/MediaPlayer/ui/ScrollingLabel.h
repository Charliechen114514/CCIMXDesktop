#ifndef SCROLLINGLABEL_H
#define SCROLLINGLABEL_H
#include <QTimer>
#include <QWidget>
class QPropertyAnimation;
namespace Ui {
class ScrollingLabel;
}

/**
 * @brief The ScrollingLabel class provides the scrolling label
 * @note this is a simple scrolling label,
 * for text too long, it will roll the text automatically
 */
class ScrollingLabel : public QWidget {
	Q_OBJECT

public:
	/**
	 * @brief ANIMATION_INTERVAL the animation interval
	 */
	static constexpr const int ANIMATION_INTERVAL = 100;
	/**
	 * @brief STEP_SHORT the step short everytime the
	 * animations make the text scroll in pix level
	 * so, make it larger will speed up the roll process
	 */
	static constexpr const short STEP_SHORT = 2;
	/**
	 * @brief Construct a new Scrolling Label object
	 * 
	 * @param parent 
	 */
	explicit ScrollingLabel(QWidget* parent = nullptr);

	/**
	 * @brief setText set the text of the label
	 * @param text	the text to set
	 */
	void setText(const QString& text);
	~ScrollingLabel();

protected:
	/**
	 * @brief resize hooks
	 * 
	 */
	void resizeEvent(QResizeEvent*) override {
		updateScroll();
	}
private slots:
	void scrollText(); ///< the slot to scroll the text
	void updateScroll(); ///< the slot to update the scroll

private:
	Ui::ScrollingLabel* ui;
	QTimer timer;
	int offset { 0 };
};

#endif // SCROLLINGLABEL_H

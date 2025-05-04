#ifndef STACKPAGESWITCHER_H
#define STACKPAGESWITCHER_H

#include <QObject>
class QStackedWidget;

struct StackpageSwitcherAnimation : public QObject {
	Q_OBJECT
public:
	explicit StackpageSwitcherAnimation(QObject* parent = nullptr)
		: QObject(parent) { }

	struct AnimationInfo {
		int new_index;
		bool toLeft;
		int animation_duration { 400 };
	};

	static void process_animations(
		QStackedWidget* binding_widget,
		AnimationInfo* animation_info);
};

#endif // STACKPAGESWITCHER_H

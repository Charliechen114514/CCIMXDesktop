#ifndef STACKPAGE_SWITCHER_ANIMATION_H
#define STACKPAGE_SWITCHER_ANIMATION_H
#include <QObject>
class QStackedWidget;

/**
 * @brief The StackpageSwitcherAnimation class
 * holdings the animations of the stack page animations
 */
struct StackpageSwitcherAnimation : public QObject {
	Q_OBJECT
public:
	/**
	 * @brief Construct a new Stackpage Switcher Animation object
	 * 
	 * @param parent 
	 */
	explicit StackpageSwitcherAnimation(QObject* parent = nullptr)
		: QObject(parent) { }

	static constexpr unsigned short ANIMATION_DURATION = 400; ///< the animation duration

	/**
	 * @brief The AnimationInfo class contains the animation info
	 * that the static functions process_animations requires
	 * @see process_animations
	 */
	struct AnimationInfo {
		int new_index; ///< the new index to be switched
		bool toLeft; ///< the direction of the animation
		int animation_duration { ANIMATION_DURATION }; ///< the animation duration
	};

	/**
	 * @brief process_animations process the animations
	 * @param binding_widget the widget to be animated
	 * @param animation_info the animation info
	 */
	static void process_animations(
		QStackedWidget* binding_widget,
		AnimationInfo* animation_info);
};

#endif // STACKPAGE_SWITCHER_ANIMATION_H

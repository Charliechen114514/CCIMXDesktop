#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QEasingCurve>
#include <QWidget>

class QPropertyAnimation;
class QParallelAnimationGroup;

/// @namespace SideBarWidgetStaticConfig
/// @brief Contains default configuration constants for SideBarWidget animations.
namespace SideBarWidgetStaticConfig {
static constexpr const bool INIT_STATE = false; ///< Initial visibility state (false means visible).
static constexpr const int ANIMATION_DURATION = 500; ///< Default animation duration in milliseconds.
static constexpr const QEasingCurve::Type ANIMATION_CURVE = QEasingCurve::InOutQuad; ///< Default easing curve type.
}; // namespace SideBarWidgetStaticConfig

namespace Ui {
class SideBarWidget;
}

/// @class SideBarWidget
/// @brief A custom widget that implements a slide-in/slide-out sidebar with animation.
class SideBarWidget : public QWidget {
	Q_OBJECT

public:
	/// @brief Constructor to initialize the sidebar widget.
	/// @param parent Optional parent widget.
	explicit SideBarWidget(QWidget* parent = nullptr);

	/// @brief Destructor to release resources.
	~SideBarWidget();

	/// @brief Shows the sidebar using animation.
	void inline showSideBar() {
		setState(false);
	}

	/// @brief Hides the sidebar using animation.
	void inline hideSideBar() {
		setState(true);
	}

	/// @brief Defines which layout role to apply widgets to.
	enum class Role { SideBar,
					  MainSide };

	/// @brief Adds widgets to either the sidebar or the main side layout.
	/// @param widgetList The list of widgets to add.
	/// @param r The role indicating target layout.
	void addLayout(const QWidgetList& widgetList, Role r);

	/// @brief Removes all widgets from the specified layout role.
	/// @param r The role indicating which layout to clear.
	void removeLayout(Role r);

	/// @brief Sets the visibility of the control button.
	/// @param visible Whether the button should be visible.
	void setButtonVisible(bool visible);

	/// @brief Sets the animation duration.
	/// @param duration Duration in milliseconds.
	void setAnimationDuration(int duration);

	/// @brief Sets the easing curve type for the animation.
	/// @param curve The easing curve to use.
	void setAnimationCurve(QEasingCurve::Type curve);

	/// @brief Returns the current state of sidebar visibility.
	/// @return True if hidden, false if visible.
	inline bool current_ui_states() { return hidden_state; }

public slots:
	/// @brief Toggles the sidebar state between visible and hidden.
	void switch_state();

	/// @brief Toggles the button visibility.
	void switch_button_visible();

private:
	QPropertyAnimation* animation_main; ///< Animation for main content.
	QPropertyAnimation* animation_side; ///< Animation for sidebar content.
	QPropertyAnimation* animation_button; ///< Animation for toggle button.
	QParallelAnimationGroup* group; ///< Group to synchronize animations.

	/// @brief Sets the current visibility state and triggers animations.
	/// @param st True to hide, false to show.
	void inline setState(bool st) {
		hidden_state = st;
		hidden_state ? do_hide_animations() : do_show_animations();
	}

	/// @brief Initializes internal memory and states.
	void __initMemory();

	/// @brief Initializes signal-slot connections.
	void __initConnection();

	/// @brief Performs hide animation.
	void do_hide_animations();

	/// @brief Performs show animation.
	void do_show_animations();

	bool hidden_state { SideBarWidgetStaticConfig::INIT_STATE }; ///< Current hidden state.
	Ui::SideBarWidget* ui; ///< Pointer to the auto-generated UI class.
};

#endif // SIDEBARWIDGET_H

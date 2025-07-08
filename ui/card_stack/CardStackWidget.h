#ifndef CARDSTACKWIDGET_H
#define CARDSTACKWIDGET_H

#include "library/limited_value/ValueLimiter.hpp"
#include <QPointer>
#include <QStackedWidget>

// Forward declarations
class QPropertyAnimation;
class QParallelAnimationGroup;
class QGraphicsOpacityEffect;
class QMutex;

/**
 * @class CardStackWidget
 * @brief An enhanced QStackedWidget with animated card transitions
 *
 * Provides a stack of widgets with customizable transition animations
 * (slide/fade) and optional automatic switching between cards.
 */
class CardStackWidget : public QStackedWidget {
    Q_OBJECT

public:
    static constexpr ValueLimitSimplePair animation_bound { 250, 500 }; /**< Bounds for animation duration */
    static constexpr ValueLimitSimplePair timer_switch_invoker { 3000, 10000 }; /**< Bounds for auto-switch timer */

    /**
     * @brief Constructs a CardStackWidget
     * @param parent Parent widget (optional)
     */
    explicit CardStackWidget(QWidget* parent = nullptr);

    /**
     * @enum CardTransitionMode
     * @brief Available transition animation modes
     */
    enum class CardTransitionMode {
        Slide, /**< Slide animation between cards */
        Fade /**< Fade animation between cards */
    };

    /**
     * @brief Sets the transition animation mode
     * @param mode The transition mode to use
     */
    void setCardTransitionMode(CardTransitionMode mode);

    /**
     * @brief Gets the current transition mode
     * @return The current transition mode
     */
    CardTransitionMode cardTransitionMode() const;

    /**
     * @brief Animates transition to a specific card
     * @param newIndex Index of the card to transition to
     */
    void slideTo(int newIndex);

    /**
     * @brief Enables/disables automatic card switching
     * @param ability true to enable, false to disable
     */
    void setablility_of_autoSwitch(bool ability);

    /**
     * @brief Checks if auto-switching is enabled
     * @return true if enabled, false otherwise
     */
    bool autoSwitchAbility();

    __BOUND_PROPERTY_GETSET_UNALLOWED_OUTRANGE(
        int, animation_duration, animation_bound); ///< @property Bounded property for animation duration

    __BOUND_PROPERTY_GETSET_UNALLOWED_OUTRANGE(
        int, randomize_duration, timer_switch_invoker); ///< @property Bounded property for auto-switch randomization duration

protected:
    /**
     * @brief Handles mouse press events for drag detection
     * @param event The mouse event
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * @brief Handles mouse release events for drag completion
     * @param event The mouse event
     */
    void mouseReleaseEvent(QMouseEvent* event) override;

    /**
     * @brief Handles mouse move events for drag tracking
     * @param event The mouse event
     */
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    bool isDragging { false }; /**< Flag indicating drag in progress */
    QPoint startPos; /**< Starting position for drag operations */
    QPropertyAnimation* current_animation; /**< Animation for current widget */
    QPropertyAnimation* next_animation; /**< Animation for next widget */
    QParallelAnimationGroup* group; /**< Animation group for parallel effects */
    QPointer<QWidget> hideAfterAnimation; /**< Widget to hide after animation */
    int animation_duration { 350 }; /**< Current animation duration */
    int randomize_duration { 2000 }; /**< Auto-switch randomization duration */
    QTimer* auto_switcher; /**< Timer for automatic switching */
    std::shared_ptr<QMutex> mutex; /**< Mutex for thread safety */
    CardTransitionMode transitionMode = CardTransitionMode::Fade; /**< Current transition mode */

    /**
     * @brief Slides to a card with specified direction
     * @param newIndex Index of card to transition to
     * @param slideUp true for upward slide, false for downward
     */
    void slideTo(int newIndex, bool slideUp);

    /**
     * @brief Bounces back from a partial drag
     * @param dy Vertical drag distance
     * @param index Current card index
     */
    void bouceBack(int dy, int index);

    /**
     * @brief Ensures opacity effect exists for a widget
     * @param w Widget to check/modify
     * @return Existing or new opacity effect
     */
    QGraphicsOpacityEffect* ensureOpacity(QWidget* w);
};

#endif // CARDSTACKWIDGET_H

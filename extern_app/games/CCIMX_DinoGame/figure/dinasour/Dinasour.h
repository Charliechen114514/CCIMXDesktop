#ifndef DINASOUR_H
#define DINASOUR_H
#include "figure/FigureObject.h"
#include <QPixmap>
class DinasourFrameFetcher;
/**
 * @brief The Dinasour Object handle
 */
class Dinasour : public FigureObject {
	Q_OBJECT
public:
	/**
	 * @brief Dinasour creator
	 * @param parent
	 */
	explicit Dinasour(QObject* parent = nullptr);
	/**
	 * @brief States of Dinasour supports
	 * 
	 */
	enum class State {
		READY, ///< dinasour ready!
		RUNNING, ///< normal run
		LAYING, ///< laying run
		/* src will be locked to the die frame */
		DIE ///< dinasour die
	};
	/**
	 * @brief isJumping is our cute jumping?
	 * @return result
	 */
	bool isJumping() const { return is_jumping; }
	/**
	 * @brief make_jump jump!
	 */
	void make_jump();
	/**
	 * @brief isLaying is our cute laying(ducking actually...)?
	 * @return result
	 */
	bool isLaying() const { return is_laying; }
	/**
	 * @brief set_laying set lay status
	 * @param st
	 */
	void set_laying(bool st);
	/**
	 * @brief process_animation using in game update for dinosaur action
	 */
	void process_animation();
	/**
	 * @brief set_providing_state set the state of dinasour
	 * @param s
	 */
	void set_providing_state(State s);
	/**
	 * @brief provide_current_bounding_rect bounding rect
	 * @return bounding rect
	 */
	QRect& provide_current_bounding_rect() override;
	/**
	 * @brief provide_current_bounding_rect pixmap for draw
	 * @return drawable map
	 */
	QPixmap& provide_drawing_srcframe() override;

private:
	/* frame sources */
	DinasourFrameFetcher* normal_run; ///< normal run src
	DinasourFrameFetcher* lay_run; ///< lay run src
	QPixmap die_map; ///< oh...
	QPixmap ready_map; ///< ready!

	/**
	 * @brief setup_frame_provider setup the frame sources
	 */
	void setup_frame_provider();
	QRect jump_rect; ///< jumping rect
	State current_state { State::READY }; ///< curret status
	bool is_jumping { false }; ///< is jumping?
	bool is_laying { false }; ///< is ducking
	int velocityY { 0 }; /// dinasour velocity
};

#endif // DINASOUR_H

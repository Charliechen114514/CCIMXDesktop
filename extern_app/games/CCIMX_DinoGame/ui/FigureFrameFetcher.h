/**
 * @file FigureFrameFetcher.h
 * @brief Declares frame fetcher classes for game figures and obstacles.
 */

#ifndef FIGUREFRAMEFETCHER_H
#define FIGUREFRAMEFETCHER_H

#include "core/FrameProvider.h"

/**
 * @class DinasourFrameFetcher
 * @brief Provides frame data for the dinosaur character based on its state.
 */
class DinasourFrameFetcher : public FrameProvider {
    Q_OBJECT
public:
	/**
	 * @brief States the dinosaur character can be in.
	 */
	enum class State {
		NORMAL, ///< Normal standing/running state
		LAY ///< Crouching/laying state
	};

	/**
	 * @brief Sets the current frame state.
	 * @param s The new state.
	 */
	void set_frame_state(State s) { this->s = s; }

	/**
	 * @brief Constructs the dinosaur frame fetcher with a valid base path.
	 * @param valid_base_path Base path to the frame resources.
	 * @param parent The parent QObject.
	 */
	explicit DinasourFrameFetcher(const QString& valid_base_path, QObject* parent);

	/**
	 * @brief Returns the current source bounding rectangle.
	 * @return Reference to the QRect representing the bounding rect.
	 */
	QRect& src_bounding_rect() override;

private:
	/**
	 * @brief The current source rectangle for rendering.
	 */
	QRect src_rect;

	/**
	 * @brief The current state of the dinosaur.
	 */
	State s;
};

/**
 * @class ObstacleBaseFrameFetch
 * @brief Abstract base class for obstacle frame providers.
 */
class ObstacleBaseFrameFetch : public FrameProvider {
    Q_OBJECT
public:
	/**
	 * @brief Constructs the base obstacle frame fetcher.
	 * @param valid_base_path Path to valid frame resources.
	 * @param parent The parent QObject.
	 */
	explicit ObstacleBaseFrameFetch(const QString& valid_base_path, QObject* parent);

	/**
	 * @brief Returns the source bounding rectangle.
	 * @return Reference to the QRect representing the bounding rect.
	 */
	virtual QRect& src_bounding_rect() = 0;

private:
	/**
	 * @brief The current source rectangle.
	 */
	QRect src_rect;
};

/**
 * @class CactusFrameFetch
 * @brief Frame fetcher for cactus-type obstacles.
 */
class CactusFrameFetch : public ObstacleBaseFrameFetch {
    Q_OBJECT
public:
	/**
	 * @brief Constructs a cactus frame fetcher.
	 * @param valid_base_path Path to frame resources.
	 * @param parent The parent QObject.
	 */
	explicit CactusFrameFetch(const QString& valid_base_path, QObject* parent);

	/**
	 * @brief Returns the source bounding rectangle.
	 * @return Reference to the QRect representing the bounding rect.
	 */
	QRect& src_bounding_rect() override { return src_rect; }

private:
	/**
	 * @brief The source rectangle for the cactus frame.
	 */
	QRect src_rect;
};

/**
 * @class BirdFrameFetch
 * @brief Frame fetcher for bird-type obstacles.
 */
class BirdFrameFetch : public ObstacleBaseFrameFetch {
    Q_OBJECT
public:
	/**
	 * @brief Constructs a bird frame fetcher.
	 * @param valid_base_path Path to frame resources.
	 * @param parent The parent QObject.
	 */
	explicit BirdFrameFetch(const QString& valid_base_path, QObject* parent);

	/**
	 * @brief Returns the source bounding rectangle.
	 * @return Reference to the QRect representing the bounding rect.
	 */
	QRect& src_bounding_rect() override { return src_rect; }

private:
	/**
	 * @brief The source rectangle for the bird frame.
	 */
	QRect src_rect;
};

#endif // FIGUREFRAMEFETCHER_H

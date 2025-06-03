/**
 * @file settings_figure.h
 * @brief Defines configuration constants for figures like the dinosaur, cactus, and bird.
 */

#ifndef SETTINGS_FIGURE_H
#define SETTINGS_FIGURE_H

#include "settings/setting_scene.h"
#include "settings_common.h"

namespace Settings {
namespace Figure {

	/**
	 * @brief FIGURE_FRAME_FLUSH_MS specifies the frame update interval (in milliseconds) for animated figures.
	 */
	static constexpr const unsigned short FIGURE_FRAME_FLUSH_MS = 200;

	namespace Dinasour {
		/**
		 * @brief DinasourSZ defines the size of the dinosaur.
		 */
		static constexpr FigureSize DinasourSZ = { 60, 60 };

		/**
		 * @brief WIDTH and HEIGHT are extracted from DinasourSZ for convenience.
		 */
		static constexpr unsigned short WIDTH = Settings::SZ<DinasourSZ>::width; ///< width
		static constexpr unsigned short HEIGHT = Settings::SZ<DinasourSZ>::height; ///< height

		/**
		 * @brief DinasourPOS sets the initial position of the dinosaur, aligned to ground level.
		 */
		static constexpr Position DinasourPOS = { 60, Scene::Ground::GROUND_Y_POS - HEIGHT }; ///< pos
		static constexpr unsigned short X = Settings::XY<DinasourPOS>::x; ///< x
		static constexpr unsigned short Y = Settings::XY<DinasourPOS>::y; ///< y

		/**
		 * @brief FRAME_1 and FRAME_2 are the animation frames of the dinosaur.
		 * @brief FRAME_SHIT is a humorous or special-case frame (e.g. damage or event).
		 */
		static constexpr const char* FRAME_1 = ":/frame/frames/dino_frame1.png"; ///< frame1
		static constexpr const char* FRAME_2 = ":/frame/frames/dino_frame2.png"; ///< frame2
		static constexpr const char* FRAME_SHIT = ":/frame/frames/ah_shit.png"; ///< frame3

		/**
		 * @brief JUMP_ABILITY defines the vertical velocity applied during a jump.
		 */
		static constexpr const short JUMP_ABILITY = -18;
	}

	namespace Obstacle {
		/**
		 * @brief MOVE_BOUND_OUT defines the X position after which an obstacle is considered off-screen.
		 * @brief MOVE_BOUND_GAP defines the minimum X spacing between obstacles.
		 */
		static constexpr const unsigned short MOVE_BOUND_OUT = 501; ///< space underlimit
		static constexpr const unsigned short MOVE_BOUND_GAP = 350; ///< range
	}

	namespace Cactus {
		/**
		 * @brief Definitions for various cactus sizes.
		 */
		static constexpr FigureSize CactusSZ_SMALL = { 20, 65 }; ///< small
		static constexpr FigureSize CactusSZ_MED = { 25, 85 }; ///< mid
		static constexpr FigureSize CactusSZ_LARGE = { 30, 110 }; ///< large
		static constexpr FigureSize DEF_SZ = CactusSZ_SMALL;

		/**
		 * @brief WIDTH and HEIGHT of the default cactus.
		 */
		static constexpr unsigned short WIDTH = Settings::SZ<DEF_SZ>::width; ///< width
		static constexpr unsigned short HEIGHT = Settings::SZ<DEF_SZ>::height; ///< height

		/**
		 * @brief Y positions for each cactus type, aligned to ground.
		 */
		static constexpr unsigned int SMALL_BASE_Y_POS = Scene::Ground::GROUND_Y_POS - Settings::SZ<CactusSZ_SMALL>::height; ///< height
		static constexpr unsigned int MED_BASE_Y_POS = Scene::Ground::GROUND_Y_POS - Settings::SZ<CactusSZ_MED>::height; ///< height
		static constexpr unsigned int LARGE_BASE_Y_POS = Scene::Ground::GROUND_Y_POS - Settings::SZ<CactusSZ_LARGE>::height; ///< height

		/**
		 * @brief INIT_POS is the initial spawn position of a cactus obstacle.
		 */
		static constexpr Position INIT_POS = { Scene::SCENE_FIXED_SZ.first - 40, SMALL_BASE_Y_POS }; ///< pos
		static constexpr unsigned short X = Settings::XY<INIT_POS>::x; ///< x
		static constexpr unsigned short Y = Settings::XY<INIT_POS>::y; ///< y

		/**
		 * @brief Frames for different cactus types or animations.
		 */
		static constexpr const char* FRAME_1 = ":/frame/frames/cac_frame1.png"; ///< frame1
		static constexpr const char* FRAME_2 = ":/frame/frames/cac_frame2.png"; ///< frame2
		static constexpr const char* FRAME_3 = ":/frame/frames/cac_frame3.png"; ///< frame3
		static constexpr const char* FRAME_4 = ":/frame/frames/cac_frame4.png"; ///< frame4
	}

	namespace Bird {
		/**
		 * @brief BIRD_APPEAR_AT_MSEC defines the delay before birds start appearing.
		 */
		static constexpr const unsigned int BIRD_APPEAR_AT_MSEC = 10000;

		/**
		 * @brief Different size options for birds.
		 */
		static constexpr FigureSize SmallBirdSize = { 30, 30 }; ///< small
		static constexpr FigureSize MediumBirdSize = { 45, 50 }; ///< medium
		static constexpr FigureSize LargeBirdSize = { 60, 60 }; ///< large

		/**
		 * @brief Y positions for bird flight paths based on size.
		 */
		static constexpr unsigned int SMALL_BASE_Y_POS = Scene::Ground::GROUND_Y_POS - Settings::SZ<SmallBirdSize>::height; ///< height
		static constexpr unsigned int MED_BASE_Y_POS = Scene::Ground::GROUND_Y_POS - Settings::SZ<MediumBirdSize>::height; ///< height
		static constexpr unsigned int LARGE_BASE_Y_POS = Scene::Ground::GROUND_Y_POS - Settings::SZ<LargeBirdSize>::height; ///< height

		/**
		 * @brief WIDTH and HEIGHT for the bird, using small size by default.
		 */
		static constexpr unsigned short WIDTH = Settings::SZ<SmallBirdSize>::width; ///< width
		static constexpr unsigned short HEIGHT = Settings::SZ<SmallBirdSize>::height; ///< height

		/**
		 * @brief Animation frames for bird flapping.
		 */
		static constexpr const char* FRAME_1 = ":/frame/frames/bird1.png"; ///< frame1
		static constexpr const char* FRAME_2 = ":/frame/frames/bird2.png"; ///< frame2

		/**
		 * @brief Predefined Y positions representing different flight heights.
		 */
		static constexpr const unsigned short LOW_HEIGHT = Scene::Ground::GROUND_Y_POS - HEIGHT - 5;
		static constexpr const unsigned short MED_HEIGHT = Scene::Ground::GROUND_Y_POS - HEIGHT - 45;
		static constexpr const unsigned short HIG_HEIGHT = Scene::Ground::GROUND_Y_POS - HEIGHT - 180;

		/**
		 * @brief INIT_POS sets the bird's initial position on screen.
		 */
		static constexpr Position INIT_POS = { Scene::SCENE_FIXED_SZ.first - 40, LOW_HEIGHT }; ///< pos
		static constexpr unsigned short X = Settings::XY<INIT_POS>::x; ///< x
		static constexpr unsigned short Y = Settings::XY<INIT_POS>::y; ///< y
	}

}
}

#endif // SETTINGS_FIGURE_H


/**
 * @file setting_scene.h
 * @brief Defines constants and settings related to the game scene and its behavior.
 */

#ifndef SETTING_SCENE_H
#define SETTING_SCENE_H

#include "core/DifficultyType.h"
#include "settings_common.h"

namespace Settings {
namespace Scene {

	/**
	 * @brief SCENE_FIXED_SZ sets the fixed size of the scene.
	 */
	static constexpr SceneSize SCENE_FIXED_SZ = { 1024, 590 };

	/**
	 * @brief SCENE_FLUSH_HZ defines the refresh rate in milliseconds (60Hz ≈ 16ms).
	 */
	static constexpr unsigned short SCENE_FLUSH_HZ = 16;

	namespace Ground {
		/**
		 * @brief GROUND_Y_POS specifies the vertical position of the ground.
		 */
		static constexpr unsigned short GROUND_Y_POS = 450;

		/**
		 * @brief GROUND_PEN_WIDTH specifies the width of the ground pen/stroke.
		 */
		static constexpr unsigned short GROUND_PEN_WIDTH = 3;
	}

	namespace Grivity {
		/**
		 * @brief Y_G_APPEND is the vertical acceleration increment (gravity effect).
		 */
		static constexpr unsigned short Y_G_APPEND = 1;
	}

	using DifficultyType = Difficulty;

	namespace Difficulty {
		/**
		 * @brief START_DIFFICULTY is the default difficulty level at game start.
		 */
		static constexpr DifficultyType START_DIFFICULTY = DifficultyType::EASY;

		/**
		 * @brief MAX_OBS_CNT defines the maximum number of simultaneous obstacles.
		 * @note Do not modify this value arbitrarily.
		 */
		static constexpr unsigned short MAX_OBS_CNT = 5;
		static_assert(MAX_OBS_CNT >= 4); ///< Ensures a valid number of obstacles

		/**
		 * @brief INIT_OBS_CNT specifies the initial number of obstacles.
		 */
		static constexpr unsigned short INIT_OBS_CNT = 2;

		/**
		 * @brief SPEED_EASY defines movement speed for EASY difficulty.
		 */
		static constexpr unsigned short SPEED_EASY = 5;

		/**
		 * @brief SPEED_MEDIUM defines movement speed for MEDIUM difficulty.
		 */
		static constexpr unsigned short SPEED_MEDIUM = 8;

		/**
		 * @brief SPEED_HARD defines movement speed for HARD difficulty.
		 */
		static constexpr unsigned short SPEED_HARD = 10;

		/**
		 * @brief SPEED_MAX defines the maximum movement speed.
		 */
		static constexpr unsigned short SPEED_MAX = 15;

		/**
		 * @brief DEF_SPEED sets the default movement speed (same as EASY).
		 */
		static constexpr unsigned short DEF_SPEED = SPEED_EASY;

		/**
		 * @brief INIT_PEROID is the time duration for the initial phase.
		 */
		static constexpr unsigned int INIT_PEROID = 5000;

		/**
		 * @brief SIMPLE_PEROID is the time duration for EASY difficulty phase.
		 */
		static constexpr unsigned int SIMPLE_PEROID = 5000;

		/**
		 * @brief MEDIUM_PEROID is the time duration for MEDIUM difficulty phase.
		 */
		static constexpr unsigned int MEDIUM_PEROID = 5000;

		/**
		 * @brief HARD_PEROID is the time duration for HARD difficulty phase.
		 */
		static constexpr unsigned int HARD_PEROID = 5000;
	}

	namespace BackGround {
		namespace RandomLine {
			/**
			 * @brief groundY is the base Y coordinate for background lines.
			 */
			constexpr int groundY = 100;

			/**
			 * @brief minLineLength specifies the minimum length of background line segments.
			 */
			constexpr int minLineLength = 4;

			/**
			 * @brief maxLineLength specifies the maximum length of background line segments.
			 */
			constexpr int maxLineLength = 20;

			/**
			 * @brief phaseMax is the upper bound of phase values (usually 2π).
			 */
			constexpr float phaseMax = 6.28f;

			/**
			 * @brief oscillationAmplitude defines the vertical wave amplitude for lines.
			 */
			constexpr float oscillationAmplitude = 2.5f;

			/**
			 * @brief timeFrequency defines how fast the wave oscillates.
			 */
			constexpr float timeFrequency = 4.0f;

			/**
			 * @brief yOffsetMin defines the minimum Y coordinate for drawing line peaks.
			 */
			constexpr int yOffsetMin = groundY + 1;
		}
	}

}
}

#endif // SETTING_SCENE_H

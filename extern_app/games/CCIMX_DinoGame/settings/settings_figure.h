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
     * @struct FigureSize
     * @brief Represents the width and height of a figure.
     */
    struct FigureSize {
        unsigned short width; ///< Width of the figure
        unsigned short height; ///< Height of the figure
    };

    /**
     * @struct Position
     * @brief Represents a 2D position with x and y coordinates.
     */
    struct Position {
        unsigned short x; ///< X coordinate
        unsigned short y; ///< Y coordinate
    };

    // Helper functions for C++17 compatibility

    /**
     * @brief Gets the width from a FigureSize.
     * @param fs The FigureSize instance.
     * @return Width of the figure.
     */
    inline constexpr unsigned short getWidth(const FigureSize& fs) noexcept {
        return fs.width;
    }

    /**
     * @brief Gets the height from a FigureSize.
     * @param fs The FigureSize instance.
     * @return Height of the figure.
     */
    inline constexpr unsigned short getHeight(const FigureSize& fs) noexcept {
        return fs.height;
    }

    /**
     * @brief Gets the X coordinate from a Position.
     * @param p The Position instance.
     * @return X coordinate.
     */
    inline constexpr unsigned short getX(const Position& p) noexcept {
        return p.x;
    }

    /**
     * @brief Gets the Y coordinate from a Position.
     * @param p The Position instance.
     * @return Y coordinate.
     */
    inline constexpr unsigned short getY(const Position& p) noexcept {
        return p.y;
    }

    /**
     * @brief Frame flush interval for animated figures (in milliseconds).
     */
    static constexpr unsigned short FIGURE_FRAME_FLUSH_MS = 200;

    /**
     * @namespace Dinasour
     * @brief Configuration constants related to the dinosaur figure.
     */
    namespace Dinasour {
        static constexpr FigureSize DinasourSZ = { 60, 60 }; ///< Size of the dinosaur
        static constexpr unsigned short WIDTH = getWidth(DinasourSZ); ///< Width of the dinosaur
        static constexpr unsigned short HEIGHT = getHeight(DinasourSZ); ///< Height of the dinosaur

        static constexpr Position DinasourPOS = { 60, Scene::Ground::GROUND_Y_POS - HEIGHT }; ///< Initial position
        static constexpr unsigned short X = getX(DinasourPOS); ///< X coordinate
        static constexpr unsigned short Y = getY(DinasourPOS); ///< Y coordinate

        static constexpr const char* FRAME_1 = ":/frame/frames/dino_frame1.png"; ///< First animation frame
        static constexpr const char* FRAME_2 = ":/frame/frames/dino_frame2.png"; ///< Second animation frame
        static constexpr const char* FRAME_SHIT = ":/frame/frames/ah_shit.png"; ///< Special/humorous frame

        static constexpr const short JUMP_ABILITY = -18; ///< Jump velocity
    }

    /**
     * @namespace Obstacle
     * @brief General configuration for obstacles.
     */
    namespace Obstacle {
        static constexpr const unsigned short MOVE_BOUND_OUT = 501; ///< Off-screen boundary
        static constexpr const unsigned short MOVE_BOUND_GAP = 350; ///< Minimum spacing between obstacles
    }

    /**
     * @namespace Cactus
     * @brief Configuration constants for cactus obstacles.
     */
    namespace Cactus {
        static constexpr FigureSize CactusSZ_SMALL = { 20, 65 }; ///< Small cactus size
        static constexpr FigureSize CactusSZ_MED = { 25, 85 }; ///< Medium cactus size
        static constexpr FigureSize CactusSZ_LARGE = { 30, 110 }; ///< Large cactus size
        static constexpr FigureSize DEF_SZ = CactusSZ_SMALL; ///< Default cactus size

        static constexpr unsigned short WIDTH = getWidth(DEF_SZ); ///< Default width
        static constexpr unsigned short HEIGHT = getHeight(DEF_SZ); ///< Default height

        static constexpr unsigned int SMALL_BASE_Y_POS = Scene::Ground::GROUND_Y_POS - getHeight(CactusSZ_SMALL); ///< Y position for small cactus
        static constexpr unsigned int MED_BASE_Y_POS = Scene::Ground::GROUND_Y_POS - getHeight(CactusSZ_MED); ///< Y position for medium cactus
        static constexpr unsigned int LARGE_BASE_Y_POS = Scene::Ground::GROUND_Y_POS - getHeight(CactusSZ_LARGE); ///< Y position for large cactus

        static constexpr Position INIT_POS = { Scene::SCENE_FIXED_SZ.first - 40, SMALL_BASE_Y_POS }; ///< Initial spawn position
        static constexpr unsigned short X = getX(INIT_POS); ///< X coordinate
        static constexpr unsigned short Y = getY(INIT_POS); ///< Y coordinate

        static constexpr const char* FRAME_1 = ":/frame/frames/cac_frame1.png"; ///< Frame 1
        static constexpr const char* FRAME_2 = ":/frame/frames/cac_frame2.png"; ///< Frame 2
        static constexpr const char* FRAME_3 = ":/frame/frames/cac_frame3.png"; ///< Frame 3
        static constexpr const char* FRAME_4 = ":/frame/frames/cac_frame4.png"; ///< Frame 4
    }

    /**
     * @namespace Bird
     * @brief Configuration constants for bird obstacles.
     */
    namespace Bird {
        static constexpr const unsigned int BIRD_APPEAR_AT_MSEC = 10000; ///< Delay before birds appear (ms)

        static constexpr FigureSize SmallBirdSize = { 30, 30 }; ///< Small bird size
        static constexpr FigureSize MediumBirdSize = { 45, 50 }; ///< Medium bird size
        static constexpr FigureSize LargeBirdSize = { 60, 60 }; ///< Large bird size

        static constexpr unsigned int SMALL_BASE_Y_POS = Scene::Ground::GROUND_Y_POS - getHeight(SmallBirdSize); ///< Y position for small bird
        static constexpr unsigned int MED_BASE_Y_POS = Scene::Ground::GROUND_Y_POS - getHeight(MediumBirdSize); ///< Y position for medium bird
        static constexpr unsigned int LARGE_BASE_Y_POS = Scene::Ground::GROUND_Y_POS - getHeight(LargeBirdSize); ///< Y position for large bird

        static constexpr unsigned short WIDTH = getWidth(SmallBirdSize); ///< Default bird width
        static constexpr unsigned short HEIGHT = getHeight(SmallBirdSize); ///< Default bird height

        static constexpr const char* FRAME_1 = ":/frame/frames/bird1.png"; ///< Wing-up frame
        static constexpr const char* FRAME_2 = ":/frame/frames/bird2.png"; ///< Wing-down frame

        static constexpr const unsigned short LOW_HEIGHT = Scene::Ground::GROUND_Y_POS - HEIGHT - 5; ///< Low flight height
        static constexpr const unsigned short MED_HEIGHT = Scene::Ground::GROUND_Y_POS - HEIGHT - 45; ///< Medium flight height
        static constexpr const unsigned short HIG_HEIGHT = Scene::Ground::GROUND_Y_POS - HEIGHT - 180; ///< High flight height

        static constexpr Position INIT_POS = { Scene::SCENE_FIXED_SZ.first - 40, LOW_HEIGHT }; ///< Initial bird position
        static constexpr unsigned short X = getX(INIT_POS); ///< X coordinate
        static constexpr unsigned short Y = getY(INIT_POS); ///< Y coordinate
    }

} // namespace Figure
} // namespace Settings

#endif // SETTINGS_FIGURE_H

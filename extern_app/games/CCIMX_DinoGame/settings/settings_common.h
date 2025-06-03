#ifndef SETTINGS_COMMON_H
#define SETTINGS_COMMON_H
#include <QPair>
#include <QPoint>

namespace Settings {

/**
 * @brief Alias for scene size represented by width and height.
 */
using SceneSize = QPair<unsigned short, unsigned short>;

/**
 * @brief Alias for figure size represented by width and height.
 */
using FigureSize = QPair<unsigned short, unsigned short>;

/**
 * @brief Template struct to extract width and height from a QPair size value.
 *
 * @tparam value A QPair representing size (width, height).
 */
template <auto value>
struct SZ {
	/**
	 * @brief Width component of the size.
	 */
	static constexpr unsigned short width = value.first;

	/**
	 * @brief Height component of the size.
	 */
	static constexpr unsigned short height = value.second;
};

/**
 * @brief Alias for position represented by x and y coordinates.
 */
using Position = QPair<unsigned short, unsigned short>;

/**
 * @brief Template struct to extract x and y coordinates from a QPair position value.
 *
 * @tparam value A QPair representing position (x, y).
 */
template <auto value>
struct XY {
	/**
	 * @brief X coordinate.
	 */
	static constexpr unsigned short x = value.first;

	/**
	 * @brief Y coordinate.
	 */
	static constexpr unsigned short y = value.second;
};

}

#endif // SETTINGS_COMMON_H

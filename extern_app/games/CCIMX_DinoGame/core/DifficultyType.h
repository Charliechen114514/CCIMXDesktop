#ifndef DIFFICULTYTYPE_H
#define DIFFICULTYTYPE_H

#include <QString>

/**
 * @enum Difficulty
 * @brief Enumeration representing different game difficulty levels
 *
 * This enum defines the possible difficulty levels for the game,
 * ranging from easiest to most challenging.
 */
enum class Difficulty {
	EASY, ///< Easy difficulty level
	MEDIUM, ///< Medium difficulty level
	HARD, ///< Hard difficulty level
	HOLY_SHIT ///< Extreme difficulty level (maximum challenge)
};

/**
 * @brief Constant representing the maximum difficulty level
 *
 * This value can be used to check if the game has reached its highest
 * difficulty setting.
 */
static constexpr const Difficulty MAX_DIFFICULTY = Difficulty::HOLY_SHIT;

/**
 * @brief Converts a Difficulty enum value to its string representation
 * @param d The difficulty level to convert
 * @return QString containing the human-readable difficulty name
 *
 * This function provides a convenient way to display difficulty levels
 * in the UI or logs. Each difficulty level has a distinct string
 * representation, with the highest level having a more colorful description.
 */
inline QString dif_str_fac(Difficulty d) {
	switch (d) {
	case Difficulty::EASY:
		return "Easy";
	case Difficulty::MEDIUM:
		return "Medium";
	case Difficulty::HARD:
		return "Hard";
	case Difficulty::HOLY_SHIT:
		return "What the fuck";
	}
	return "";
}

#endif // DIFFICULTYTYPE_H

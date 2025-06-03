#ifndef SETTINGS_SOUNDEFFECT_H
#define SETTINGS_SOUNDEFFECT_H

namespace Settings {
namespace SoundEffect {

	/**
	 * @brief File path for the jump sound effect.
	 */
	static constexpr const char* JUMP = "qrc:/soundtrack/soundeffects/jump.wav";

	/**
	 * @brief File path for the die sound effect.
	 */
	static constexpr const char* DIE = "qrc:/soundtrack/soundeffects/die.wav";

	/**
	 * @brief File path for the score point sound effect.
	 */
	static constexpr const char* SCORE = "qrc:/soundtrack/soundeffects/point.wav";

	/**
	 * @brief Default volume level for sound effects.
	 */
	static constexpr float DEF_VOL = 1.0;

} // namespace SoundEffect
} // namespace Settings

#endif // SETTINGS_SOUNDEFFECT_H

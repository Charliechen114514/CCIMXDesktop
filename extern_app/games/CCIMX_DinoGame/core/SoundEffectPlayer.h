#ifndef SOUNDEFFECTPLAYER_H
#define SOUNDEFFECTPLAYER_H

#include <QList>
#include <QObject>

class QSoundEffect;

/**
 * @class SoundEffectPlayer
 * @brief Handles playback of sound effects
 */
class SoundEffectPlayer : QObject {
public:
	/**
	 * @enum EffectIndex
	 * @brief Indexes for different sound effects
	 */
	enum class EffectIndex {
		JUMP, ///< Jump sound effect
		SCORE, ///< Score sound effect
		DIE ///< Death sound effect
	};

	/**
	 * @brief Converts EffectIndex to integer
	 * @param e Effect index to convert
	 * @return Integer representation
	 */
	static constexpr int index(const EffectIndex& e) {
		return static_cast<int>(e);
	}

	/**
	 * @brief Converts integer to EffectIndex
	 * @param e Integer to convert
	 * @return EffectIndex representation
	 */
	static constexpr EffectIndex index(const int e) {
		return static_cast<EffectIndex>(e);
	}

	/**
	 * @brief Gets total number of sound effects
	 * @return Count of available effects
	 */
	static constexpr int max_cnt() {
		return index(SoundEffectPlayer::EffectIndex::DIE) + 1;
	}

	/**
	 * @brief Constructs SoundEffectPlayer
	 * @param parent Parent QObject
	 */
	explicit SoundEffectPlayer(QObject* parent);

	/**
	 * @brief Plays specified sound effect
	 * @param index Index of effect to play
	 */
	void play(EffectIndex index);

private:
	QList<QSoundEffect*> effects; ///< List of sound effect objects

	/**
	 * @brief Initializes sound effects
	 */
	void init_sound_effect();

	/**
	 * @brief Configures individual sound effect
	 * @param index Effect to configure
	 * @param src Sound file path
	 */
	void setup_soundeffect(EffectIndex index, const char* src);
};

#endif // SOUNDEFFECTPLAYER_H

#include "SoundEffectPlayer.h"
#include "settings/settings_soundeffect.h"
#include <QSoundEffect>
SoundEffectPlayer::SoundEffectPlayer(QObject* parent)
	: QObject(parent) {
	init_sound_effect();
}

void SoundEffectPlayer::play(EffectIndex index) {
	effects[this->index(index)]->play();
}

void SoundEffectPlayer::init_sound_effect() {
	effects.resize(max_cnt());
	setup_soundeffect(
		EffectIndex::JUMP, Settings::SoundEffect::JUMP);
	setup_soundeffect(
		EffectIndex::DIE, Settings::SoundEffect::DIE);
	setup_soundeffect(
		EffectIndex::SCORE, Settings::SoundEffect::SCORE);
}

void SoundEffectPlayer::setup_soundeffect(EffectIndex index,
										  const char* src) {
	effects[this->index(index)] = new QSoundEffect(this);
	effects[this->index(index)]->setSource(QUrl(src));
	effects[this->index(index)]->setVolume(Settings::SoundEffect::DEF_VOL);
}

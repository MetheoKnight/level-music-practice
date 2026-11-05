#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(LevelMusicPlayLayer, PlayLayer) {
	// Pretend we're not in practice mode while the game picks which music to start,
	// so it chooses the level's song instead of the practice track.
	void startMusic() {
		if (!Mod::get()->getSettingValue<bool>("enabled")) {
			PlayLayer::startMusic();
			return;
		}
		bool wasPractice = m_isPracticeMode;
		m_isPracticeMode = false;
		PlayLayer::startMusic();
		m_isPracticeMode = wasPractice;
	}

	// The practice track can also be started when toggling practice mode on;
	// after the original runs, restart the level music.
	void togglePracticeMode(bool practice) {
		PlayLayer::togglePracticeMode(practice);
		if (practice && Mod::get()->getSettingValue<bool>("enabled")) {
			this->startMusic();
		}
	}
};

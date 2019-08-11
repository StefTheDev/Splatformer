#pragma once
#include "helpers.h"
#include <fmod.hpp>

namespace SoundManager {
	bool LoadSounds(std::string);
	void Release();

	extern FMOD::System* audioSystem;
	extern FMOD::Channel* loopChannel;
	extern FMOD::Channel* miscChannel;
	extern std::map<std::string, FMOD::Sound*> sounds;

	void update();
	void playSound(std::string);
	void playSound(std::string, int);
	void setSound(std::string, int);
};
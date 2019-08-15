#pragma once

#include "Utilities.h"

namespace SoundManager {
	//Initialise the manager
	FMOD_RESULT Initialise();
	//Load all the sound files from a directory
	FMOD_RESULT LoadSounds(std::string directory);
	//Release the memory of a specified sound
	void ReleaseSound(std::string sound);
	//Release the memory of all loaded sounds
	void ReleaseAll();
	//Release the manager and all loaded sounds
	void Release();

	extern FMOD::System* audioSystem;
	extern FMOD::Channel* loopChannel;
	extern FMOD::Channel* miscChannel;
	extern std::map<std::string, FMOD::Sound*> sounds;

	//Update the state of all the currently in-use channels
	void update();
	//Play a sound using its file name sans extension, and sets the mode of the sound using FMOD_MODE
	void playSound(std::string soundName, FMOD_MODE soundMode);
	//Play a sound using its file name sans extension
	void playSound(std::string soundName);
	//Sets the mode of the sound using FMOD_MODE
	void setSound(std::string soundName, FMOD_MODE soundMode);
};
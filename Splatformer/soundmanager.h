#pragma once

#include "Utilities.h"
#include <map>

#include <fmod.hpp>

namespace SoundManager {
	//Initialise the manager
	FMOD_RESULT Initialise();

	//Load all the sound files from a directory
	FMOD_RESULT LoadSounds(std::string directory);

	//Load a specific sound file
	FMOD_RESULT LoadSound(std::string path);

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
	void Update();

	//Play a sound using its file name sans extension, and sets the mode of the sound using FMOD_MODE
	FMOD_RESULT PlaySound(std::string soundName, FMOD_MODE soundMode);

	//Play a sound using its file name sans extension
	FMOD_RESULT PlaySound(std::string soundName);

	//Sets the mode of the sound using FMOD_MODE
	void SetSound(std::string soundName, FMOD_MODE soundMode);
};
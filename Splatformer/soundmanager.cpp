#include "soundmanager.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include <cstring>

namespace fsys = std::experimental::filesystem;

FMOD::System* SoundManager::audioSystem;
FMOD::Channel* SoundManager::loopChannel;
FMOD::Channel* SoundManager::miscChannel;
std::map<std::string, FMOD::Sound*> SoundManager::sounds;

FMOD_RESULT SoundManager::Initialise() {
	FMOD_RESULT result;
	result = FMOD::System_Create(&audioSystem);

	if (result != FMOD_OK) {
		return result;
	}

	result = audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	
	return result;
}

FMOD_RESULT SoundManager::LoadSounds(std::string _defaultPath) {
	FMOD_RESULT result;

	for (auto& path : fsys::directory_iterator(_defaultPath)) {
		std::string pthStr = path.path().generic_string();

		std::string fileName;
		std::string delimiter = "/";

		FMOD::Sound** newSound = new FMOD::Sound*;

		result = audioSystem->createSound(pthStr.c_str(), FMOD_DEFAULT, 0, newSound);

		size_t pos = 0;
		std::string token;
		while ((pos = pthStr.find(delimiter)) != std::string::npos) {
			token = pthStr.substr(0, pos);
			pthStr.erase(0, pos + delimiter.length());
		}
		fileName = pthStr;
		fileName = fileName.substr(0, fileName.find("."));

		if (result != FMOD_OK) {
			return result;
		}

		sounds.insert(std::make_pair(
			fileName,
			*newSound
		));

		*newSound = nullptr;
		newSound = nullptr;
	}

	return FMOD_OK;
}

FMOD_RESULT SoundManager::LoadSound(std::string _path) {
	FMOD_RESULT result;

	std::string fileName;
	std::string delimiter = "/";

	FMOD::Sound** newSound = new FMOD::Sound*;

	result = audioSystem->createSound(_path.c_str(), FMOD_DEFAULT, 0, newSound);

	size_t pos = 0;
	std::string token;
	while ((pos = _path.find(delimiter)) != std::string::npos) {
		token = _path.substr(0, pos);
		_path.erase(0, pos + delimiter.length());
	}
	fileName = _path;
	fileName = fileName.substr(0, fileName.find("."));

	if (result != FMOD_OK) {
		return result;
	}

	sounds.insert(std::make_pair(
		fileName,
		*newSound
	));

	*newSound = nullptr;
	newSound = nullptr;

	return FMOD_OK;
}


void SoundManager::Update() {
	audioSystem->update();
}

void SoundManager::PlaySound(std::string _sound) {
	FMOD_RESULT result;
	FMOD_MODE sndType;
	sounds[_sound]->getMode(&sndType);

	if ((sndType | FMOD_LOOP_NORMAL) == sndType) {
		result = audioSystem->playSound(sounds[_sound], 0, false, &loopChannel);
	} else {
		result = audioSystem->playSound(sounds[_sound], 0, false, &miscChannel);
	}
}

void SoundManager::PlaySound(std::string _sound, FMOD_MODE _mode) {
	FMOD_RESULT result;
	sounds[_sound]->setMode(_mode);

	if (_mode == FMOD_LOOP_NORMAL) {
		result = audioSystem->playSound(sounds[_sound], 0, false, &loopChannel);
	} else {
		result = audioSystem->playSound(sounds[_sound], 0, false, &miscChannel);
	}
}

void SoundManager::SetSound(std::string _sound, FMOD_MODE _mode) {
	sounds[_sound]->setMode(_mode);
}

void SoundManager::ReleaseSound(std::string _sound) {
	sounds[_sound]->release();
	sounds.erase(_sound);
}

void SoundManager::ReleaseAll() {
	for (auto& sound : sounds) {
		sound.second->release();
	}
}

void SoundManager::Release() {
	for (auto& sound : sounds) {
		sound.second->release();
	}
	audioSystem->release();
}
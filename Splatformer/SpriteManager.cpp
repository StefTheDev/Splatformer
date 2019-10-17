#include "SpriteManager.h"

using namespace std;

SpriteManager* SpriteManager::instance = nullptr;

SpriteManager* SpriteManager::Get() {
	if (instance == nullptr) instance = new SpriteManager();

	return instance;
}

void SpriteManager::AddSprite(string _name, shared_ptr<Sprite> _sprite) {
	sprites.insert(pair<string, shared_ptr<Sprite>>(_name, _sprite));
}

void SpriteManager::RemoveSprite(std::string _name) {
	sprites.erase(_name);
}

std::shared_ptr<Sprite> SpriteManager::GetSprite(std::string _name) {
	return sprites[_name];
}

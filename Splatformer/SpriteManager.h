#pragma once
#include "Utilities.h"
#include "Sprite.h"

class SpriteManager {
public:
	static SpriteManager* Get();

	void AddSprite(std::string name, std::shared_ptr<Sprite> sprite);
	void RemoveSprite(std::string name);
	std::shared_ptr<Sprite> GetSprite(std::string name);

private:
	static SpriteManager* instance;
	std::map<std::string, std::shared_ptr<Sprite>> sprites;
};
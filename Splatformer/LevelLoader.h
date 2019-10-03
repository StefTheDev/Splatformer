#pragma once
#include "Utilities.h"
#include "Entity.h"
#include "RespawnPlatform.h"

namespace LevelLoader {
	bool LoadLevel(std::string levelPath, std::vector<std::unique_ptr<Entity>>& sceneEntities, std::vector<RespawnPlatform*>& sceneRespawns);
}
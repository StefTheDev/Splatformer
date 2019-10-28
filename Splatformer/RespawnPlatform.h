#pragma once
#include "Platform.h"
#include "Player.h"

//Respawn Platforms act as checkpoints and should be activated when a player lands on it.
class RespawnPlatform : public Platform {
public:
	//RespawnPlatform(Vector2 _position, int _respawnNumber);
	RespawnPlatform(TileInfo info, int _respawnNumber);
	~RespawnPlatform() {}

	void Update(Camera* gameCamera, float sceneTime) override;
	virtual void Initialise(b2World* world, std::shared_ptr<Sprite> platformSprite) override;
	void Activate();
	//void Render(SDL_Renderer * _renderer);
	int respawnNumber;
	bool GetActive() { return isActive; }
	void SetActive(bool _b) { isActive = _b; }

	static bool sortAscending(RespawnPlatform* _a, RespawnPlatform* _b) { return _a->respawnNumber < _b->respawnNumber; };

private:
	// used to keep track of which checkpoint this is 
	// the later the checkpoint is in the level the higher the number should be
	// Each respawn should have a unique respawnNumber
	// Will be read in from the level loader
	

	bool isActive = false;
	
	// bool hasBeenLandedOn = false;
};
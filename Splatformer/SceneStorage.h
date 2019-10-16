#pragma once
#include "Utilities.h"

#include "MenuScene.h"
#include "GameScene.h"
#include "Lobby.h"

class StorageBase {
public:
	virtual void LoadScene(SDL_Renderer* gameRenderer) = 0;
	virtual void UnloadScene() = 0;
	virtual void UpdateScene() = 0;
	virtual void RenderScene(SDL_Renderer* gameRenderer) = 0;
	virtual void HandleEvents(SDL_Event sdlEvent) = 0;
	virtual bool Loaded() = 0;
};

template <class SceneType>
class SceneStorage : public StorageBase {
public: 
	virtual void LoadScene(SDL_Renderer* _gameRenderer) override {
		sceneInstance = std::make_unique<SceneType>();
		sceneInstance->LoadScene(_gameRenderer);
	}

	virtual void UnloadScene() override {
		sceneInstance->UnloadScene();

		sceneInstance.reset();
	}

	virtual void UpdateScene() override {
		sceneInstance->UpdateScene();
	}

	virtual void RenderScene(SDL_Renderer* _gameRenderer) override {
		sceneInstance->RenderScene(_gameRenderer);
	}

	virtual void HandleEvents(SDL_Event _sdlEvent) override {
		sceneInstance->HandleEvents(_sdlEvent);
	}

	virtual bool Loaded() override {
		return sceneInstance != nullptr;
	}

private:
	std::unique_ptr<Scene> sceneInstance = nullptr;
};

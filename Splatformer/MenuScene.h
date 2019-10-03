#include "scene.h"
#include "player.h"

//UI Enitities
#include "UIButton.h"
#include "UIText.h"

#include "GameManager.h"

class MenuScene : public Scene {
public:
	MenuScene();

	void Update() override;
	void Render(SDL_Renderer* gameRenderer) override;

private:
	void Load(SDL_Renderer* gameRenderer) override;
	void Unload() override;

	std::unique_ptr<b2World> world;
};
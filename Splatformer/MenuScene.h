#include "scene.h"
#include "player.h"

//UI Enitities
#include "UIButton.h"
#include "UIText.h"

#include "GameManager.h"

class MenuScene : public Scene {
public:
	MenuScene();
	virtual ~MenuScene() override;

	void Update() override;
	void Render(SDL_Renderer* gameRenderer) override;

private:
	void Load(SDL_Renderer* gameRenderer) override;
	void Unload() override;
};
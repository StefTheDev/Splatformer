#include "scene.h"
#include "player.h"

//UI Enitities
#include "UIButton.h"
#include "UIText.h"

#include "GameManager.h"

class InstructionScene: public Scene {
public:
	InstructionScene();
	virtual ~InstructionScene() override;

	void Update() override;
	void Render(SDL_Renderer* gameRenderer) override;

private:
	void Load(SDL_Renderer* gameRenderer) override;
	void Unload() override;
	void ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) override;

	std::unique_ptr<Sprite> controllerInput;
	std::unique_ptr<Sprite> items;
};
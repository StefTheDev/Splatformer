#include "InstructionScene.h"


InstructionScene::InstructionScene()
{

}

InstructionScene::~InstructionScene() {
}

void InstructionScene::Update()
{

}

void InstructionScene::Render(SDL_Renderer* gameRenderer)
{
	controllerInput->Draw(gameRenderer, Vector2(300, 400), Vector2(684, 315));
	items->Draw(gameRenderer, Vector2(1100, 380), Vector2(373, 315));
}

void InstructionScene::Load(SDL_Renderer* _gameRenderer)
{

	Input::GetInstance()->inGame = false;


	std::unique_ptr<UIText> header = std::make_unique<UIText>();

	header->LoadSprite(nullptr);
	header->Initialise(Vector2(0.0f, -320.0f), "INSTRUCTIONS", 128, SDL_Color{ 0, 255, 255 }, _gameRenderer);

	objects.push_back(std::move(header));


	controllerInput = std::make_unique<Sprite>("Resources/Sprites/ControllerInput.png", _gameRenderer, false);
	controllerInput->SetSource(Vector2(2500, 1080));

	items = std::make_unique<Sprite>("Resources/Sprites/Items.png", _gameRenderer, false);
	items->SetSource(Vector2(2500, 1080));


	std::unique_ptr<UIText> back = std::make_unique<UIText>();

	back->LoadSprite(nullptr);
	back->Initialise(Vector2(0.0f, 300.0f), "(B) Menu", 32, SDL_Color{ 255, 255, 255 }, _gameRenderer);

	objects.push_back(std::move(back));
}



void InstructionScene::Unload()
{

}


void InstructionScene::ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) {
	if (_button == SDL_CONTROLLER_BUTTON_B) {
		GameManager::GetInstance()->Switch(MENU);
	}
}
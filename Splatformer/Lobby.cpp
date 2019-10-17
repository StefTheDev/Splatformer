#include "Lobby.h"
#include "GameManager.h"

Lobby::Lobby() {

}

Lobby::~Lobby() {
	std::cout << "Lobby Destroyed\n";

	players.clear();
}

void Lobby::Update() {
	controllersAtStartOfGame = Input::GetInstance()->GetNumGamepads();

	static_cast<UIText*>(objects[0].get())->SetText("Players: " + std::to_string(Input::GetInstance()->GetNumGamepads()));
}

void Lobby::Render(SDL_Renderer* gameRenderer) {

}

void Lobby::ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) {
	if (_button == SDL_CONTROLLER_BUTTON_A) {
		GameManager::GetInstance()->Switch(INGAME);
	} else if (_button == SDL_CONTROLLER_BUTTON_B) {
		//Go to MenuScene
		GameManager::GetInstance()->Switch(MENU);
	}
}

void Lobby::Load(SDL_Renderer* _gameRenderer) 
{
	std::unique_ptr<UIText> label = std::make_unique<UIText>();

	label->LoadSprite(nullptr);
	label->Initialise(Vector2(0.0f, 0.0f), "Players: 0", 64, SDL_Color{ 255, 255, 255 }, _gameRenderer);

	objects.push_back(std::move(label));

	label = std::make_unique<UIText>();

	label->LoadSprite(nullptr);
	label->Initialise(Vector2(100.0f, 300.0f), "(B) Back", 32, SDL_Color{ 255, 0, 0}, _gameRenderer);

	objects.push_back(std::move(label));

	label = std::make_unique<UIText>();

	label->LoadSprite(nullptr);
	label->Initialise(Vector2(-100.0f, 300.0f), "(A) Start", 32, SDL_Color{ 0, 255, 0 }, _gameRenderer);

	objects.push_back(std::move(label));
}

void Lobby::Unload() {

}

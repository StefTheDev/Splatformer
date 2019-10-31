#include "Lobby.h"
#include "GameManager.h"
#include <stdlib.h>
#include <time.h> 

unsigned int maxLevels = 3;

std::string levelTitles[] = {
	"Entry",
	"Drop Down",
	"Flicker Stance",
};

Lobby::Lobby() {

}

Lobby::~Lobby() {

	players.clear();
}

void Lobby::Update() {
	controllersAtStartOfGame = Input::GetInstance()->GetNumGamepads();

	static_cast<UIText*>(objects[0].get())->SetText("Players: " + std::to_string(Input::GetInstance()->GetNumGamepads()));
	static_cast<UIText*>(objects[4].get())->SetText("< " + levelTitles[SELECTED_LEVEL] + " >");
}

void Lobby::Render(SDL_Renderer* gameRenderer) {

}

void Lobby::ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) {
	if (_button == SDL_CONTROLLER_BUTTON_A && controllersAtStartOfGame > 1) {
		GameManager::GetInstance()->Switch(INGAME);

	} else if (_button == SDL_CONTROLLER_BUTTON_B) {
		//Go to MenuScene
		GameManager::GetInstance()->Switch(MENU);

	} else if (_button == SDL_CONTROLLER_BUTTON_Y) {
		//Select a random level
		SELECTED_LEVEL = rand() % maxLevels;

		//Start the game
		GameManager::GetInstance()->Switch(INGAME);

	} else if (_button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
		//Level select -1
		if (SELECTED_LEVEL == 0) {
			SELECTED_LEVEL = maxLevels - 1;
		} else {
			SELECTED_LEVEL = (SELECTED_LEVEL - 1) % maxLevels;
		}

	} else if (_button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
		//Level select +1
		SELECTED_LEVEL = (SELECTED_LEVEL + 1) % maxLevels;
	}
}

void Lobby::Load(SDL_Renderer* _gameRenderer) 
{
	srand(time(NULL));

	Input::GetInstance()->inGame = false;


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

	label = std::make_unique<UIText>();

	label->LoadSprite(nullptr);
	label->Initialise(Vector2(0.0f, 250.0f), "(Y) Random Level", 32, SDL_Color{ 245, 182, 66 }, _gameRenderer);

	objects.push_back(std::move(label));

	label = std::make_unique<UIText>();

	label->LoadSprite(nullptr);
	label->Initialise(Vector2(0.0f, 200.0f), "< " + levelTitles[SELECTED_LEVEL] + " >", 32, SDL_Color{ 200, 200, 200 }, _gameRenderer);

	objects.push_back(std::move(label));
}

void Lobby::Unload() {

}

#include "WinScene.h"
#include "GameManager.h"
#include "SpriteManager.h"

std::string spriteNames[] = {
	"AppleSprite",
	"BananaSprite",
	"CarrotSprite",
	"OnionSprite"
};

float spriteXOffset = -40.0f;
int fontSize = 32;


WinScene::WinScene()
{

}

WinScene::~WinScene()
{
}

void WinScene::Update()
{

}

void WinScene::Render(SDL_Renderer* _gameRenderer){
	std::vector<ScoreData> tempScoreData = GameManager::GetInstance()->GetScoreData();

	

	for (int i = 0; i < tempScoreData.size(); i++) {
		SpriteManager::Get()->GetSprite(spriteNames[i])->Draw(
			_gameRenderer,
			Vector2(WINDOW_WIDTH * 0.5f - (PLAYER_WIDTH * 0.5f) + spriteXOffset, (WINDOW_HEIGHT * 0.5f) + (i * 64.0f) - (PLAYER_WIDTH * 0.5f)),
			Vector2(PLAYER_WIDTH, PLAYER_HEIGHT)
		);
	}
		
}

Uint32 timerCallback(Uint32 interval, void* param) {

	WinScene* thisScene = static_cast<WinScene*>(param);

	thisScene->GetObjects().push_back(std::move(thisScene->play));

	static_cast<UIButton*>(thisScene->GetObjects().back().get())->SetHover(true);

	return 0;
}

void WinScene::Load(SDL_Renderer* gameRenderer)
{
	std::unique_ptr<UIText> header = std::make_unique<UIText>();

	header->LoadSprite(nullptr);
	header->Initialise(Vector2(0.0f, -320.0f), "LEVEL COMPLETE!", 128, SDL_Color{ 0, 255, 255 }, gameRenderer);

	objects.push_back(std::move(header));

	std::vector<ScoreData> tempScoreData = GameManager::GetInstance()->GetScoreData();

	ScoreData highestScorer{};

	int highscorers = 1;
	for (int i = 0; i < tempScoreData.size(); i++)
	{
		if (i == 0) {
			highestScorer = tempScoreData[0];
		}
		else
		{
			if (highestScorer.score == tempScoreData[i].score) highscorers += 1;
			if (highestScorer.score < tempScoreData[i].score) highestScorer = tempScoreData[i];
		}
	}
	
	for (int i = 0; i < tempScoreData.size(); i++) {
		ScoreData score = tempScoreData[i];
		
		std::unique_ptr<UIText> scorer = std::make_unique<UIText>();
		scorer->LoadSprite(nullptr);



		if (score.score == highestScorer.score)
		{
			if (highscorers > 1) {
				std::string text = ": " + std::to_string(tempScoreData[i].score) + " TIED!";
				scorer->Initialise(Vector2(), text.c_str(), fontSize, SDL_Color{ 255, 255, 0 }, gameRenderer);
				Vector2 textPos = Vector2(static_cast<float>(scorer->GetDimensions().x * 0.5f), i * 64.0f);
				scorer->SetPosition(textPos);
			}
			else {
				std::string text = ": " + std::to_string(tempScoreData[i].score) + " WINNER!";
				scorer->Initialise(Vector2(), text.c_str(), fontSize, SDL_Color{ 0, 255, 0 }, gameRenderer);
				Vector2 textPos = Vector2(static_cast<float>(scorer->GetDimensions().x * 0.5f), i * 64.0f);
				scorer->SetPosition(textPos);
			}
		}
		else
		{
			std::string text = ": " + std::to_string(tempScoreData[i].score) + "";
			scorer->Initialise(Vector2(), text.c_str(), fontSize, SDL_Color{ 255, 255, 255 }, gameRenderer);
			Vector2 textPos = Vector2(static_cast<float>(scorer->GetDimensions().x * 0.5f), i * 64.0f);
			scorer->SetPosition(textPos);
		}

		objects.push_back(std::move(scorer));
	}

	play = std::make_unique<UIButton>();
	play->LoadSprite(nullptr);
	play->Initialise(Vector2(0.0f, 300.0f), "RETURN TO MENU", 64, gameRenderer, [this] {
		GameManager::GetInstance()->Switch(MENU);
	});

	SoundManager::PlaySound("Victory", FMOD_DEFAULT);

	waitTimer = SDL_AddTimer(5000, timerCallback, this);
}

void WinScene::Unload()
{
	GameManager::GetInstance()->Clear();
}

void WinScene::ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) {
	if (_button == SDL_CONTROLLER_BUTTON_B) {
		GameManager::GetInstance()->Switch(MENU);
	}
}

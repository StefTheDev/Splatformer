#include "WinScene.h"
#include "GameManager.h"

WinScene::WinScene()
{

}

WinScene::~WinScene()
{
}

void WinScene::Update()
{

}

void WinScene::Render(SDL_Renderer* _gameRenderer)
{
}

void WinScene::Load(SDL_Renderer* gameRenderer)
{
	std::unique_ptr<UIText> header = std::make_unique<UIText>();

	header->LoadSprite(nullptr);
	header->Initialise(Vector2(0.0f, -320.0f), "GAME OVER!", 128, SDL_Color{ 0, 255, 255 }, gameRenderer);

	objects.push_back(std::move(header));

	std::vector<ScoreData> tempScoreData = GameManager::GetInstance()->GetScoreData();

	ScoreData highestScorer;

	for (int i = 0; i < tempScoreData.size(); i++)
	{
		if (i == 0) {
			highestScorer = tempScoreData[0];
		}
		else
		{
			if (highestScorer.score < tempScoreData[i].score) highestScorer = tempScoreData[i];
		}
	}
	
	for (int i = 0; i < tempScoreData.size(); i++) {
		ScoreData score = tempScoreData[i];
		
		std::unique_ptr<UIText> scorer = std::make_unique<UIText>();
		scorer->LoadSprite(nullptr);

		if (score.index == highestScorer.index)
		{
			std::string text = "Player " + std::to_string(i + 1) + ": " + std::to_string(tempScoreData[i].score) + " WINNER!";
			scorer->Initialise(Vector2(0.0f, i * 64), text.c_str(), 32, SDL_Color{ 255, 0, 255 }, gameRenderer);
		}
		else
		{
			std::string text = "Player " + std::to_string(i + 1) + ": " + std::to_string(tempScoreData[i].score) + "";
			scorer->Initialise(Vector2(0.0f, i * 64), text.c_str(), 32, SDL_Color{ 255, 255, 255 }, gameRenderer);
		}

		objects.push_back(std::move(scorer));
	}


	std::unique_ptr<UIButton> play = std::make_unique<UIButton>();
	play->LoadSprite(nullptr);
	play->Initialise(Vector2(0.0f, 300.0f), "MAIN MENU", 64, gameRenderer, [this]
		{
			GameManager::GetInstance()->Switch(MENU);
		});

	objects.push_back(std::move(play));

	SoundManager::PlaySound("Victory", FMOD_DEFAULT);
}

void WinScene::Unload()
{
	GameManager::GetInstance()->Clear();
}

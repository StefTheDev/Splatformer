#include "WinScene.h"
#include "GameManager.h"

WinScene::WinScene()
{

}

WinScene::~WinScene()
{
	std::cout << "Win Scene Destroyed\n";
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
	header->Initialise(Vector2(0.0f, -320.0f), "WINNER!", 128, SDL_Color{ 0, 255, 255 }, gameRenderer);

	objects.push_back(std::move(header));

	std::vector<ScoreData> tempScoreData = GameManager::GetInstance()->GetScoreData();

	ScoreData highestScorer;

	for (int i = 0; i < tempScoreData.size(); i++)
	{
		if (i == 0) 
		{
			highestScorer = tempScoreData[i];
		}
		else
		{
			if (highestScorer.score < tempScoreData[i].score) highestScorer = tempScoreData[i];
		}

		std::unique_ptr<UIText> scorer = std::make_unique<UIText>();
		std::string text = std::to_string(i + 1) + ". " + std::to_string(tempScoreData[i].score);

		scorer->LoadSprite(nullptr);
		scorer->Initialise(Vector2(0.0f, i * -64 + 128), text.c_str(), 128, SDL_Color{ 0, 255, 255 }, gameRenderer);

		objects.push_back(std::move(scorer));
	}

	std::unique_ptr<UIText> highscorer = std::make_unique<UIText>();
	std::string text = std::to_string(highestScorer.index + 1) + ". " + std::to_string(highestScorer.score);

	highscorer->LoadSprite(nullptr);
	highscorer->Initialise(Vector2(0.0f, 128), text.c_str(), 128, SDL_Color{ 0, 255, 255 }, gameRenderer);

	objects.push_back(std::move(highscorer));


	std::unique_ptr<UIButton> play = std::make_unique<UIButton>();
	play->LoadSprite(nullptr);
	play->Initialise(Vector2(0.0f, 200.0f), "MAIN MENU", 64, gameRenderer, [this]
		{
			GameManager::GetInstance()->Switch(MENU);
		});

	objects.push_back(std::move(play));

	std::cout << "Win Scene Loaded with " << objects.size() << " objects";
}

void WinScene::Unload()
{
}

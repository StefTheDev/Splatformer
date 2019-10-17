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

	std::unique_ptr<UIText> winner = std::make_unique<UIText>();
	std::string text = "Player " + std::to_string(GameManager::GetInstance()->GetWinner());

	winner->LoadSprite(nullptr);
	winner->Initialise(Vector2(0.0f, 0.0f), text.c_str(), 128, SDL_Color{ 0, 255, 255 }, gameRenderer);

	objects.push_back(std::move(winner));

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

#include "MenuScene.h"

MenuScene::MenuScene()
{
	
}

MenuScene::~MenuScene() {
	std::cout << "Menu Destroyed\n";
}

void MenuScene::Update()
{

}

void MenuScene::Render(SDL_Renderer * gameRenderer)
{

}

void MenuScene::Load(SDL_Renderer* _gameRenderer) 
{
	std::unique_ptr<UIText> header = std::make_unique<UIText>();

	header->LoadSprite(nullptr);
	header->Initialise(Vector2(0.0f, -320.0f), "SPLATFORMER", 128, SDL_Color{ 0, 255, 255}, _gameRenderer);

	objects.push_back(std::move(header));

	std::unique_ptr<UIButton> play = std::make_unique<UIButton>();
	play->LoadSprite(nullptr);
	play->Initialise(Vector2(0.0f, -80.0f), "PLAY", 64, _gameRenderer, [this] 
	{
		GameManager::GetInstance()->Switch(LOBBY);
	});

	objects.push_back(std::move(play));

	std::unique_ptr<UIButton> credits = std::make_unique<UIButton>();
	credits->LoadSprite(nullptr);
	credits->Initialise(Vector2(0.0f, 0.0f), "CREDITS", 64, _gameRenderer, [this]
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Credits", "Made by Damon, Jason, Chloe, Stef.", NULL);
	});

	objects.push_back(std::move(credits));

	std::unique_ptr<UIButton> exit = std::make_unique<UIButton>();
	exit->LoadSprite(nullptr);
	exit->Initialise(Vector2(0.0f, 80.0f), "QUIT", 64, _gameRenderer, [this]
	{
		SDL_Quit();
		std::exit(0);
	});

	objects.push_back(std::move(exit));

	// TODO: WHY THIS NO WORK?
	SoundManager::PlaySound("Jump", FMOD_LOOP_NORMAL);
}

void MenuScene::Unload()
{
	//SoundManager::loopChannel->stop();
}

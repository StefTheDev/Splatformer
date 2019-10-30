#include "MenuScene.h"

MenuScene::MenuScene()
{
	//SoundManager::PlaySound("game bgm", FMOD_LOOP_NORMAL);

}

MenuScene::~MenuScene() {
}

void MenuScene::Update()
{

}

void MenuScene::Render(SDL_Renderer * gameRenderer)
{

}

void MenuScene::Load(SDL_Renderer* _gameRenderer) 
{

	Input::GetInstance()->inGame = false;
	//SoundManager::loopChannel
	std::cout << SoundManager::PlaySound("menu bgm", FMOD_LOOP_NORMAL) << std::endl;
	//SoundManager::LoadSounds("Resources\Sounds");
	//SoundManager::PlaySound("Horn");


	std::unique_ptr<UIText> header = std::make_unique<UIText>();

	header->LoadSprite(nullptr);
	header->Initialise(Vector2(0.0f, -320.0f), "SPLATFORMER", 128, SDL_Color{ 0, 255, 255}, _gameRenderer);

	objects.push_back(std::move(header));

	std::unique_ptr<UIButton> play = std::make_unique<UIButton>();
	play->LoadSprite(nullptr);
	play->Initialise(Vector2(0.0f, -120.0f), "PLAY", 64, _gameRenderer, [this] 
	{
		GameManager::GetInstance()->Switch(LOBBY);
	});

	std::unique_ptr<UIButton> instruction = std::make_unique<UIButton>();
	instruction->LoadSprite(nullptr);
	instruction->Initialise(Vector2(0.0f, -40.0f), "INSTRUCTIONS", 64, _gameRenderer, [this]
		{
			GameManager::GetInstance()->Switch(INSTRUCTION);
		});

	std::unique_ptr<UIButton> credits = std::make_unique<UIButton>();
	credits->LoadSprite(nullptr);
	credits->Initialise(Vector2(0.0f, 40.0f), "CREDITS", 64, _gameRenderer, [this]
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Credits", "Made by Damon, Jason, Chloe, Stef.", NULL);
	});

	std::unique_ptr<UIButton> exit = std::make_unique<UIButton>();
	exit->LoadSprite(nullptr);
	exit->Initialise(Vector2(0.0f, 120.0f), "QUIT", 64, _gameRenderer, [this]
	{
		SDL_Quit();
		std::exit(0);
	});
	
	play->SetHover(true);
	play->SetUp(exit.get());
	play->SetDown(instruction.get());

	instruction->SetUp(play.get());
	instruction->SetDown(credits.get());

	credits->SetUp(instruction.get());
	credits->SetDown(exit.get());

	exit->SetUp(credits.get());
	exit->SetDown(play.get());

	objects.push_back(std::move(play));
	objects.push_back(std::move(instruction));
	objects.push_back(std::move(credits));
	objects.push_back(std::move(exit));
}

void MenuScene::Unload()
{
	std::cout << SoundManager::loopChannel->stop() << std::endl;
}

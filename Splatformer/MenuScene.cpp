#include "MenuScene.h"



MenuScene::MenuScene() : Scene()
{
}


MenuScene::~MenuScene()
{

}

void MenuScene::RenderScene(SDL_Renderer * renderer)
{
	for (auto& textLabel : textLabels) {
		textLabel->Render(renderer);
	}

	Scene::RenderScene(renderer);
}

void MenuScene::LoadScene(SDL_Renderer * renderer)
{
	TTF_Font * font = TTF_OpenFont("Resources/Fonts/Helvetica.ttf", 250);

	textLabels.push_back(std::make_unique<TextLabel>("Play", font, SDL_Color{ 255, 0, 0 }, SDL_Rect { 0, 0, 400, 100 }));
	textLabels.push_back(std::make_unique<TextLabel>("Credits", font, SDL_Color{ 255, 255, 0 }, SDL_Rect{ 0, 0, 400, 100 }));
	textLabels.push_back(std::make_unique<TextLabel>("Quit", font, SDL_Color{ 255, 255, 0 }, SDL_Rect{ 0, 0, 400, 100 }));

	for (int i = 0; i < textLabels.size(); i++) {
		textLabels[i]->SetPosition(Vector2{ static_cast<float>(0), static_cast<float>(i * 50)});
	}

	Scene::LoadScene(renderer);
}

void MenuScene::UnLoadScene()
{
	textLabels.clear();
	Scene::UnloadScene();
}
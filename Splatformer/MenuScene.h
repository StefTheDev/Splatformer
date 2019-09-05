#pragma once

#include "scene.h"
#include "TextLabel.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();

	void RenderScene(SDL_Renderer * renderer);

	void LoadScene(SDL_Renderer * renderer);
	void UnLoadScene();

private:

	//Current index of selected menu item;
	int index = 0;

	std::vector<std::unique_ptr<TextLabel>> textLabels;
};


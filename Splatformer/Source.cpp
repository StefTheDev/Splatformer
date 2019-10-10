#include "GameManager.h"
//#include "MenuScene.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char* argv[]) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameManager* gameManager = GameManager::GetInstance();
	if (!gameManager->Initialise("Splatformer")) return 0;

	Uint32 startFrame, timeFrame;

	while (gameManager->GetState() != EXIT)
	{

		startFrame = SDL_GetTicks();

		gameManager->HandleEvents();
		gameManager->Process();
		gameManager->Render();

		timeFrame = SDL_GetTicks() - startFrame;

		if (FRAME_DELAY > timeFrame) SDL_Delay(FRAME_DELAY - timeFrame);

		gameManager->CheckSwitch();
	}

	gameManager->Clean();

	delete gameManager;
	return 0;
}
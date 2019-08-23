#include "GameManager.h"


std::unique_ptr<GameManager> gameManager;

int main(int argc, char* argv[]) {
	gameManager = std::make_unique<GameManager>();
	gameManager->Initialise("Splatformer");

	Uint32 startFrame, timeFrame;

	while (gameManager->GetState() != EXIT)
	{
		startFrame = SDL_GetTicks();

		gameManager->HandleEvents();
		gameManager->Process();
		gameManager->Render();

		timeFrame = SDL_GetTicks() - startFrame;

		if (FRAME_DELAY > timeFrame) SDL_Delay(FRAME_DELAY - timeFrame);
	}

	gameManager->Clean();
	return 0;
}
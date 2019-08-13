#include "GameManager.h"

std::unique_ptr<GameManager> gameManager;

int main(int argc, char* args[]) {
	gameManager = std::make_unique<GameManager>("Filler");
	
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
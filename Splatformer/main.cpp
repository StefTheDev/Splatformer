#include "GameManager.h"

std::unique_ptr<GameManager> gameManager;

int main(int argc, char* args[]) {

	gameManager = std::make_unique<GameManager>();
	while (gameManager->GetState() != EXIT)
	{
		gameManager->Process();
		gameManager->Render();
	}

	gameManager->Clean();
	return 0;
}
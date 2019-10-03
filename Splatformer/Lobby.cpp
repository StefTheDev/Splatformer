#include "Lobby.h"

Lobby::Lobby() {
}

void Lobby::Update() {
	controllersAtStartOfGame = Input::GetInstance()->GetNumGamepads();
	std::cout << "Controllers: " << controllersAtStartOfGame << std::endl;
}

void Lobby::Render(SDL_Renderer* gameRenderer) {
}

void Lobby::Load(SDL_Renderer* gameRenderer) {
}

void Lobby::Unload() {
}

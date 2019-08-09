#include "scene.h"
#include <locale>

InputState thing[255];
InputState Scene::KeyState[255];
InputState Scene::SpecialKeyState[128];

//std::chrono::time_point<std::chrono::system_clock> Scene::currTime;
//std::chrono::duration<double> Scene::deltaTimeDuration;
float Scene::deltaTime;

//glm::vec2 Scene::MousePos;

void Scene::UpdateGlobal() {
	//deltaTimeDuration = std::chrono::system_clock::now() - currTime;
	//currTime = std::chrono::system_clock::now();
	//deltaTime = deltaTimeDuration.count();
}

void Scene::UpdateDowns(unsigned char _key) {
	std::locale loc;
	KeyState[std::tolower(_key, loc)] = DOWN;
}

void Scene::UpdateUps(unsigned char _key) {
	std::locale loc;
	KeyState[std::tolower(_key, loc)] = UP;
}

void Scene::UpdateSpecialDowns(int _key) {
	SpecialKeyState[_key] = DOWN;
}

void Scene::UpdateSpecialUps(int _key) {
	SpecialKeyState[_key] = DOWN;
}

void Scene::UpdateMousePos(int _x, int _y) {
	//MousePos = glm::vec2(static_cast<float>(_x), static_cast<float>(_y));
}

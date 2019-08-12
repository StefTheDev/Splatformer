#pragma once
//#include "helpers.h"

enum InputState {
	UP = 0,
	DOWN,
	UP_FIRST,
	DOWN_FIRST
};

class Scene {
public:
	virtual void Initialise() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void KeyUp(unsigned char key) = 0;
	virtual void KeyDown(unsigned char key) = 0;
	virtual void SpecialKeyUp(int key) = 0;
	virtual void SpecialKeyDown(int key) = 0;
	virtual void MouseClick(int button, int state) = 0;
	virtual void MouseMove() = 0;
	virtual void MouseMoveActive() = 0;

	static void UpdateGlobal();
	static void UpdateDowns(unsigned char key);
	static void UpdateUps(unsigned char key);
	static void UpdateSpecialDowns(int key);
	static void UpdateSpecialUps(int key);
	static void UpdateMousePos(int x, int y);

protected:
	static InputState KeyState[255];
	static InputState SpecialKeyState[128];
	//static glm::vec2 MousePos;

	//static std::chrono::time_point<std::chrono::system_clock> currTime;
	//static std::chrono::duration<double> deltaTimeDuration;
	static float deltaTime;
};
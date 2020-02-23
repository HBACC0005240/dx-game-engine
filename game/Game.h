#pragma once
#include "Graphics.h"

class Game {
private:
	GameWind& wnd;
	Graphics gfx;
public:
	Game(GameWind& wmd);
	~Game();
	void Init();
	void Run();
	static bool KeyBoard(char key, BUTTON_KEY bk);
	static bool keyMouse(int x, int y, BUTTON_KEY bk);
};
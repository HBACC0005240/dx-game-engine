#pragma once
#include "Graphics.h"

class Game {
private:
	GameWind& wnd;
	Graphics gfx;
public:
	Game(GameWind wmd);
	~Game();

	void Run();
};
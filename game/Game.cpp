#include "GameWind.h"
#include "Graphics.h"
#include "Game.h"

Game::Game(GameWind wnd):wnd(wnd),gfx(wnd)
{
}

Game::~Game()
{
}

void Game::Run()
{
	gfx.Render();
	wnd.wcRect;
}

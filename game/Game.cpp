#include "GameWind.h"
#include "Graphics.h"
#include "Game.h"

Game::Game(GameWind& wnd):wnd(wnd),gfx(wnd)
{
	OutputDebugString(L"Game()����\n");
}

Game::~Game()
{
	OutputDebugString(L"~Game()����\n");
}

void Game::Run()
{
	gfx.Render();
}

#include "GameWind.h"
#include "Graphics.h"
#include "Game.h"

Game::Game(GameWind& wnd):wnd(wnd),gfx(wnd)
{
	OutputDebugString(L"Game()¹¹Ôì\n");
}

Game::~Game()
{
	OutputDebugString(L"~Game()Îö¹¹\n");
}

void Game::Run()
{
	gfx.Render();
}

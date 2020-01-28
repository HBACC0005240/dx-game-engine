#include "GameWind.h"
#include "Graphics.h"
#include "Game.h"
#include <vector>

Game::Game(GameWind& wnd):wnd(wnd),gfx(wnd)
{
	OutputDebugString(L"Game()构造\n");
}

Game::~Game()
{
	OutputDebugString(L"~Game()析构\n");
}

void Game::Init()
{
	//初始化顶点
	gfx.InitVertex();
}


void Game::Run()
{
	GetClientRect(wnd.mHwnd, &wnd.clientRect);
	GTime::run();
	gfx.Render();
	GTime::over();
}

bool Game::KeyDown(int key)
{
	wchar_t buf[50];
	swprintf_s(buf, TEXT("按键：%c"), key);
	OutputDebugString(buf);
	return false;
}

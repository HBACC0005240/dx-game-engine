#include "GameWind.h"
#include "Graphics.h"
#include "Game.h"
#include <vector>

Game::Game(GameWind& wnd):wnd(wnd),gfx(wnd)
{
	OutputDebugString(L"Game()����\n");
}

Game::~Game()
{
	OutputDebugString(L"~Game()����\n");
}

void Game::Init()
{
	//��ʼ������
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
	swprintf_s(buf, TEXT("������%c"), key);
	OutputDebugString(buf);
	return false;
}

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

bool Game::keyMouse(int x, int y, BUTTON_KEY bk)
{
	wchar_t buf[50] = { 0 };
	switch (bk)
	{
	case L_BUTTON_DOWN:
		swprintf_s(buf, TEXT("������£�%d,%d\n"), x, y);
		break;
	case L_BUTTON_UP:
		swprintf_s(buf, TEXT("�������%d,%d\n"), x, y);
		break;
	case R_BUTTON_DOWN:
		swprintf_s(buf, TEXT("�Ҽ����£�%d,%d\n"), x, y);
		break;
	case R_BUTTON_UP:
		swprintf_s(buf, TEXT("�Ҽ�����%d,%d\n"), x, y);
		break;
	default:
		break;
	}
	OutputDebugString(buf);
	return false;
}

bool Game::KeyBoard(char key, BUTTON_KEY bk)
{
	wchar_t buf[50] = { 0 };
	switch (bk)
	{
	case KB_DOWN:
		swprintf_s(buf, TEXT("���£�%c\n"), key);
		break;
	case KB_UP:
		swprintf_s(buf, TEXT("����%c\n"), key);
		break;
	default:
		break;
	}
	OutputDebugString(buf);
	return false;
}

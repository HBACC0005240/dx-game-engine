#include "DrawGText.h"

DrawGText::DrawGText(LPD3DXFONT d3dFont)
{
	OutputDebugString(L"DrawGText()¹¹Ôì\n");
	p_d3dFont = d3dFont;
}

DrawGText::~DrawGText()
{
	OutputDebugString(L"~DrawGText()Îö¹¹\n");
}

void DrawGText::DrawFps(float fps, RECT* rect,DWORD color)
{
	wchar_t str[20] = { 0 };
	swprintf_s(str, 20, TEXT("FPS:%0.2f"), fps);
	p_d3dFont->DrawText(NULL, str, lstrlen(str), rect, DT_TOP | DT_LEFT, color);
}

void DrawGText::Draw(const wchar_t* text, long x, long y, long w, long h, DWORD color)
{
	//RECT rect = { 0,0,800,600 };
	RECT rect = { x,y,w,h };
	p_d3dFont->DrawText(NULL, text, lstrlen(text), &rect, DT_TOP | DT_LEFT, color);
}

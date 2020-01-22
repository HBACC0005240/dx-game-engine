#pragma once
#include "Core.h"

class DrawGText {
private:
	LPD3DXFONT p_d3dFont;
public:
	DrawGText(LPD3DXFONT d3dFont);
	~DrawGText();

	void Draw(const wchar_t* text, long x, long y, long w, long h, DWORD color);
	void DrawFps(float fps, RECT* rect, DWORD color);
};
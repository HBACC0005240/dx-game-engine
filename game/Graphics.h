#pragma once
#include "Core.h"
#include "GameWind.h"
#include "Camera.h"
#include "DrawPoint.h"
#include "DrawLine.h"
#include "DrawGText.h"
#include "DrawTriangle.h"
#include "GWzlData.h"
#include "GPlayer.h"
#include "GMap.h"

class Graphics {
private:
	GameWind& wnd; //��Ϸ����
	LPDIRECT3D9 m_d3d9;//d3d����
	LPD3DXFONT m_d3dFont = nullptr;//���ֶ���
public:
	Camera* g_camera;//��Ӱ��
	DrawPoint* g_point;//����
	DrawLine* g_line;//����
	DrawGText* g_text;//���ֶ���
	DrawTriangle* g_triangle;//�����ζ���
	DrawTriangle* g_3dtriangle;//�����ζ���
	GWzlData* pWzlHum;
	GPlayer* g_player;
	GMap* g_map;
public:
	LPDIRECT3DDEVICE9 m_d3dDevice;//�豸����
	Graphics(GameWind &wnd);
	~Graphics();
	HRESULT InitD3D();
	HRESULT InitVertex();
	void Render();
	float Getfps();
};
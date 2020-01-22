#include "Camera.h"

Camera::Camera(LPDIRECT3DDEVICE9 d3dDevice)
{
	OutputDebugString(L"Camera()构造\n");
	p_d3dDevice = d3dDevice;
}

Camera::~Camera()
{
	OutputDebugString(L"~Camera()析构\n");

}

void Camera::SetMatrices()
{
	static float i = 0;
	D3DXMATRIXA16 matWorld,Ry,Rx;
	if (i >= (2.0f * D3DX_PI))
	{
		i = 0;
	}
	i+=0.05f;
	FLOAT fAngle = i;// *(2.0f * D3DX_PI) / 1000.0f;
	wchar_t buf[50] = { 0 };
	swprintf_s(buf, 50, L"角度:%0.2f \n", fAngle);
	OutputDebugString(buf);
	D3DXMatrixRotationY(&Ry, fAngle);
	D3DXMatrixRotationX(&Rx, fAngle);
	matWorld = Rx * Ry;
	p_d3dDevice->SetTransform(D3DTS_WORLD, &matWorld);


	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	p_d3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	p_d3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

}

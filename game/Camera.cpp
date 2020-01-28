#include "Camera.h"

Camera::Camera(LPDIRECT3DDEVICE9 d3dDevice)
{
	OutputDebugString(TEXT("Camera()构造\n"));
	p_d3dDevice = d3dDevice;
}

Camera::~Camera()
{
	OutputDebugString(TEXT("~Camera()析构\n"));

}

#define DEBUG1
#define DEBUG2
#define DEBUG3
void Camera::SetMatrices(float width,float height)
{
#ifdef DEBUG1
	///----------------------------------------------------------------
	///四大变换之二：取景变换矩阵的设置
	D3DXMATRIX matView;
	D3DXVECTOR3 position(0.0f, 0.0f, -4.0f);//摄像机位置
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);//观察点位置
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//向上的向量
	D3DXMatrixLookAtLH(&matView, &position, &target, &up);
	p_d3dDevice->SetTransform(D3DTS_VIEW, &matView);
#endif // DEBUG

#ifdef DEBUG2

	///----------------------------------------------------------------
	///四大变换之三：投影变换矩阵的设置
	//设置透视投影变换
	D3DXMATRIX proj;
	//透视投影矩阵
	float aspect = (float)(width / height);
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, aspect, 1.0f, 1000.0f);
	p_d3dDevice->SetTransform(D3DTS_PROJECTION, &proj);

	//正交投影矩阵
	//D3DXMatrixOrthoLH(&proj, WINDOW_WIDTH, WINDOW_HEIGHT, 0.1f, 1000.0f);
	p_d3dDevice->SetTransform(D3DTS_PROJECTION, &proj);
#endif // DEBUG

#ifdef DEBUG3
	///----------------------------------------------------------------
	///四大变换之四：视口变换的设置
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = (DWORD)width;//视口的宽度
	vp.Height = (DWORD)height;//视口的高度
	vp.MinZ = 0.0;
	vp.MaxZ = 1.0;
	p_d3dDevice->SetViewport(&vp);
#endif // DEBUG
	/*D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	p_d3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);*/

}

void Camera::SetTransform(float timeDelta)
{
	///----------------------------------------------------------------
///四大变换之一：世界变换矩阵的设置

///绕X旋转矩阵
	D3DXMATRIX Rx, Ry, Rz;
	static float x = 0.0f;
	D3DXMatrixRotationX(&Rx, x);
	x += timeDelta;
	if (x >= 6.28f)
	{
		x = 0.0f;
	}

	///绕Y旋转矩阵
	static float y = 0.0f;
	D3DXMatrixRotationY(&Ry, y);
	y += timeDelta;
	if (y >= 6.28f)
	{
		y = 0.0f;
	}

	///绕Z旋转矩阵
	static float z = 0.0f;
	D3DXMatrixRotationY(&Rz, z);
	z += timeDelta;
	if (z >= 6.28f)
	{
		z = 0.0f;
	}

	///绕X旋转矩阵 * 绕Y旋转矩阵
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);//单位化世界矩阵

	///组合矩阵
	matWorld = Rx * Ry * Rz * matWorld;
	if (::GetAsyncKeyState(0x33) & 0x8000f) {
		p_d3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	}
}

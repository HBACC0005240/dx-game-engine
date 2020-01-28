#include "Camera.h"

Camera::Camera(LPDIRECT3DDEVICE9 d3dDevice)
{
	OutputDebugString(TEXT("Camera()����\n"));
	p_d3dDevice = d3dDevice;
}

Camera::~Camera()
{
	OutputDebugString(TEXT("~Camera()����\n"));

}

#define DEBUG1
#define DEBUG2
#define DEBUG3
void Camera::SetMatrices(float width,float height)
{
#ifdef DEBUG1
	///----------------------------------------------------------------
	///�Ĵ�任֮����ȡ���任���������
	D3DXMATRIX matView;
	D3DXVECTOR3 position(0.0f, 0.0f, -4.0f);//�����λ��
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);//�۲��λ��
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//���ϵ�����
	D3DXMatrixLookAtLH(&matView, &position, &target, &up);
	p_d3dDevice->SetTransform(D3DTS_VIEW, &matView);
#endif // DEBUG

#ifdef DEBUG2

	///----------------------------------------------------------------
	///�Ĵ�任֮����ͶӰ�任���������
	//����͸��ͶӰ�任
	D3DXMATRIX proj;
	//͸��ͶӰ����
	float aspect = (float)(width / height);
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, aspect, 1.0f, 1000.0f);
	p_d3dDevice->SetTransform(D3DTS_PROJECTION, &proj);

	//����ͶӰ����
	//D3DXMatrixOrthoLH(&proj, WINDOW_WIDTH, WINDOW_HEIGHT, 0.1f, 1000.0f);
	p_d3dDevice->SetTransform(D3DTS_PROJECTION, &proj);
#endif // DEBUG

#ifdef DEBUG3
	///----------------------------------------------------------------
	///�Ĵ�任֮�ģ��ӿڱ任������
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = (DWORD)width;//�ӿڵĿ��
	vp.Height = (DWORD)height;//�ӿڵĸ߶�
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
///�Ĵ�任֮һ������任���������

///��X��ת����
	D3DXMATRIX Rx, Ry, Rz;
	static float x = 0.0f;
	D3DXMatrixRotationX(&Rx, x);
	x += timeDelta;
	if (x >= 6.28f)
	{
		x = 0.0f;
	}

	///��Y��ת����
	static float y = 0.0f;
	D3DXMatrixRotationY(&Ry, y);
	y += timeDelta;
	if (y >= 6.28f)
	{
		y = 0.0f;
	}

	///��Z��ת����
	static float z = 0.0f;
	D3DXMatrixRotationY(&Rz, z);
	z += timeDelta;
	if (z >= 6.28f)
	{
		z = 0.0f;
	}

	///��X��ת���� * ��Y��ת����
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);//��λ���������

	///��Ͼ���
	matWorld = Rx * Ry * Rz * matWorld;
	if (::GetAsyncKeyState(0x33) & 0x8000f) {
		p_d3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	}
}

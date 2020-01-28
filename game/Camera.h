#pragma once
#include "Core.h"
class Camera {
public:
	LPDIRECT3DDEVICE9 p_d3dDevice;//�豸����
public:
	Camera(LPDIRECT3DDEVICE9 d3dDevice);
	~Camera();

	//���ñ任
	void SetMatrices(float width, float height);
	//��ת
	void SetTransform(float timeDelta);
};
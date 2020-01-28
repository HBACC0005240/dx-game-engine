#pragma once
#include "Core.h"
class Camera {
public:
	LPDIRECT3DDEVICE9 p_d3dDevice;//设备驱动
public:
	Camera(LPDIRECT3DDEVICE9 d3dDevice);
	~Camera();

	//设置变换
	void SetMatrices(float width, float height);
	//旋转
	void SetTransform(float timeDelta);
};
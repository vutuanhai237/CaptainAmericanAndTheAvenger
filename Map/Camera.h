#pragma once
#include <d3dx9.h>
#include "Framework/GameSetting.h"

#define FAR_LEFT 120
#define FAR_RIGHT 120
#define FAR_TOP 128
#define FAR_BOTTOM 88

class Camera
{
public:
	static Camera* GetInstance();
	void Release();

	void Init(int PixelWidth, int PixelHeight);

	D3DXVECTOR2 World2Render(const D3DXVECTOR2 &Point);
	D3DXVECTOR2 Render2World(const D3DXVECTOR2 &Point);

	void SetCameraPosition(D3DXVECTOR2 Point);
	D3DXVECTOR2 GetCameraPosition();
	D3DXVECTOR2 GetFollowPoint();

	void MoveX(float dx);
	void MoveY(float dy);
private:
	Camera();
	~Camera() {};

	RECT BoxFollow;

	int PixelWidth, PixelHeight;
	D3DXVECTOR2 PointBL;
	D3DXVECTOR2 FollowPoint;
	static Camera* Instance;
};
#pragma once
#include <d3dx9.h>
#include "Framework/GameSetting.h"

#define FAR_LEFT 104
#define FAR_RIGHT 104
#define FAR_TOP 80
#define FAR_BOTTOM 80

class Camera
{
public:
	static Camera* GetInstance();
	void Release();

	void Init(SIZE MapSize);
	void Init(int PixelWidth, int PixelHeight);

	D3DXVECTOR2 World2Render(const D3DXVECTOR2 &Point);
	D3DXVECTOR2 Render2World(const D3DXVECTOR2 &Point);

	void SetCameraPosition(D3DXVECTOR2 Point);
	void SetCameraPosition(FLOAT x, FLOAT y);
	D3DXVECTOR2 GetCameraPosition();
	D3DXVECTOR2 GetFollowPoint();

	void MoveX(float dx);
	void MoveY(float dy);

	RECT GetCameraViewRect();

	void SetCameraFreeze(bool IsFreeze);
private:
	Camera();
	~Camera() {};

	RECT BoxFollow;
	bool IsFreze;

	int PixelWidth, PixelHeight;
	D3DXVECTOR2 PointBL;
	D3DXVECTOR2 FollowPoint;
	static Camera* Instance;
};
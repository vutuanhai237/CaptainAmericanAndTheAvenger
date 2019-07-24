#include "Camera.h"

Camera* Camera::Instance = NULL;

Camera* Camera::GetInstance()
{
	if (!Instance)
		Instance = new Camera();
	return Instance;
}

void Camera::Release()
{
	delete Instance;
}

void Camera::Init(SIZE MapSize)
{
	PixelWidth = MapSize.cx;
	PixelHeight = MapSize.cy;
}

void Camera::Init(int Width, int Height)
{
	PixelWidth = Width;
	PixelHeight = Height;
}

D3DXVECTOR2 Camera::World2Render(const D3DXVECTOR2 &p)
{
	return D3DXVECTOR2(p.x - PointBL.x, PointBL.y + GAME_SCREEN_HEIGHT - p.y);
}

D3DXVECTOR2 Camera::Render2World(const D3DXVECTOR2 &p)
{
	return D3DXVECTOR2(p.x + PointBL.x, PointBL.y + GAME_SCREEN_HEIGHT - p.y);
}

void Camera::SetCameraPosition(D3DXVECTOR2 p)
{
	FollowPoint = p;
	if (IsFreze)
		return;
	D3DXVECTOR2 tmp = World2Render(p);

	if (tmp.x > BoxFollow.right)
		PointBL.x += tmp.x - BoxFollow.right;
	else if (tmp.x < BoxFollow.left)
		PointBL.x -= BoxFollow.left - tmp.x;
	if (tmp.y > BoxFollow.bottom)
		PointBL.y -= tmp.y - BoxFollow.bottom;
	else if (tmp.y < BoxFollow.top)
		PointBL.y += BoxFollow.top - tmp.y;

	if (PointBL.x < 0)
		PointBL.x = 0;
	else if (PointBL.x + GAME_SCREEN_WIDTH > PixelWidth)
		PointBL.x = PixelWidth - GAME_SCREEN_WIDTH;
	if (PointBL.y < 0)
		PointBL.y = 0;
	else if (PointBL.y > PixelHeight - GAME_SCREEN_HEIGHT)
		PointBL.y = PixelHeight - GAME_SCREEN_HEIGHT;
}

void Camera::SetCameraPosition(FLOAT x, FLOAT y)
{
	SetCameraPosition(D3DXVECTOR2(x, y));
}

D3DXVECTOR2 Camera::GetCameraPosition()
{
	return PointBL;
}

D3DXVECTOR2 Camera::GetFollowPoint()
{
	return FollowPoint;
}

void Camera::MoveX(float dx)
{
	SetCameraPosition(D3DXVECTOR2(FollowPoint.x + dx, FollowPoint.y));
}

void Camera::MoveY(float dy)
{
	SetCameraPosition(D3DXVECTOR2(FollowPoint.x, FollowPoint.y - dy));
}

RECT Camera::GetCameraViewRect()
{
	RECT ret;
	ret.bottom = PointBL.y;
	ret.top = ret.bottom + GAME_SCREEN_HEIGHT;
	ret.left = PointBL.x;
	ret.right = ret.left + GAME_SCREEN_WIDTH;
	return ret;
}

void Camera::SetCameraFreeze(bool IsFreeze)
{
	this->IsFreze = IsFreeze;
}

Camera::Camera()
{
	BoxFollow.top = FAR_TOP;
	BoxFollow.bottom = GAME_SCREEN_HEIGHT - FAR_BOTTOM; 
	BoxFollow.left = FAR_LEFT;
	BoxFollow.right = GAME_SCREEN_WIDTH - FAR_RIGHT; 

	PointBL = FollowPoint = D3DXVECTOR2(0, 0);
	IsFreze = 0;
}

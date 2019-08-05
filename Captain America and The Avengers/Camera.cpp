#include "Camera.h"
#include "SceneManager.h"-
#include "Player.h"

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

void Camera::RefreshCamera(D3DXVECTOR2 p)
{
	FollowPoint = p;
	if (IsFreze)
		return;

	PointBL.x = p.x - GAME_SCREEN_WIDTH / 2;
	PointBL.y = p.y - FAR_BOTTOM;

	if (PointBL.x < 0)
		PointBL.x = 0;
	else if (PointBL.x + GAME_SCREEN_WIDTH > PixelWidth)
		PointBL.x = PixelWidth - GAME_SCREEN_WIDTH;
	if (PointBL.y < 0)
		PointBL.y = 0;
	else if (PointBL.y > PixelHeight - GAME_SCREEN_HEIGHT)
		PointBL.y = PixelHeight - GAME_SCREEN_HEIGHT;
}

void Camera::SetCameraPosition(D3DXVECTOR2 p)
{
	FollowPoint = p;
	if (IsFreze)
		return;
	D3DXVECTOR2 tmp = World2Render(p);

	if (tmp.x >= BoxFollow.right)
		PointBL.x += tmp.x - BoxFollow.right;
	else if (tmp.x <= BoxFollow.left)
		PointBL.x -= BoxFollow.left - tmp.x;
	else if (IsExtend == 1)
	{
		BoxFollow.right = tmp.x;
		if (BoxFollow.right <= GAME_SCREEN_WIDTH - FAR_RIGHT)
		{
			BoxFollow.right = GAME_SCREEN_WIDTH - FAR_RIGHT;
			IsExtend = 0;
		}
	}
	else if (IsExtend == -1)
	{
		BoxFollow.left = tmp.x;
		if (BoxFollow.left >= FAR_LEFT)
		{
			BoxFollow.left = FAR_LEFT;
			IsExtend = 0;
		}
	}
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
	if (this->IsFreze == IsFreeze)
		return;
	auto objs = SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();

	this->IsFreze = IsFreeze;
	if (IsFreeze)
	{
		// put 2 virtual wall
		Entity *wall = new Entity();
		wall->SetPosition(D3DXVECTOR2(PointBL.x, PixelHeight / 2));
		wall->SetSize(16, PixelHeight);
		wall->SetTag(Entity::Entity_Tag::wall);
		objs->push_back(wall);

		wall = new Entity();
		wall->SetPosition(D3DXVECTOR2(PointBL.x + GAME_SCREEN_WIDTH, PixelHeight / 2));
		wall->SetSize(16, PixelHeight);
		wall->SetTag(Entity::Entity_Tag::wall);
		objs->push_back(wall);
	}
	else
	{
		// remove 2 virtual wall
		delete (*objs)[objs->size() - 1];
		objs->pop_back();
		delete (*objs)[objs->size() - 1];
		objs->pop_back();
		// check extend
		D3DXVECTOR2 pos = World2Render(Player::GetInstance()->GetPosition());
		if (pos.x > BoxFollow.right)
		{
			IsExtend = 1;
			BoxFollow.right = pos.x;
		}
		else if (pos.x<BoxFollow.left)
		{
			IsExtend = -1;
			BoxFollow.left = pos.x;
		}
	}
}

bool Camera::GetCameraFreeze()
{
	return this->IsFreze;
}

Camera::Camera()
{
	BoxFollow.top = FAR_TOP;
	BoxFollow.bottom = GAME_SCREEN_HEIGHT - FAR_BOTTOM; 
	BoxFollow.left = FAR_LEFT;
	BoxFollow.right = GAME_SCREEN_WIDTH - FAR_RIGHT; 

	PointBL = FollowPoint = D3DXVECTOR2(0, 0);
	IsFreze = false;
	IsExtend = 0;
}



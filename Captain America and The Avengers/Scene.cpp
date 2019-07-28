#include "Scene.h"
#include "Player.h"

D3DCOLOR Scene::GetBackcolor()
{
	return BackColor;
}

Scene::Scene()
{
	IsExitAble = false;
}

bool Scene::IsInsideExitZone()
{
	D3DXVECTOR2 pos = Player::GetInstance()->GetPosition();
	return ExitZone.left < pos.x && pos.x < ExitZone.right && ExitZone.bottom < pos.y&&pos.y < ExitZone.top;
}

#include "Scene.h"
#include "Player.h"

void Scene::Update(float dt)
{
	if (IsExitAble)
		FrameExitCounter++;
}

void Scene::Draw()
{
	if (IsExitAble)
		DrawExit();
}

D3DCOLOR Scene::GetBackcolor()
{
	return BackColor;
}

void Scene::SwapMap(int code)
{
	Mode = code;
}

int Scene::GetMode()
{
	return Mode;
}

Scene::Scene()
{
	IsExitAble = false;
	FrameExitCounter = 0;
	exit = new Sprite(L"Resources/exit.png", D3DCOLOR_XRGB(255, 0, 255));
	Mode = 0;
}

bool Scene::IsInsideExitZone()
{
	D3DXVECTOR2 pos = Player::GetInstance()->GetPosition();
	return ExitZone.left < pos.x && pos.x < ExitZone.right && ExitZone.bottom < pos.y&&pos.y < ExitZone.top;
}

void Scene::DrawExit()
{
	if (FrameExitCounter == 0)
	{
		FirstExitPosition = Player::GetInstance()->GetPosition();
		FirstExitPosition.y += PLAYER_SIZE_HEIGHT;
	}
	if (FrameExitCounter < 50)
		exit->DrawInt(FirstExitPosition);
	else
	{
		if (FrameExitCounter == 50)
		{
			exit->SetPosition(64, 24);
		}

		if (FrameExitCounter >> 4 & 1)
			exit->Draw();
	}
	FrameExitCounter++;
}

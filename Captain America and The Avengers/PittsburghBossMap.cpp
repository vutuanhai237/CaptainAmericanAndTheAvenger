#include "PittsburghBossMap.h"
#include "Framework/d3d.h"
#include "Camera.h"

PittsburghBossMap::PittsburghBossMap() : WorldMap(L"Resources/Map/pittsburgh_boss_map.txt", 0)
{
	CaroUp = new Animation(0, L"Resources/Map/CaroUp.png", D3DCOLOR_ARGB(0, 0, 0, 0), 4);
	CaroUp->SetTime(2.0f / 60);
	CaroUp->SetFrame(2);
	CaroDown = new Animation(0, L"Resources/Map/CaroDown.png", D3DCOLOR_ARGB(0, 0, 0, 0), 4);
	CaroDown->SetTime(2.0f / 60);
	Camera::GetInstance()->Init(this->GetMapSize());
}

void PittsburghBossMap::Update(float dt)
{
	CaroUp->Update(dt);
	CaroDown->Update(dt);
}

void PittsburghBossMap::Draw(D3DCOLOR ColorMode)
{
	LPD3DXSPRITE Hander = d3d::GetInstance()->GetSpriteHander();
	D3DXMATRIX OldMatrix;
	Hander->GetTransform(&OldMatrix);
	D3DXVECTOR2 pos = Camera::GetInstance()->GetCameraPosition();
	int gStartX = (int)(pos.x / PIXEL_PER_TITLE);
	int gStartY = Height - (int)(pos.y / PIXEL_PER_TITLE) - GRID_HIGHT_BLOCK - 1;
	Hander->Begin(D3DXSPRITE_ALPHABLEND);
	int x = (PIXEL_PER_TITLE >> 1) - ((int)pos.x % PIXEL_PER_TITLE);
	for (int i = gStartX; i <= gStartX + GRID_WIDTH_BLOCK; i++)
	{
		int y = -(PIXEL_PER_TITLE >> 1) + ((int)pos.y % PIXEL_PER_TITLE);
		for (int j = gStartY; j <= gStartY + GRID_HIGHT_BLOCK; j++)
		{
			if (j < 0)
			{
				y += PIXEL_PER_TITLE;
				continue;
			}
			switch (Map[j][i])
			{
			case 0:
				CaroDown->SetPosition((FLOAT)x, (FLOAT)y);
				CaroDown->ImperiouslyDraw();
				break;
			case 1:
				CaroUp->SetPosition((FLOAT)x, (FLOAT)y);
				CaroUp->ImperiouslyDraw();
				break;
			default:
				break;
			}
			y += PIXEL_PER_TITLE;
		}
		x += PIXEL_PER_TITLE;
	}
	Hander->End();
	Hander->SetTransform(&OldMatrix);
}

PittsburghBossMap::~PittsburghBossMap()
{
	delete CaroUp;
	delete CaroDown;
}
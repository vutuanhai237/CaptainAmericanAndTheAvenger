#include "CharlestonMap.h"
#include "Framework/d3d.h"
#include "Camera.h"

CharlestonMap::CharlestonMap() : WorldMap(L"Resources/Map/charleston_map.txt", 0)
{
	sewer = new Animation(1, L"Resources/Map/sewer.png", D3DCOLOR_ARGB(0, 0, 0, 0), 3, 1);
	sewer->SetTime(4.0f / 60);
	warter1 = new Animation(1, L"Resources/Map/water_1.png", D3DCOLOR_ARGB(0, 0, 0, 0), 3, 1);
	warter1->SetTime(4.0f / 60);
	warter2 = new Animation(1, L"Resources/Map/water_2.png", D3DCOLOR_ARGB(0, 0, 0, 0), 3, 1);
	warter2->SetTime(4.0f / 60);
	Camera::GetInstance()->Init(this->GetMapSize());
}

void CharlestonMap::Update(float dt)
{
	sewer->Update(dt);
	warter1->Update(dt);
	warter2->Update(dt);
}

void CharlestonMap::Draw()
{
	LPD3DXSPRITE Hander = d3d::GetInstance()->GetSpriteHander();
	D3DXMATRIX OldMatrix;
	Hander->GetTransform(&OldMatrix);

	D3DXVECTOR2 pos = Camera::GetInstance()->GetCameraPosition();
	int gStartX = (int)(pos.x / PIXEL_PER_TITLE);
	int gStartY = Height - (int)(pos.y / PIXEL_PER_TITLE) - GRID_HIGHT_BLOCK - 1;

	//Debug::PrintOut(L"%d ", gStartY);

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
			case CHARLESTON_REPLACEID_0:
				sewer->SetPosition(x, y);
				sewer->ImperiouslyDraw();
				break;
			case CHARLESTON_REPLACEID_1:
				warter1->SetPosition(x, y);
				warter1->ImperiouslyDraw();
				break;
			case CHARLESTON_REPLACEID_2:
				warter2->SetPosition(x, y);
				warter2->ImperiouslyDraw();
				break;
			default:
				SetRect(Map[j][i]);
				Sprite::SetPosition(x, y);
				Hander->SetTransform(&Matrix);
				Hander->Draw(texture, &rect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
				break;
			}
			y += PIXEL_PER_TITLE;
		}
		x += PIXEL_PER_TITLE;
	}

	Hander->End();

	Hander->SetTransform(&OldMatrix);
}

CharlestonMap::~CharlestonMap()
{
	delete warter1;
	delete warter2;
}

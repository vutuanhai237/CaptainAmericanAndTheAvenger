#include "WorldMap.h"
#include "Framework/d3d.h"
#include "Framework/GameSetting.h"
#include <fstream>
#include <math.h>

using namespace std;

WorldMap::WorldMap(LPCWSTR LinkTitleMap, int IDTitleMap, int pixelPerTitle) : Sprite(IDTitleMap)
{
	fstream data(LinkTitleMap, ios_base::in);
	data >> TotalTitle >> Width >> Height;
	Map = new int*[Height];
	for (int i = 0; i < Height; i++)
	{
		Map[i] = new int[Width];
		for (int j = 0; j < Width; j++)
			data >> Map[i][j];
	}
	PixelWidth = Width * pixelPerTitle;
	PixelHight = Height * pixelPerTitle;
	PixelPerTitle = pixelPerTitle;
	cDelta = GAME_SCREEN_WIDTH / pixelPerTitle + 1;
	cFollowPoint = D3DXVECTOR2(0, 0);
	cDeltaRender = 0;
}

void WorldMap::SetCamera(D3DXVECTOR2 Position)
{
	cFollowPoint = Position;
	// Force camera only in map
	if (cFollowPoint.x < 0)
		cFollowPoint.x = 0;
	if (cFollowPoint.y > PixelWidth)
		cFollowPoint.y = PixelWidth;

	cFrom = floorf((Position.x - (GAME_SCREEN_WIDTH >> 2)) / PixelPerTitle); 
	cDeltaRender = (int)floorf(cFollowPoint.x) % PixelPerTitle;
	if (cFrom < 0)
	{
		cFrom = 0;
		cDeltaRender = 0;
	}
	if (cFrom > Width - cDelta)
	{
		cFrom = Width - cDelta;
		cDeltaRender = PixelPerTitle;
	}
}

void WorldMap::SetCamera(float x, float y)
{
	SetCamera(D3DXVECTOR2(x, y));
}

D3DXVECTOR2 WorldMap::GetCameraPosition()
{
	return cFollowPoint;
}

void WorldMap::Draw()
{	
	LPD3DXSPRITE Hander = d3d::GetInstance()->GetSpriteHander();
	D3DXMATRIX OldMatrix;
	Hander->GetTransform(&OldMatrix);

	Hander->Begin(D3DXSPRITE_ALPHABLEND);
	int cTo = cFrom + cDelta;
	D3DXVECTOR3 pDraw(0, 0, 0);

	int x = (PixelPerTitle >> 1) - cDeltaRender;
	for (int j = cFrom; j < cTo; j++)
	{
		int y = PixelPerTitle >> 1;
		for (int i = 0; i < Height; i++)
		{
			SetRect(Map[i][j]);
			Sprite::SetPosition(x, y);
			Hander->SetTransform(&Matrix);
			Hander->Draw(texture, &rect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
			y += PixelPerTitle;
		}
		x += PixelPerTitle;
	}
	Hander->End();

	Hander->SetTransform(&OldMatrix);
}

void WorldMap::SetRect(int ID)
{
	LONG Left = ID * PixelPerTitle;
	Sprite::SetRect(0, PixelPerTitle, Left, Left + PixelPerTitle);
}

WorldMap::~WorldMap()	
{
	for (int i = 0; i < Width; i++)
		delete Map[i];
	delete Map;
}

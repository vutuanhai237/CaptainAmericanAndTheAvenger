#pragma once
#include "Framework/Sprite.h"

class WorldMap : public Sprite
{
public:
	WorldMap(LPCWSTR LinkTitleMap, int IDTitleMap, int PixelPerTitle);
	void SetCamera(D3DXVECTOR2 Position);
	void SetCamera(float x, float y);
	D3DXVECTOR2 GetCameraPosition();
	void Draw() override;
	void SetRect(int IDTitle);
	~WorldMap();
private:
	int PixelWidth, PixelHight;
	int TotalTitle;
	int Width, Height;
	int **Map;
	int PixelPerTitle;
	// camera
	int cFrom, cDelta;
	D3DXVECTOR2 cFollowPoint;
	int cDeltaRender;
};


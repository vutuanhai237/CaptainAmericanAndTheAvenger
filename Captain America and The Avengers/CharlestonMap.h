#pragma once
#include "WorldMap.h"
#include "Framework/Animation.h"
#define CHARLESTON_REPLACEID_0 69
#define CHARLESTON_REPLACEID_1 72
#define CHARLESTON_REPLACEID_2 75

class CharlestonMap : public WorldMap
{
public:
	CharlestonMap();
	void Update(float dt);
	void Draw(D3DCOLOR ColorMode = Sprite::DefaultColorMode) override;
	~CharlestonMap();
private:
	Animation *warter1;
	Animation *warter2;
	Animation *sewer;
	Animation *exit;
};
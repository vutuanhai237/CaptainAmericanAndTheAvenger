#pragma once
#include "WorldMap.h"
#include "Framework/Animation.h"
class PittsburghBossMap : public WorldMap
{
public:
	PittsburghBossMap();
	void Update(float dt);
	void Draw(D3DCOLOR ColorMode = Sprite::DefaultColorMode) override;
	~PittsburghBossMap();
private:
	Animation *CaroUp, *CaroDown;
};


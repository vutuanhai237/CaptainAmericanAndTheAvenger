#pragma once
#include "WorldMap.h"
#include "Framework/Animation.h"
class PittsburghBossMap : public WorldMap
{
public:
	void Update(float dt);
	void Draw(D3DCOLOR ColorMode = Sprite::DefaultColorMode) override;
	PittsburghBossMap();
	~PittsburghBossMap();
private:
	Animation *CaroUp;
	Animation *CaroDown;
};


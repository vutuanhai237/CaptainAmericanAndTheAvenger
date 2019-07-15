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
	void Draw() override;
	~CharlestonMap();
private:
	Animation *warter1, *warter2, *sewer;
};
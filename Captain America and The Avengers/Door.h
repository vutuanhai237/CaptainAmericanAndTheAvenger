#pragma once
#include "Entity.h"
#include "Framework/Animation.h"

class Door : public Entity
{
public:
	Door(int WorldX, int WorldY, int GotoCode, int PositionGotoX, int PositionGotoY);
	~Door();

	int OnCollision(Entity *, float dt) override;
	void Update(float dt) override;
	void Draw() override;
	
	static int IDDarkDoor;
	static int IDLightDoor;
private:
	std::vector<Animation*> *animation;
	int GotoCode;
	D3DXVECTOR2 PositionGoto;
};


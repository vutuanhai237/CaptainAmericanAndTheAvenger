#pragma once
#include "Entity.h"
#include "ShieldState.h"
#include "Framework/Animation.h"

class Shield : public Entity
{
public:
	static Shield *GetInstance();
	void Release();
	D3DXVECTOR2 GetPosition() override;
	int OnCollision(Entity *, float dt) override;
	BoundingBox GetBoundingBox() override;
	void Update(float dt);
	void Draw() override;
	void SetShieldState(ShieldState *state);
	ShieldState *GetShieldState();
	ShieldState *GetBufferState();
	Animation *GetAnimation();
protected:
	Animation *shield;
	ShieldState *state;
	ShieldState *buffer;
private:
	Shield();
	~Shield();
	static Shield *Instance;
};
#pragma once
#include "Enemy.h"
#include "Equation.h"
#define TURRET_HP 64
#define TURRET_TIME_FIRING 1.5f
#define TURRET_TIME_ROLLING 1.396f

class Turret : public Enemy
{
public:
	enum NameState {
		rolling,
		firing
	};
	int i = 0;
	int frame;
	float time_fire;
	float time_rolling;
	float alpha;
	float omega;
	NameState current_state;
	void Update(float dt) override;
	void UpdateRollingState(float dt);
	void UpdateFiringState(float dt);
	int OnCollision(Entity*, float dt) override;
	BoundingBox GetBoundingBox() override;
	void Draw() override;
	Turret(D3DXVECTOR2 position_spawn, float alpha);
	~Turret() override;
};


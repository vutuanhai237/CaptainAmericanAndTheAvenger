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
	// Function
	void Update(float dt) override;
	int OnCollision(Entity*, float dt) override;
	void Draw() override;
	BoundingBox GetBoundingBox() override;
	NameState current_state;
	void UpdateRollingState(float dt);
	void UpdateFiringState(float dt);
	Turret(D3DXVECTOR2 position_spawn, float alpha);
	~Turret() override;
};


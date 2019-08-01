#pragma once
#include "EnemyWeapon.h"
#include "Equation.h"
#include "BossGragas.h"
#define BARREL_DAMAGE 5
#define BARREL_VELOCITY_X 100.0f
#define BARREL_SIZE_WIDTH 22
#define BARREL_SIZE_HEIGHT 14
class Barrel : public EnemyWeapon
{

public:
	virtual void Update(float dt) override;
	virtual int OnCollision(Entity*, float dt) override;
	virtual void Exploding(float dt);
	virtual void Release();
	virtual void Draw();
	Barrel(D3DXVECTOR2, Entity::Entity_Direction direction);
	CollisionOut IsCollisionWithWall(float dt, int delta_y = 4);

	~Barrel() override;
	bool IsDead;
	float distance;
	bool IsStraight;
	bool IsExploding;
	float distance_out;
	Animation* current_ani;
	Equation *e;
protected:
	float time_wait;
	bool IsCrossed;
	float time_out_explode;
	float time_out_straight;
};
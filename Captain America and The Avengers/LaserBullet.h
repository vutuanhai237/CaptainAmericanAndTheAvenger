#pragma once
#include "EnemyWeapon.h"
#include "Equation.h"
#define LASER_BULLET_DAMAGE 5
#define LASER_BULLET_VELOCITY_X 150.0f
class LaserBullet : public EnemyWeapon
{
public:
	virtual void Update(float dt) override;
	virtual int OnCollision(Entity*, float dt) override;
	virtual void Draw();
	LaserBullet(D3DXVECTOR2, Entity::Entity_Direction direction, FLOAT velocity_y = 0.0f);
	~LaserBullet() override;
	bool IsDead;
	bool IsComeBack;
	Equation* e;
	Animation* current_ani;
	float time_out_straight;
	float distance;
};


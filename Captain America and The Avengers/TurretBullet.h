#pragma once
#include "EnemyWeapon.h"
#define TURRET_BULLET_VELOCITY 200.0f
#define DISTANCE_OUT 400.0f
#define TIME_OUT_STRAIGHT 0.016*15
#define TURRET_BULLET_DAMAGE 1
class TurretBullet : public EnemyWeapon
{
public:
	virtual void Update(float dt) override;
	virtual int OnCollision(Entity*, float dt) override;
	virtual void Draw();
	TurretBullet(D3DXVECTOR2, Entity::Entity_Direction direction, int alpha);
	~TurretBullet() override;
	float time_out_straight;
	float distance;
	bool IsDead;
	Animation* current_ani;
};


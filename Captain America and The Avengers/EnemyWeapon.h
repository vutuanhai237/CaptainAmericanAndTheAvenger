#pragma once
#include "Entity.h"
#include "Player.h"
#define TIME_EXPLODE 0.25f
class EnemyWeapon : public Entity
{
public:
	virtual void Update(float dt);
	virtual int OnCollision(Entity*, float dt) override;
	virtual bool IsCollisionExplode();
	EnemyWeapon();
	virtual ~EnemyWeapon();
protected:
	Animation* explode_ani;
	int damage;
};


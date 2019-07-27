#pragma once
#include "Entity.h"
#include "Player.h"
#include "Framework/Animation.h"
class EnemyWeapon : public Entity
{
public:
	virtual void Update(float dt);
	virtual int OnCollision(Entity*, float dt) override;
	EnemyWeapon();
	virtual ~EnemyWeapon();
protected:
	Animation* explode_ani;

};


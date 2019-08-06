#pragma once
#include "EnemyWeapon.h"
// properties for bullet
#define BULLET_DAMAGE 1
#define BULLET_VELOCITY_X 200.0f
#define TIME_OUT_STRAIGHT 0.016*15
#define DISTANCE_OUT 400.0f

class Bullet : public EnemyWeapon
{
public:	
	virtual void Update(float dt) override;
	virtual int OnCollision(Entity*, float dt) override;
	virtual void Draw();
	Bullet(D3DXVECTOR2, Entity::Entity_Direction direction, FLOAT direction_y = 0.0f);
	~Bullet() override;
	bool IsDead;
	float distance;
	float time_out_straight;
	Animation* current_ani;
};


#pragma once
#include "EnemyWeapon.h"
#define ENERGY_BULLET_VELOCITY_X 400.0f
#define ENERGY_BULLET_DAMAGE 3
class EnergyBullet : public EnemyWeapon
{
public:
	enum EnergyBulletType {
		horizontal = 14,
		vertical = 15,
		crossed = 16
	};
	virtual void Update(float dt) override;
	virtual int OnCollision(Entity*, float dt) override;
	virtual void Draw();
	EnergyBullet(D3DXVECTOR2, Entity::Entity_Direction direction, FLOAT direction_y = 0.0f);
	~EnergyBullet() override;
	bool IsDead;
	float distance;
	float time_out_straight;
	Animation* current_ani;
	Animation* horizontal_ani;
	Animation* vertical_ani;
	Animation* crossed_ani;
};


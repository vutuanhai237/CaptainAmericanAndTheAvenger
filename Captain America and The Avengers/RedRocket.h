#pragma once
#include "EnemyWeapon.h"
class RedRocket : public EnemyWeapon
{

public:
	enum RedRocketState {
		crossed,
		horizontal
	};
	virtual void Update(float dt) {};
	virtual void Render() {};
	virtual void OnCollision() {};
	
	RedRocket();
	~RedRocket();
protected:
	Animation* crossed_ani;
	Animation* horizontal_ani;
};


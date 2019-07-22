#pragma once
#include "ShieldState.h"

#define SHIELD_ATTACK_VELOCITY 6.0f
#define SHIELD_FOLLOW_VELOCITY_Y 4.0f
#define SHIELD_ATTACK_ACCELERATION 0.8f
#define SHIELD_ATTACK_TIME_OUT 0.32f

#define SHIELD_BEFORE_ATTACK_FRAME_1_DELTA_X -19.0f
#define SHIELD_BEFORE_ATTACK_FRAME_1_DELTA_Y 9.5f
#define SHIELD_BEFORE_ATTACK_FRAME_2_DELTA_X 23.0f
#define SHIELD_BEFORE_ATTACK_FRAME_2_DELTA_Y 0.5f

class ShieldAttackState : public ShieldState
{
public:
	ShieldAttackState();
	void Update(float dt) override;
	void Draw() override;
private:
	int direction;
	float delta;
	bool IsComeBack;
	float DeltaSlow;
};
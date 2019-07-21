#pragma once
#include "ShieldState.h"

#define SHIELD_NOMAL_DELTA_X 10.5f
#define SHIELD_NOMAL_DELTA_Y 8.0f
#define SHIELD_NOMAL_DUCKING_DELTA_X 10.5f
#define SHIELD_NOMAL_DUCKING_DELTA_Y -11.0f
#define SHIELD_NOMAL_DASHING_FRAME_2_DELTA_X 18.5f
#define SHIELD_NOMAL_DASHING_FRAME_2_DELTA_Y -2.0f
#define SHIELD_NOMAL_DASHING_FRAME_3_DELTA_X 29.5
#define SHIELD_NOMAL_DASHING_FRAME_3_DELTA_Y 0.0f

class ShieldNomalState : public ShieldState
{
public:
	ShieldNomalState();
	void Update(float dt) override;
	void Draw() override;
};
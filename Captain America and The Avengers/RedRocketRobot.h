#pragma once
#include "Enemy.h"
#include "RedRocket.h"

#define TIME_DUCKING 2.0f
#define TIME_IDLE 2.0f
#define RED_ROCKET_ROBOT_SIZE_WIDTH 8
#define RED_ROCKET_ROBOT_SIZE_HEIGHT 40
#define RED_ROCKET_ROBOT_FOOT_HEIGHT 8
#define RED_ROCKET_ROBOT_VELOCITY 80
class RedRocketRobot : public Enemy
{
private:
	Animation* running_ani;
	Animation* ducking_ani;
	Animation* idle_ani;
	RedRocket* red_rocket;
	D3DXVECTOR2 position_spawn;
	D3DXVECTOR2 position_goto;
public:
	enum RedRocketRobotState {
		none,
		idle,
		running,
		ducking,
		beaten
	};
	virtual void Update(float dt); 
	virtual void Render();
	virtual void OnCollision();
	virtual void SetActive(bool IsActive);
	virtual void Draw();
	bool IsCollisionWithGround(float dt, int delta_y = 12);
	bool IsRunning;
	bool IsDucking;
	bool Isbeaten;
	bool IsIdle;
	bool IsHaveJump;
	float time_ducking;
	float time_idle;
	RedRocketRobotState current_state;
	RedRocketRobot();
	~RedRocketRobot();
};


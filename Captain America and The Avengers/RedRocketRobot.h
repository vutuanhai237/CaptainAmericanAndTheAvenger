#pragma once
#include "Enemy.h"
#include "RedRocket.h"
#include "Equation.h"
#include <vector>
#define TIME_DUCKING 2.0f
#define TIME_IDLE 2.0f
#define RED_ROCKET_ROBOT_SIZE_WIDTH 8
#define RED_ROCKET_ROBOT_SIZE_HEIGHT 44
#define RED_ROCKET_ROBOT_FOOT_HEIGHT 8
#define RED_ROCKET_ROBOT_VELOCITY 80
#define RED_ROCKET_ROBOT_VELOCITY_X 80
class RedRocketRobot : public Enemy
{
private:
	Animation* running_ani;
	Animation* ducking_ani;
	Animation* idle_ani;
public:
	enum RedRocketRobotState {
		none,
		idle,
		running,
		ducking,
		beaten,
		jumping
	};
	enum Level {
		stupid,
		normal,
		clever
	};
	virtual void Update(float dt);
	virtual void UpdateStupidLevel(float dt);
	virtual void UpdateNormalLevel(float dt);
	virtual void UpdateCleverLevel(float dt);
	CollisionOut SweptAABBPrivate(BoundingBox recta, BoundingBox rectb);
	virtual void OnCollision();
	virtual void SetActive(bool IsActive);
	virtual void Draw();
	bool IsCollisionWithGround(float dt, int delta_y = 12);
	bool IsRunning;
	bool IsDucking;
	bool Isbeaten;
	bool IsIdle;
	bool IsHaveJump;
	bool IsLoop;
	bool IsCrossed;
	bool IsLock;
	bool IsLockChangeRocket;
	bool IsChamDatLanDau;
	int IsJumpingFirst;
	float time_ducking;
	float time_idle;
	int rocket_active;
	Entity::Entity_Direction goto_direction;
	Level level;
	RedRocketRobotState current_state;
	RedRocket* rocket;
	Equation *e;
	int NumberRocket;
	RedRocketRobot();
	RedRocketRobot(Level level, D3DXVECTOR2 position_spawn, D3DXVECTOR2 position_goto, D3DXVECTOR2 position_loop);
	void UpdateFromFile();
	~RedRocketRobot();
};


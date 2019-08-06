#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Equation.h"
#define GRAY_ROBOT_HP 2
#define GRAY_ROBOT_SIZE_WIDTH 8
#define GRAY_ROBOT_SIZE_HEIGHT 44
#define GRAY_ROBOT_FOOT_HEIGHT 8
#define GRAY_ROBOT_VELOCITY_Y 140
#define GRAY_ROBOT_VELOCITY_X 30
#define GRAY_ROBOT_TIME_FIRING 0.7f
class GrayRobot : public Enemy
{
public:
	enum GrayRobotState {
		idle = 25,
		firing = 26,
		beaten = 27
	};
	int IsLui;
	int previous_IsLui;
	int count_bullet;
	int i;
	float time_fire;	
	float distance;
	float Ax;
	float Ay;
	float omega;
	float t;
	bool UpdateOneTime;
	bool UpdateOneTime2;
	D3DXVECTOR2 virtual_point;
	GrayRobotState current_state;
	virtual void Update(float dt);
	void UpdateIdleState(float dt);
	void UpdateFiringState(float dt);
	virtual void Draw();
	// on collusion
	BoundingBox GetBoundingBox() override;
	virtual int OnCollision(Entity*, float dt);
	bool IsCollisionWithGround(float dt, int delta_y = 12);
	GrayRobot(D3DXVECTOR2 position_spawn, float distance);
	~GrayRobot() override;
protected:
	Animation* firing_ani;
	Animation* idle_ani;
};


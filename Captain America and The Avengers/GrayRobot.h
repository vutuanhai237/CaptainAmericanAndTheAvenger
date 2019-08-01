#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Equation.h"
#define GRAY_ROBOT_HP 2
#define GRAY_ROBOT_SIZE_WIDTH 8
#define GRAY_ROBOT_SIZE_HEIGHT 44
#define GRAY_ROBOT_FOOT_HEIGHT 8
#define GRAY_ROBOT_VELOCITY_Y 80
#define GRAY_ROBOT_VELOCITY_X 30
#define GRAY_ROBOT_TIME_FIRING 0.7f
class GrayRobot : public Enemy
{
private:
	Animation* firing_ani;
	Animation* idle_ani;
public:
	// Share zone
	enum GrayRobotState {
		none,
		idle = 25,
		firing = 26,
		beaten = 27
	};
	bool UpdateOneTime;
	bool UpdateOneTime2;
	float time_fire;
	int IsLui;
	int previous_IsLui;
	int i = 0;
	Eclipse *e;
	float distance;
	float Ax;
	float Ay;
	float omega;
	float t;
	D3DXVECTOR2 virtual_point;
	int count_bullet;
	virtual void Update(float dt);
	virtual int OnCollision(Entity*, float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	GrayRobotState current_state;
	void UpdateIdleState(float dt);
	void UpdateFiringState(float dt);
	bool IsCollisionWithGround(float dt, int delta_y = 12);

	GrayRobot(D3DXVECTOR2 position_spawn, float distance);
	~GrayRobot() override;
};


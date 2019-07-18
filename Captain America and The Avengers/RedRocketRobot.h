#pragma once
#include "Enemy.h"
#include "RedRocket.h"

#define TIME_DUCKING 2.0f
#define TIME_IDLE 2.0f
class RedRocketRobot : public Enemy
{
private:
	Animation* running_ani;
	Animation* ducking_ani;
	Animation* idle_ani;
	RedRocket* red_rocket;
public:
	enum RedRocketRobotState {
		idle,
		running,
		ducking,
		beaten
	};
	virtual void Update(float dt); 
	virtual void Render();
	virtual void OnCollision();
	virtual void SetActive(bool IsActive);
	bool IsRunning;
	bool IsDucking;
	bool Isbeaten;
	

	RedRocketRobot();
	~RedRocketRobot();
};


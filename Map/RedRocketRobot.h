#pragma once
#include "Enemy.h"

#include "RedRocket.h"
class RedRocketRobot : public Enemy
{
private:
	Animation* running_ani;
	Animation* ducking_ani;
	RedRocket* red_rocket;
public:
	enum RedRocketRobotState {
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


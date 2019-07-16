#pragma once
#include "Entity.h"
#include "PlayerState.h"
#include <map>

#define VELOCITY_X 40.0f
#define VELOCITY_Y 80.0f











using namespace std;
class Player : public Entity
{
public:
	static Player* GetInstance();
	Player();
	~Player();
	void Update(float dt);
	void Render();
	void Draw();
	void HandleInput(float dt);
	void Init();
	void ChangeState(PlayerState* new_state);
	PlayerState::NameState GetCurrentState();
	PlayerState* GetPlayerState();
	void SetCurrentState(PlayerState::NameState new_state);
	Animation* GetCurrentAnimation();
	void SetPosition(float x, float y) override;
	void AddTimeBuffer(float dt);
	float GetTimeBuffer();

	void SetTimeBuffer(float dt);
protected:
	static Player *instance;
	std::map<int, Animation*> animations;
	PlayerState::NameState current_state;
	PlayerState* player_state;
	Animation* animation;
	float time_buffer;
};


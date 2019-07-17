#pragma once
#include "Entity.h"
#include "PlayerState.h"
#include <map>

#define VELOCITY_X 80.0f
#define VELOCITY_Y 140.0f
#define DELTA_JUMP 1.0f
#define DISTANCE_JUMPING 120.0f
#define DISTANCE_ROLLING 140.0f
#define TIME_AIR 0.016*15
#define TIME_ROLLING 0.016* 30
#define TIME_KICKING 0.016* 10







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
	void SetIsRolling(bool IsRolling);
	bool GetIsRolling();
	void SetPositionIdle(D3DXVECTOR2 position_idle);
	D3DXVECTOR2 GetPositionIdle();

protected:
	static Player *instance;
	std::map<int, Animation*> animations;
	PlayerState::NameState current_state;
	PlayerState* player_state;
	Animation* animation;
	D3DXVECTOR2 position_idle;
	float time_buffer;
	bool IsRolling;
};


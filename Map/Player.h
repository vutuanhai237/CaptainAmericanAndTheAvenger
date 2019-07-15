#pragma once
#include "Entity.h"
#include "PlayerState.h"
#include <map>

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
	void HandleInput();
	void Init();
	void ChangeState(PlayerState* new_state);
	PlayerState::NameState GetCurrentState();
	PlayerState* GetPlayerState();
	void SetCurrentState(PlayerState::NameState new_state);
	Animation* GetCurrentAnimation();
	void SetPosition(float x, float y) override;
protected:
	static Player *instance;
	std::map<int, Animation*> animations;
	PlayerState::NameState current_state;
	PlayerState* player_state;
	Animation* animation;
	
};


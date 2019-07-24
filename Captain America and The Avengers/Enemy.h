#pragma once
#include "Entity.h"
#include "Player.h"
#include "BoxCollider.h"
#include "Framework/Animation.h"
#include <math.h>
#include "SceneManager.h"
class Enemy: public Entity
{
public:
	virtual Animation* GetCurrentAnimation();
	virtual void Update(float dt); // update animation và loại animation, gọi vũ khí
	virtual void OnCollision() {}; // xử lý va chạm của enemy và gọi xử lý va chạm vũ khí
	virtual void SetActive(bool IsActive) {}; // set enemy có đc render, update, oncollision hay không
	virtual void Delete() {}; // gọi khi enemy ra khỏi camera hoặc bị chết
	virtual void Spawn(); // sinh ra quái từ vị trí đc đọc từ file
	virtual void SetSpawnBox(float top, float left, float width, float height, Entity::Entity_Direction direction);
	virtual void SetBoxCollider(BoxCollider box);
	virtual bool IsCollisionWithGround(float dt, int delta_y = 12);
	virtual void Draw() {};
	Enemy();
	virtual ~Enemy();
	// bool variable
	bool IsJumping;
protected:
	Animation* beaten_ani; 
	Animation* explode_ani;
	Animation* current_animation;
	bool IsExplode;
	D3DXVECTOR2 position_spawn;
	D3DXVECTOR2 position_goto;
	D3DXVECTOR2 position_loop;
	BoxCollider spawn_box; // box spawn cố định còn box va chạm khác
	BoxCollider box;
};


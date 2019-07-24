#include "RedRocket.h"
#include "FrameWork//Debug.h"


void RedRocket::Update(float dt)
{
	EnemyWeapon::Update(dt);
	this->current_ani->Update(dt);

	if (IsCrossed) {
		if (IsStraight) {
			this->current_ani = this->horizontal_ani;
			this->time_out_straight += dt;
			if (this->time_out_straight >= TIME_OUT_STRAIGHT) {
				IsStraight = false;
			}
		}
		else {
			this->position.y += abs(this->GetVelocityX()*dt);
			this->current_ani = this->crossed_ani;
		}
	}
	else {
	
	}
	this->distance += abs(this->GetVelocityX()*dt);

}

void RedRocket::OnCollision()
{
}

void RedRocket::Release(D3DXVECTOR2 position_respawn) 
{
	this->SetVelocityX(0);
	this->SetPosition(position_respawn);
	this->distance = 0;
	this->IsFire = false;
	this->IsStraight = true;
	this->time_out_straight = 0;
}

void RedRocket::Draw()
{
	if (this->GetVelocityX() != 0) {
		this->current_ani->Draw(this->GetPosition());
		if (this->GetMoveDirection()) {
			this->current_ani->SetScale(1, 1);
		}
		else {
			this->current_ani->SetScale(-1, 1);
		}
	}
	
}

RedRocket::RedRocket()
{
	this->crossed_ani = new Animation(RedRocket::RedRocketState::crossed, 2);
	this->horizontal_ani = new Animation(RedRocket::RedRocketState::horizontal, 2);
	this->current_ani = this->horizontal_ani;
	this->SetVelocityX(5);
	this->SetPosition(0,0);
	this->IsLocking = true;
	this->distance = 0;
	this->IsStraight = true;
	this->time_out_straight = 0;
}

RedRocket::RedRocket(D3DXVECTOR2 position, bool IsCrossed)
{

	this->crossed_ani = new Animation(RedRocket::RedRocketState::crossed, 2);
	this->horizontal_ani = new Animation(RedRocket::RedRocketState::horizontal, 2);
	this->current_ani = this->horizontal_ani;
	this->SetVelocityX(5);
	this->SetPosition(position);
	this->IsLocking = true;
	this->distance = 0;
	this->IsStraight = true;
	this->time_out_straight = 0;
	this->IsCrossed = IsCrossed;
}


RedRocket::~RedRocket()
{
	delete this->crossed_ani;
	delete this->horizontal_ani;
}

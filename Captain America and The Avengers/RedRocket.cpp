#include "RedRocket.h"
#include "FrameWork//Debug.h"


void RedRocket::Update(float dt)
{
	EnemyWeapon::Update(dt);
	this->current_ani->Update(dt);
	this->distance += this->GetVelocityX()*dt;
}

void RedRocket::Render()
{
}

void RedRocket::OnCollision()
{
}

void RedRocket::Release() 
{
	delete this;
}

void RedRocket::Draw()
{
	this->current_ani->Draw(this->GetPosition());
	if (this->GetMoveDirection()) {
		this->current_ani->SetScale(1, 1);
	}
	else {
		this->current_ani->SetScale(-1, 1);
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
}

RedRocket::RedRocket(D3DXVECTOR2 position)
{

	this->crossed_ani = new Animation(RedRocket::RedRocketState::crossed, 2);
	this->horizontal_ani = new Animation(RedRocket::RedRocketState::horizontal, 2);
	this->current_ani = this->horizontal_ani;
	this->SetVelocityX(5);
	this->SetPosition(position);
	this->IsLocking = true;
	this->distance = 0;

}


RedRocket::~RedRocket()
{
	delete this->crossed_ani;
	delete this->horizontal_ani;
}

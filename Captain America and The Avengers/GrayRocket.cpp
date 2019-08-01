#include "GrayRocket.h"
#include "Framework/GameSetting.h"

int GrayRocket::ID = -1;

float TrueRadian(float radian)
{
	while (radian < 0)
		radian += 2 * PI;
	while (radian > 2 * PI)
		radian -= 2 * PI;
	return radian;
}

GrayRocket::GrayRocket(FLOAT WorldX, FLOAT WorldY, Entity::Entity_Direction direction) : EnemyWeapon()
{
	Entity::position.x = WorldX;
	Entity::position.y = WorldY;
	rocket = new Animation(GrayRocket::ID, 2);
	rocket->SetTime(0.125f);
	if (direction == Entity::Entity_Direction::LeftToRight)
		radian = 0;
	else
		radian = PI;
	Timer = 0.0f;
	ChangeDirectionCounter = 7;
}

GrayRocket::~GrayRocket()
{
	delete rocket;
}

void GrayRocket::Update(float dt)
{
	Timer += dt;
	rocket->Update(dt);
	D3DXVECTOR2 target = Player::GetInstance()->GetPosition();
	if (ChangeDirectionCounter > 0 && Timer > GRAY_ROCKET_TIME_CHANGE_DIRECTION)
	{
		Timer -= GRAY_ROCKET_TIME_CHANGE_DIRECTION;
		float dx = target.x - Entity::position.x;
		float dy = target.y - Entity::position.y;
		if (sqrt(dx*dx + dy * dy) < GRAY_ROCKET_MIN_LOCATION_FOLLOW)
			ChangeDirectionCounter = 0;
		else
		{
			float direction = atan2f(dy, dx);


			float tmp1 = TrueRadian(direction - radian);
			float tmp2 = TrueRadian(radian - direction);
			if (tmp1 < tmp2)
			{
				if (tmp1 > GRAY_ROCKET_TURN / 2)
				{
					radian = TrueRadian(radian + GRAY_ROCKET_TURN);
					ChangeDirectionCounter--;
				}
			}
			else
			{
				if (tmp2 > GRAY_ROCKET_TURN / 2)
				{
					radian = TrueRadian(radian - GRAY_ROCKET_TURN);
					ChangeDirectionCounter--;
				}
			}
			rocket->SetRotation(-radian);
		}
	}
	rocket->Update(dt);
	Entity::position.x += cosf(radian)*GRAY_ROCKET_VELOCITY*dt;
	Entity::position.y += sinf(radian)*GRAY_ROCKET_VELOCITY*dt;
}

void GrayRocket::Draw()
{
	rocket->Draw(Entity::position);
}
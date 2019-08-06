#include "FrameWork/SoundManager.h"
#include "GrayRocketRobot.h"
#include "Shield.h"

void GrayRocketRobot::Update(float dt)
{
	Enemy::Update(dt);
	Player *player = Player::GetInstance();
	this->current_animation->Update(dt);
	if (this->IsExplode)
	{
		this->time_explode += dt;
		this->current_animation = explode_ani;
		this->SetVelocityX(0.0f);
		if (this->time_explode >= TIME_EXPLODE) 
		{
			this->IsDead = true;
			this->IsActive = false;
		}
		return;
	}
	if (this->IsBeaten)
	{
		this->current_state = GrayRocketRobotState::beaten;
		this->current_animation = beaten_ani;
		this->SetVelocityX(0.0f);
		this->time_beaten += dt;
		if (this->time_beaten >= TIME_BEATEN)
		{
			this->IsExplode = true;
			SoundManager::GetInstance()->Play(SoundManager::SoundList::entity_explode);
		}
		if (this->GetMoveDirection() == Entity::Entity_Direction::LeftToRight)
		{
			this->position.x -= 1;
		}
		else 
		{
			this->position.x += 1;
		}
		return;
	}
	this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
	// Khi không còn va chạm với mặt đất, cho phép một lần nhảy
	if (IsChamDatLanDau == false)
	{
		if (this->IsCollisionWithGround(dt)) 
		{
			this->SetVelocityY(0);
			this->position_spawn = this->position;
			IsChamDatLanDau = true;
		}
		else 
		{
			this->SetVelocityY(GRAY_ROCKET_ROBOT_VELOCITY);
		}
		return;
	}
	// Cập nhật tọa độ khi đang nhảy
	if (this->current_state == GrayRocketRobotState::jumping)
	{
		if (this->IsCollisionWithGround(dt) && this->IsJumpingFirst > 5) 
		{
			this->current_state = GrayRocketRobotState::running;
			this->current_animation = running_ani;
			return;
		}
		this->IsJumpingFirst++;
		this->SetVelocityX(GRAY_ROCKET_ROBOT_VELOCITY_X);
		this->SetVelocityY(GRAY_ROCKET_ROBOT_VELOCITY);
		this->SetPositionY(e->GetYFromX(this->GetPosition().x));
		return;
	}
	// Bắt việc shield có được ném hay không, thì nhảy để né
	if (Shield::GetInstance()->GetShieldState()->GetCurrentState() == ShieldState::NameState::ShieldAttack
		&& this->IsJumping == false
		&& this->current_state == GrayRocketRobotState::running
		&& (this->GetMoveDirection() != Player::GetInstance()->GetMoveDirection()))
	{
		this->IsJumping = true;
		this->current_state = GrayRocketRobotState::jumping;
		this->current_animation = ducking_ani;
		e = new Equation(
			this->position,
			D3DXVECTOR2(this->position.x - 50, this->position.y));
		return;
	}
	// Đi tới position togo, nếu đã nhảy rồi thì không đi nữa, hoặc đã đi tới điểm cần tới
	if (abs(position.x - position_goto.x) >= 10.0f && this->IsJumpingFirst == 0)
	{
		this->SetVelocityX(GRAY_ROCKET_ROBOT_VELOCITY_X);
		this->current_state = GrayRocketRobotState::running;
		this->current_animation = this->running_ani;
	}
	else
	{
		if ((IsLoop == false && this->current_state == GrayRocketRobotState::running) || this->IsJumpingFirst > 0)
		{
			this->SetVelocityY(0);
			this->IsLoop = true;
		}
		if (this->current_state == GrayRocketRobotState::running)
		{
			this->current_state = GrayRocketRobotState::running;
			this->current_animation = running_ani;
		}
	}
}


int GrayRocketRobot::OnCollision(Entity* obj, float dt)
{
	if (Camera::GetInstance()->GetCameraFreeze() == true) {
		if (Player::GetInstance()->IsBornRocketRobot == false) {
			if (this->hp <= 0) {
				Player::GetInstance()->number_rocket_robot += 1;
				Player::GetInstance()->IsBornRocketRobot = true;
				this->IsExplode = true;
				SoundManager::GetInstance()->Play(SoundManager::SoundList::entity_explode);
			}
			if (this->GetPosition().x <= 255 && this->GetPosition().y <= 120) {
				Player::GetInstance()->IsBornRocketRobot = true;
			}
		}
	}
	return Enemy::OnCollision(obj, dt);
}

void GrayRocketRobot::Draw()
{
	Enemy::Draw();
}

BoundingBox GrayRocketRobot::GetBoundingBox()
{
	SIZE size;
	size.cx = 24;
	size.cy = 46;
	return BoundingBox(Entity::position, size, Entity::velocity.x, Entity::velocity.y);
}

bool GrayRocketRobot::IsCollisionWithGround(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = GRAY_ROCKET_ROBOT_SIZE_WIDTH;
	FootSize.cy = GRAY_ROCKET_ROBOT_FOOT_HEIGHT;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, velocity.x*dt, velocity.y*dt);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();
	if (foot.vy == 0)
	{
		for (auto item : obj)
		{
			if (item->GetTag() == Entity::Entity_Tag::wall && Checker->IsCollide(foot, BoundingBox(item->GetPosition(), item->GetSize(), 0, 0)))
				return true;
		}
		return false;
	}
	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		if (item->GetTag() == Entity::Entity_Tag::wall)
		{
			box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
			tmp = Checker->SweptAABB(foot, box2);
			if (tmp.side == CollisionSide::bottom)
			{
				position.y = item->GetPosition().y + GRAY_ROCKET_ROBOT_SIZE_HEIGHT / 2 + 4;
				return true;
			}
		}
	}
	return false;
}

GrayRocketRobot::GrayRocketRobot(D3DXVECTOR2 position_spawn, D3DXVECTOR2 position_goto, bool IsCrossed) : Enemy()
{
	this->SetTag(Entity::Entity_Tag::gray_rocket_robot);
	this->SetType(Entity::Entity_Type::enemy_type);
	this->SetVelocityY(-5.0f);
	this->SetVelocityX(0.0f);
	this->running_ani = new Animation(GrayRocketRobot::GrayRocketRobotState::running, 3);
	this->ducking_ani = new Animation(GrayRocketRobot::GrayRocketRobotState::ducking, 2);
	this->beaten_ani = new Animation(GrayRocketRobot::GrayRocketRobotState::beaten, 1);
	//
	this->running_ani->SetTime(0.1f);
	this->ducking_ani->SetTime(0.5f);
	//
	this->position = position_spawn;
	this->position_spawn = position_spawn;
	this->position_goto = position_goto;
	this->hp = GRAY_ROCKET_ROBOT_HP;
	this->IsChamDatLanDau = false;
	this->IsLoop = false;
	this->IsJumping = false;
	this->IsFire = true;
	this->IsExplode = false;
	this->IsJumpingFirst = 0;
	this->i = 0;
	this->time_explode = 0;
	this->IsLui = -1;
	this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
	this->current_state = GrayRocketRobotState::running;
	this->current_animation = running_ani;
	this->previous_state = GrayRocketRobotState::running;
}

GrayRocketRobot::~GrayRocketRobot()
{

}
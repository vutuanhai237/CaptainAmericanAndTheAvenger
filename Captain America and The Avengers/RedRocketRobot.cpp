#include "RedRocketRobot.h"
#include "Equation.h"
#include "Shield.h"
#include "FrameWork//Debug.h"
void RedRocketRobot::Update(float dt)
{
	Enemy::Update(dt);
	Player *player = Player::GetInstance();
	this->current_animation->Update(dt);
	auto keyboard = DirectInput::GetInstance();
	//for (auto item : this->rocket) {
	//	if (item->distance > DISTANCE_OUT) {
	//	//	rocket.erase(item);

	//	}
	//	else {
	//		//item->Update(dt);
	//	}
	//}
	
	// Khi không còn va chạm với mặt đất, cho phép một lần nhảy
	if (this->IsCollisionWithGround(dt) && IsChamDatLanDau == false)
	{
		IsChamDatLanDau == true;
		return;
	}
	else {
		this->SetVelocityY(RED_ROCKET_ROBOT_VELOCITY);
	}

	// Quay mặt về player
	if ((player->GetPosition().x - this->GetPosition().x > 0) && this->level != Level::clever) {
		this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
	}
	else {
		this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
	}
	// Thực hiện động tác 2s ngồi một lần 
	if (this->IsIdle && this->current_state == RedRocketRobotState::idle) {
		this->time_idle += dt;
	}
	if (this->IsDucking) {
		this->time_ducking += dt;
	}
	if (this->time_idle >= 2.0f && this->current_state == RedRocketRobotState::idle) {
		this->IsIdle = false;
		this->IsDucking = true;
		this->current_animation = this->ducking_ani;
		this->current_state = RedRocketRobot::RedRocketRobotState::ducking;
		this->time_idle = 0.0f;

	//	this->rocket[this->NumberRocket] = new RedRocket(this->position);
		//this->rocket->SetVelocityX(RED_ROCKET_VELOCITY_X);
		//// bắn tên lửa
		//this->rocket[this->NumberRocket] = new RedRocket();
		//this->rocket[this->NumberRocket]->SetPosition(this->GetPosition());
		//this->rocket[this->NumberRocket]->IsFire = true;
		//this->NumberRocket++;

	}
	if (this->time_ducking >= 2.0f && this->current_state == RedRocketRobotState::ducking) {
		this->IsDucking = false;
		this->IsIdle = true;
		this->current_animation = this->idle_ani;
		this->current_state = RedRocketRobot::RedRocketRobotState::idle;
		this->time_ducking = 0.0f;
		this->IsLocking = false;
		//this->rocket = new RedRocket(this->position);
		//this->rocket->SetVelocityX(RED_ROCKET_VELOCITY_X);
		// bắn tên lửa
		/*if (this->level != Level::clever) {
			this->rocket[this->NumberRocket] = new RedRocket();
			this->rocket[this->NumberRocket]->SetPosition(this->GetPosition());
			this->rocket[this->NumberRocket]->IsFire = true;
			this->NumberRocket++;
		}*/
	}
	

	// ngu thì đứng yên một chỗ
	if (this->level == Level::stupid) {
		this->UpdateStupidLevel(dt);
	}
	
	// bình thường thì sẽ đi tới đi lui
	if (this->level == Level::normal) {
		this->UpdateNormalLevel(dt);

	}
	// thông minh sẽ respawn tại một địa điểm, sau đi loop giữa 2 địa điểm khác
	if (this->level == Level::clever) {
		this->UpdateCleverLevel(dt);
	}

}

void RedRocketRobot::UpdateStupidLevel(float dt)
{
	return;
}

void RedRocketRobot::UpdateNormalLevel(float dt)
{
	// Xét va chạm trẻn mặt đất
	if (this->IsCollisionWithGround(dt)) {
		// Vừa va chạm vừa đang nhảy thì chuyển về ngồi
		if (this->current_state == RedRocketRobotState::jumping) {
			this->current_state = RedRocketRobotState::ducking;
		}
		// Nếu không thì ...


	}
	// Cập nhật tọa độ khi đang nhảy
	if (this->current_state == RedRocketRobotState::jumping && this->IsCollisionWithGround(dt) == false) {
		Equation *e = new Equation(
			this->position,
			D3DXVECTOR2(this->position.x + (this->GetMoveDirection() == 0 ? 1 : -1) * 30, this->position.y));
		this->SetPositionX(RED_ROCKET_ROBOT_VELOCITY_X*dt);
		this->SetPositionY(e->GetYFromX(this->GetPosition().x));
		return;
	}
	// Bắt việc shield có được ném hay không, thì nhảy để né
	if (Shield::GetInstance()->GetShieldState()->GetCurrentState() == ShieldState::NameState::ShieldAttack
		&& this->IsJumping == false && this->current_state == RedRocketRobotState::running) {
		this->IsJumping = true;
		this->current_state = RedRocketRobotState::jumping;
		return;
	}
	// Đi tới position togo, nếu đã nhảy rồi thì không đi nữa, hoặc đã đi tới điểm cần tới
	if ((position.x - position_goto.x) >= 5.0f) {
		this->SetVelocityX(RED_ROCKET_ROBOT_VELOCITY_X);
		this->current_state = RedRocketRobotState::running;
		if (this->IsJumping == true && this->current_state != RedRocketRobotState::jumping) {
			this->SetVelocityX(0);
			this->current_state = RedRocketRobotState::idle;
		}
	}
	else {
		this->SetVelocityX(0);
		this->current_state = RedRocketRobotState::idle;
	}
}

void RedRocketRobot::UpdateCleverLevel(float dt)
{
	// thông minh nhưng thực ra cũng ngu, luôn hướng về trái
	this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
	// Xét va chạm trẻn mặt đất
	if (this->IsCollisionWithGround(dt)) {
		if (this->current_state == RedRocketRobotState::jumping) {
			this->current_state = RedRocketRobotState::ducking;

		}
	}
	// Nếu bị hụt chân thì nhảy
	else {
		if (IsJumping == false) {
			this->current_state = RedRocketRobotState::jumping;
			this->IsJumping = true;
		}
	}

	// Cập nhật tọa độ khi đang nhảy
	if (this->current_state == RedRocketRobotState::jumping) {
		Equation *e = new Equation(
			this->position_spawn,
			this->position_goto);
		this->SetPositionX(RED_ROCKET_ROBOT_VELOCITY_X*dt);
		this->SetPositionY(e->GetYFromX(this->GetPosition().x));
		return;
	}

	if (abs(this->position.x - this->position_loop.x) >= 5.0f && IsLoop && IsLocking) {
		this->SetVelocityX(RED_ROCKET_ROBOT_VELOCITY_X);
		this->current_state = RedRocketRobotState::running;
		
	}
	else {
		IsLoop == false;
		IsLocking = true;
		this->current_state = RedRocketRobotState::idle;
	}

	if (abs(this->position.x - this->position_goto.x) >= 5.0f && IsLoop == false && IsLocking) {
		this->SetVelocityX(RED_ROCKET_ROBOT_VELOCITY_X);
		this->current_state = RedRocketRobotState::running;
	}
	else {
		IsLoop == true;
		IsLocking = true;
		this->current_state = RedRocketRobotState::idle;

	}

}

void RedRocketRobot::Render()
{
}

void RedRocketRobot::OnCollision()
{
}

void RedRocketRobot::SetActive(bool IsActive)
{
}

void RedRocketRobot::Draw()
{
	this->current_animation->Draw(this->position);
	if (this->GetMoveDirection()) {
		this->GetCurrentAnimation()->SetScale(1, 1);
	}
	else {
		this->GetCurrentAnimation()->SetScale(-1, 1);
	}

	//for (auto item : this->rocket)
	//	if (item != NULL) {
	//		item->Draw();
	//	}
}

<<<<<<< Updated upstream
=======
BoundingBox RedRocketRobot::GetBoundingBox()
{
	SIZE size;
	size.cx = 24;
	size.cy = 46;
	return BoundingBox(Entity::position, size, Entity::velocity.x, Entity::velocity.y);
}
>>>>>>> Stashed changes

bool RedRocketRobot::IsCollisionWithGround(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = RED_ROCKET_ROBOT_SIZE_WIDTH;
	FootSize.cy = RED_ROCKET_ROBOT_FOOT_HEIGHT;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, velocity.x*dt, velocity.y*dt);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();

	if (foot.vy == 0)
	{
		for (auto item : obj)
		{
			if (item->GetTag() == Entity::Entity_Tag::ground && Checker->IsCollide(foot, BoundingBox(item->GetPosition(), item->GetSize(), 0, 0)))
				return true;
		}
		return false;
	}

	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		if (item->GetTag() == Entity::Entity_Tag::ground)
		{
			box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
			tmp = Checker->SweptAABB(foot, box2);
			if (tmp.side == CollisionSide::bottom)
			{
				position.y = item->GetPosition().y + RED_ROCKET_ROBOT_SIZE_HEIGHT / 2;
				return true;
			}
		}
	}
	return false;
}

RedRocketRobot::RedRocketRobot() : Enemy()
{
	this->idle_ani = new Animation(RedRocketRobot::RedRocketRobotState::idle, 2);
	this->running_ani = new Animation(RedRocketRobot::RedRocketRobotState::running, 3);
	this->ducking_ani = new Animation(RedRocketRobot::RedRocketRobotState::ducking, 2);
	this->beaten_ani = new Animation(RedRocketRobot::RedRocketRobotState::beaten, 1);
	//
	this->idle_ani->SetTime(0.5);
	this->running_ani->SetTime(0.1);
	this->ducking_ani->SetTime(0.5);
	//
	this->IsChamDatLanDau = false;
	this->NumberRocket = 0;
	this->IsLoop = false;
	this->IsJumping = false;
	this->position = position_spawn;
	this->time_ducking = 0.0f;
	this->IsDucking = false;
	this->IsIdle = true;
	this->current_state = RedRocketRobotState::idle;
	this->current_animation = idle_ani;
	this->level = Level::stupid;
	this->SetVelocityY(-5.0f);
	this->SetVelocityX(0.0f);
	//this->rocket = NULL;
	//
	if (position_spawn.x > position_goto.x) {
		this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
	}
	else {
		this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);

	}
}

RedRocketRobot::RedRocketRobot(Level level, D3DXVECTOR2 position_spawn, D3DXVECTOR2 position_goto, D3DXVECTOR2 position_loop)
{
	RedRocketRobot();
	this->level = level;
	this->position_spawn = position_spawn;
	this->position_goto = position_goto;
	this->position_loop = position_loop;

}

void RedRocketRobot::UpdateFromFile()
{
	if (this->level == Level::clever) {
		this->IsLoop = true;
	}
}


RedRocketRobot::~RedRocketRobot()
{
}

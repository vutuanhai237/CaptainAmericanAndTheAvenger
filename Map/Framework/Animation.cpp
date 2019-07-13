#include "Animation.h"
#include "GameTimer.h"

Animation::Animation(int ID, int Total, int StartFrame) : Sprite(ID)
{
	TotalFrame = Total;
	CurrentFrame = StartFrame;
	width = Info.Width / Total;
	SetFrame();

	DelayTime = 1.0f / 60;
	RepeatTime = 0;
	delta = 0;
}

void Animation::SetTime(float Delay, float Repeat)
{
	DelayTime = Delay;
	RepeatTime = Repeat;
}

void Animation::Update(float dt)
{
	if (IsStop)
		return;
	delta += dt;
	if (delta >= DelayTime)
	{
		delta -= DelayTime;
		CurrentFrame++;
		if (CurrentFrame == TotalFrame)
			delta -= RepeatTime;
		if (CurrentFrame > TotalFrame)
			CurrentFrame = 1;
		SetFrame();
	}
}

void Animation::Pause(float time)
{
	delta -= time;
}

void Animation::Stop()
{
	IsStop = true;
}

void Animation::Continue()
{
	IsStop = false;
}

void Animation::SetFrame(int Frame)
{
	CurrentFrame = Frame;
	SetFrame();
}



void Animation::SetFrame()
{
	int Right = CurrentFrame * width;
	SetRect(0, Info.Height, Right - width, Right);
}

#pragma once
#include "Sprite.h"

class Animation : public Sprite
{
public:
	Animation(int ID, int TotalFrame, int StartFrame = 1); // ID Texture, Time delay between 2 Frame, Time delay when animation done
	Animation(int name, LPCWSTR Path, D3DXCOLOR TransparentColor, int TotalFrame, int StartFrame = 1); // Path *.png, Transparent Color, Time delay between 2 Frame, Time delay when animation done
	void SetTime(float DelayTime, float RepeatTime = 0.0f);
	void Update(float dt);
	void Pause(float time);
	void Stop();
	void Continue();
	void SetFrame(int Frame);
	int GetNumberCurrentFrame();

	float GetAnimationTime();
	void SetAnimationTime(float time);

	void ResetAnimation();
	int GetName();
private:

	void SetFrame();
	int width;
	float delta, RepeatTime, DelayTime;
	int CurrentFrame;
	int TotalFrame;
	float AnimationTime;
	int name;
	bool IsStop = false;
};
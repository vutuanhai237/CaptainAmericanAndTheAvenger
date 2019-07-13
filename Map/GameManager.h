#pragma once
#include <Windows.h>

class GameManager
{
public:
	static GameManager* GetInstance();
	void Init(int FPS = 60);
	int GetFPS();
	void Running();
	void Release();
private:
	GameManager() {};
	~GameManager();
	void Update(float delta);
	void Render();
	int FPS;
	float TPF;
	static GameManager* Instance;
	static float delta;

	static int TotalFrame;
	static DWORD StTime;
};
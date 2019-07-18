#include "GameManager.h"
#include "Framework/GameTimer.h"
#include "Framework/d3d.h"
#include "Framework/DirectInput.h"
#include "Framework/Texture.h"
#include "Framework/Sprite.h"
#include "SceneManager.h"
#include "Charleston.h"
#include "Player.h"
#include "Framework/Debug.h"

DWORD GameManager::StTime = GetTickCount();

GameManager* GameManager::Instance = NULL;
int GameManager::TotalFrame = 0;
float GameManager::delta = 0.0f;

GameManager* GameManager::GetInstance()
{
	if (!Instance)
		Instance = new GameManager();
	return Instance;
}

void GameManager::Init(int fps)
{
	FPS = fps;
	TPF = 1.0f / fps; // 1.0f / fps;

	Texture *texture = Texture::GetInstance();
	int ID;
	texture->Add(ID, L"Resources/Map/TitleMap.png", D3DCOLOR_ARGB(0, 0, 0, 0));

	SceneManager::GetInstance()->ReplaceScene(new Charleston());
}

int GameManager::GetFPS()
{
	return FPS;
}

void GameManager::Running()
{
	delta += GameTimer::GetInstance()->GetCounter();
	
	if (GetTickCount() - StTime > 1000)
	{
		Debug::PrintOut(L"FPS: %d\n", TotalFrame);
		TotalFrame = 0;
		StTime = GetTickCount();
	}

	if (delta >= TPF)
	{
		Update(delta);
		delta = 0;
	}
	else
	{
		Sleep((TPF - delta)*1000);
		delta = TPF;
	}

	Render();
}

void GameManager::Release()
{
	delete Instance;
}

GameManager::~GameManager()
{
	GameTimer::GetInstance()->Release();
	d3d::GetInstance()->Release();
	DirectInput::GetInstance()->Release();
	Texture::GetInstance()->Release();
	SceneManager::GetInstance()->Release();
	Player::GetInstance()->Release();
}

void GameManager::Update(float delta)
{
	DirectInput::GetInstance()->KeySnapShot(delta);
	SceneManager::GetInstance()->GetCurrentScene()->Update(delta);
}

void GameManager::Render()
{
	auto d3d = d3d::GetInstance();
	auto d3ddev = d3d->GetDevice();
	auto CurrentScene = SceneManager::GetInstance()->GetCurrentScene();
	d3d->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET, CurrentScene->GetBackcolor(), 1.0f, 0);
	if (d3ddev->BeginScene())
	{
		// something
		CurrentScene->Draw();
		d3ddev->EndScene();
		//Debug::PrintOut(L"%d\n", ++TotalFrame);
		TotalFrame++;
	}
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

#include "SceneManager.h"

SceneManager* SceneManager::Instance = NULL;

SceneManager* SceneManager::GetInstance()
{
	if (!Instance)
		Instance = new SceneManager();
	return Instance;
}

void SceneManager::Release()
{
	delete Instance;
}

Scene* SceneManager::GetCurrentScene()
{
	return CurrentScene;
}

void SceneManager::Update(float dt)
{
	CurrentScene->Update(dt);
}

void SceneManager::ReplaceScene(Scene *scene)
{
	delete CurrentScene;
	CurrentScene = scene;
}

SceneManager::~SceneManager()
{
	delete CurrentScene;
}

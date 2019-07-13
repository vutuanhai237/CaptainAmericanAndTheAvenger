#pragma once
#include "Scene.h"

class SceneManager
{
public:
	static SceneManager* GetInstance();
	void Release();

	Scene* GetCurrentScene();
	void Update(float dt);
	void ReplaceScene(Scene *scene);
private:
	SceneManager() {};
	~SceneManager();

	static SceneManager* Instance;
	Scene *CurrentScene;
};
#include "World11.h"
#include "Framework/DirectInput.h"
#include "Framework/Debug.h"

void World11::Update(float dt)
{
	auto input = DirectInput::GetInstance();
	auto cam = map->GetCameraPosition();
	if (input->KeyDown(DIK_LEFT))
		cam.x --;
	if (input->KeyDown(DIK_RIGHT))
		cam.x ++;
	if (cam != map->GetCameraPosition())
		map->SetCamera(cam);
	//Debug::PrintOut(L"%f,%f\n", cam.x, cam.y);
}

void World11::Draw()
{
	map->Draw();
}

World11::World11()
{
	map = new WorldMap(L"World11.txt", 0, 16);
}

World11::~World11()
{
	delete map;
}

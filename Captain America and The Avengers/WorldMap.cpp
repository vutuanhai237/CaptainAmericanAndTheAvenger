#include "WorldMap.h"
#include "Framework/d3d.h"
#include "Camera.h"
#include <fstream>
#include <math.h>

using namespace std;

WorldMap::WorldMap(LPCWSTR Path, int IDTitleMap) : Sprite(IDTitleMap)
{
	Init(Path);
}

WorldMap::WorldMap(LPCWSTR Path, LPCWSTR PathTitleMap) : Sprite(PathTitleMap, D3DCOLOR_XRGB(0, 0, 0))
{
	Init(Path);
}

void WorldMap::Draw(D3DCOLOR ColorMode)
{
	LPD3DXSPRITE Hander = d3d::GetInstance()->GetSpriteHander();
	D3DXMATRIX OldMatrix;
	Hander->GetTransform(&OldMatrix);

	D3DXVECTOR2 pos = Camera::GetInstance()->GetCameraPosition();
	int gStartX = (int)(pos.x / PIXEL_PER_TITLE);
	int gStartY = Height - (int)(pos.y / PIXEL_PER_TITLE) - GRID_HIGHT_BLOCK - 1;

	Hander->Begin(D3DXSPRITE_ALPHABLEND);

	int x = (PIXEL_PER_TITLE >> 1) - ((int)pos.x % PIXEL_PER_TITLE);
	for (int i = gStartX; i <= gStartX + GRID_WIDTH_BLOCK; i++)
	{
		int y = -(PIXEL_PER_TITLE >> 1) + ((int)pos.y % PIXEL_PER_TITLE);
		for (int j = gStartY; j <= gStartY + GRID_HIGHT_BLOCK; j++)
		{
			if (j < 0)
			{
				y += PIXEL_PER_TITLE;
				continue;
			}
			SetRect(Map[j][i]);
			Sprite::SetPosition(x, y);
			Hander->SetTransform(&Matrix);
			Hander->Draw(texture, &rect, NULL, NULL, ColorMode);
			y += PIXEL_PER_TITLE;
		}
		x += PIXEL_PER_TITLE;
	}

	Hander->End();

	Hander->SetTransform(&OldMatrix);
}

void WorldMap::SetRect(int ID)
{
	LONG Left = ID * PIXEL_PER_TITLE;
	Sprite::SetRect(0, PIXEL_PER_TITLE, Left, Left + PIXEL_PER_TITLE);
}

WorldMap::~WorldMap()
{
	for (int i = 0; i < Height; i++)
		delete Map[i];
	delete Map;

	for (int i = 0; i < MapObj.size(); i++)
	{
		delete MapObj[i];
	}
}

SIZE WorldMap::GetMapSize()
{
	SIZE ret;
	ret.cx = Width * PIXEL_PER_TITLE;
	ret.cy = Height * PIXEL_PER_TITLE;
	return ret;
}

vector<Entity*>* WorldMap::GetMapObj()
{
	return &MapObj;
}

void WorldMap::Init(LPCWSTR Path)
{
	fstream data(Path, ios_base::in);
	data >> Width >> Height;
	Map = new int*[Height];
	for (int i = 0; i < Height; i++)
	{
		Map[i] = new int[Width];
		for (int j = 0; j < Width; j++)
			data >> Map[i][j];
	}

	Entity *obj;
	int n, id = 0;
	data >> n;
	long top = 0, left = 0, width = 0, height = 0;
	for (int i = 0; i < n; i++)
	{
		data >> id >> left >> top >> width >> height;
		obj = new Entity();
		switch (id)
		{
		case MAPOBJ_GROUND:
			//top -= 8;
			obj->SetTag(Entity::Entity_Tag::ground);
			break;
		case MAPOBJ_WALL:
			//top -= 8;
			obj->SetTag(Entity::Entity_Tag::wall);
			break;
		case MAPOBJ_WATER:
			top -= 8;
			obj->SetTag(Entity::Entity_Tag::water);
			break;
		case MAPOBJ_ROPE:
			top -= 8;
			left += 4;
			width -= 4;
			obj->SetTag(Entity::Entity_Tag::rope);
			break;
		case MAPOBJ_SPIKE:

			obj->SetTag(Entity::Entity_Tag::spike);
			break;
		default:
			break;
		}
		obj->SetSize(width, height);
		obj->SetPosition(left + width / 2.0f, top - height / 2.0f);
		MapObj.push_back(obj);
	}
}

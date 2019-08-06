#include "Texture.h"
#include "d3d.h"

Texture* Texture::Instance = NULL;

Texture* Texture::GetInstance()
{
	if (!Instance)
		Instance = new Texture();
	return Instance;
}

HRESULT Texture::Add(int &ID, LPCWSTR path, D3DCOLOR Trans)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(path, &info);
	if (result != D3D_OK)
		return result;

	LPDIRECT3DTEXTURE9 texture;
	result = D3DXCreateTextureFromFileEx(d3d::GetInstance()->GetDevice(), path, info.Width, info.Height, 1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, Trans, &info, NULL, &texture);
	if (result != D3D_OK)
		return result;

	Textures.push_back(texture);
	Info.push_back(info);
	ID = (int)(Textures.size() - 1);

	return result;
}

LPDIRECT3DTEXTURE9 Texture::GetTexture(int ID)
{
	return Textures[ID];
}

D3DXIMAGE_INFO Texture::GetInfo(int ID)
{
	return Info[ID];
}

void Texture::Release()
{
	delete Instance;
}

Texture::~Texture()
{
	while (!Textures.empty())
	{
		LPDIRECT3DTEXTURE9 tmp = Textures.back();
		tmp->Release();
		tmp = NULL;
		Textures.pop_back();
	}
	while (!Info.empty())
		Info.pop_back();
}

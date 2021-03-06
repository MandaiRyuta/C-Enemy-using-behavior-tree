#pragma once
//インクルード
#include <crtdbg.h>
#include <d3dx9.h>
#include <unordered_map>
#include <vector>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#ifndef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#endif
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"XAudio2.lib")

#include "../DX9Object/RenderObject.h"
#include "../Input/Input.h"
#include "../Camera/camera.h"
#include "../Light/Light.h"

#define FVF_VERTEX3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
namespace Texturers
{
	const std::string Texture2D = "Resource/Texture/rupi.png";
}
struct MeshInfomation
{
	LPDIRECT3DINDEXBUFFER9 index_buffer;
	LPDIRECT3DVERTEXBUFFER9 vertex_buffer;
};

struct Textureinfomation
{
	LPDIRECT3DTEXTURE9 texture;
};

struct VERTEX3D
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DCOLOR   color;
	D3DXVECTOR2 texcoord;
};

struct Vertex2D
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
};
//DirectX9を使ったレンダリング
class CDX9Renderer
{
public:
	CDX9Renderer(){}
	~CDX9Renderer(){}
public:
	bool Init(HWND hWnd, bool bWindow, int nWindowWidth, int nWindowHeight);
	void Uninit();
	void Update();
	void Draw();
private:
	bool DX9Init(HWND hWnd, bool bWindow, int nWindowWidth, int nWindowHeight);
	void TargetObject();
private:
	std::unordered_map<std::string, MeshInfomation*> meshinfo_;
	std::unordered_map<std::string, Textureinfomation*> textureinfo_;
	std::vector<RenderObject*> rendererobject_;
	LPDIRECT3D9 pD3D_;
	LPDIRECT3DDEVICE9 device_;
	RenderObject* object;
	CCamera* camera_;
	//CLight* light_;

};
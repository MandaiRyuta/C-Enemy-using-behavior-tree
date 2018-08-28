#pragma once

#include <Windows.h>
#include <time.h>
#include <crtdbg.h>
#include <d3dx9.h>
#include <string>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#ifndef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#endif
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"XAudio2.lib")

///////////////////////////////////
//�E�B���h�E�̉�ʃT�C�Y�w��
//�Ăяo���� : windows_rect::SCREEN_WIDTH || windows_rect::SCREEN_HEIGHT
namespace wiindows_rect
{
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;
}

//�f�o�C�X���Ăяo���֐�
LPDIRECT3DDEVICE9 GetDevice();

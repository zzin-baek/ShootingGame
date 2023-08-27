
#pragma once
#pragma warning(disable: 4005)

#include <SDKDDKVER.h>

#define WIN32_LEAN_AND_MEAN

#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment (lib, "msimg32.lib")

#include <Windows.h>
#include <timeapi.h>
#pragma comment(lib, "Winmm.lib")

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <memory>
#include <algorithm>
#include <functional>

#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <unordered_map>
#include <cassert>
#include <bitset>

using namespace std;

using std::vector;

// # ����� ���� ��� ���� #
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "TempSoundManager.h"
#include "Utils.h"
#include "TimeManager.h"

//using namespace MY_UTILS;
// # �̱��� #
#define RND				RandomFunction::getSingleton()
#define KEYMANAGER		KeyManager::getSingleton()
#define IMAGEMANAGER	ImageManager::getSingleton()
#define TIMEMANAGER		TimeManager::getSingleton()
#define SOUNDMANAGER	TempSoundManager::getSingleton()

#define WINSTART_X		400
#define WINSTART_Y		100
#define WINSIZE_X		560
#define WINSIZE_Y		800
// WS_CAPTION: Ÿ��Ʋ �ٸ� ������ ���� �ɼ�
#define WINSTYLE		WS_CAPTION | WS_SYSMENU
#define WINNAME			(LPTSTR)(TEXT("ShootingGame"))

// # ��ũ�� �Լ� # (Ŭ�������� ���� �Ҵ�� �κ� ����)
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[](p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

extern HINSTANCE		_hInstance;
extern HWND				_hWnd;
extern POINT			_ptMouse;


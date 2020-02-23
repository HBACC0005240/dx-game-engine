#pragma once
#include <Windows.h>
#include <string>
#include <tchar.h> //swprintf_s
#include "Exception.h"

#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")//d3d¡¥Ω”ø‚
#pragma comment(lib,"winmm.lib") //timeGetTime()

#include "GTime.h"


#define CALL  __stdcall

enum BUTTON_KEY
{
    L_BUTTON_DOWN = 0,
    L_BUTTON_UP = 1,
    R_BUTTON_DOWN = 2,
    R_BUTTON_UP = 3,

    KB_DOWN = 4,
    KB_UP = 5,
};
//=============================================================================
//
// メイン処理[main.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800)//

//=============================================================================
//インクルード
//=============================================================================
#include<windows.h>
#include"d3dx9.h"
#include "dinput.h"
#include "xaudio2.h"

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")//システム時間の取得に必要
#pragma comment(lib,"dinput8.lib")//

//=============================================================================
//マクロ定義
//=============================================================================
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE | D3DFVF_TEX1)

//=============================================================================
//前方宣言
//=============================================================================
class CRenderer;

#ifdef _DEBUG
int GetFPS(void);
#endif
#endif

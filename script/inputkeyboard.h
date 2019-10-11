
//=============================================================================
//
// キーボード入力処理 [inputkeyboard.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
#define DIRECTINPUT_VERSION (0x0800)

#include"manager.h"
#include "scene.h"
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	NUM_KEY_MAX			(256)	// キーの最大数
 
//=============================================================================
//クラス
//=============================================================================

class CInputkeyborad : public CInput
{
public:
	CInputkeyborad();
	virtual ~CInputkeyborad();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual bool GetKeyboardPress(int Key);
	virtual bool GetKeyboardTrigger(int Key);
	virtual bool GetKeyboardRelease(int Key);

private: 

	BYTE g_aKeyState[NUM_KEY_MAX];//
	BYTE g_aKeyStateTrigger[256];//単発
	BYTE g_aKeyStateRelease[256];//溜め
	LPDIRECTINPUTDEVICE8 m_pDevice;


};
#endif
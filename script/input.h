
//=============================================================================
//
// 入力処理[input.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#define DIRECTINPUT_VERSION (0x0800)

#include"manager.h"
#include "scene.h"
//=============================================================================
//クラス
//=============================================================================

class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
protected:
	static LPDIRECTINPUT8 m_pInput;
};
#endif
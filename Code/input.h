//=============================================================================
//
// ���͏���[input.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#define DIRECTINPUT_VERSION (0x0800)

//=============================================================================
//�C���N���[�h
//=============================================================================
#include"manager.h"
#include "scene.h"

//=============================================================================
//�L�[���͂̃N���X
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

//=============================================================================
//
// �L�[�{�[�h���͏��� [inputkeyboard.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
#define DIRECTINPUT_VERSION (0x0800)

#include"manager.h"
#include "scene.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
 
//=============================================================================
//�N���X
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
	BYTE g_aKeyStateTrigger[256];//�P��
	BYTE g_aKeyStateRelease[256];//����
	LPDIRECTINPUTDEVICE8 m_pDevice;


};
#endif
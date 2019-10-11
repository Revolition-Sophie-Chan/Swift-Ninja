//=============================================================================
//
// �Q�[���p�b�h���� [gamepad.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define NUM_JOYPAD_MAX		(1)		// �p�b�h�ő吔
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define JOY_MAX_RANGE		(32768)	// �p�b�h�L���͈�

//=============================================================================
//�N���X��`
//=============================================================================
class CGamepad : public CInput
{
public:

	//�}�N���@���ł��g��

	// �L�[�̎��
	typedef enum
	{
		JOYPADKEY_X = 0,			// [0] �w�{�^��
		JOYPADKEY_Y,				// [1] �x�{�^��
		JOYPADKEY_A,				// [2] �`�{�^��
		JOYPADKEY_B,				// [3] �a�{�^��
		JOYPADKEY_LEFT_SHOULDER,	// [4] ����O�{�^��
		JOYPADKEY_RIGHT_SHOULDER,	// [5] �E��O�{�^��
		JOYPADKEY_LEFT_TRIGGER,		// [6] ���g���K�[
		JOYPADKEY_RIGHT_TRIGGER,	// [7] �E�g���K�[
		JOYPADKEY_LEFT_THUMB,		// [8] ���X�e�B�b�N�{�^��
		JOYPADKEY_RIGHT_THUMB,		// [9] �E�X�e�B�b�N�{�^��
		JOYPADKEY_BACK,				// [10] �o�b�N�{�^��
		JOYPADKEY_START,			// [11] �X�^�[�g�{�^��
		JOYPADKEY_LEFT,				// [12] �����L�[[��]
		JOYPADKEY_RIGHT,			// [13] �����L�[[�E]
		JOYPADKEY_UP,				// [14] �����L�[[��]
		JOYPADKEY_DOWN,				// [15] �����L�[[��]
		JOYPADKEY_MAX
	} JOYPADKEY;

	CGamepad();
	~CGamepad();


	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nIDPad, JOYPADKEY key);
	bool GetTrigger(int nIDPad, JOYPADKEY key);
	bool GetRelease(int nIDPad, JOYPADKEY key);
	void GetStickLeft(int nIDPad, float *pValueH, float *pValueV);
	void GetStickRight(int nIDPad, float *pValueH, float *pValueV);

private:
	static LPDIRECTINPUTDEVICE8	m_apDIDevGamepad[NUM_JOYPAD_MAX];						// IDirectInputDevice8�ւ̃|�C���^(�W���C�p�b�h)
	LPDIRECTINPUTEFFECT		m_pDIEffect = NULL;											// �U���p
	DIJOYSTATE2				m_aGamepadState[NUM_JOYPAD_MAX];							// �W���C�p�b�h��Ԃ��󂯎�郏�[�N
	bool					m_aKeyStateGamepad[NUM_JOYPAD_MAX][NUM_KEY_MAX];			// �W���C�p�b�h�̉�����Ԃ�ێ����郏�[�N
	bool					m_aKeyStateTriggerGamepad[NUM_JOYPAD_MAX][NUM_KEY_MAX];		// �W���C�p�b�h�̃g���K�[��Ԃ�ێ����郏�[�N
	bool					m_aKeyStateReleaseGamepad[NUM_JOYPAD_MAX][NUM_KEY_MAX];		// �W���C�p�b�h�̃����[�X��Ԃ�ێ����郏�[�N
	D3DXVECTOR3				m_aKeyStateAxis[NUM_JOYPAD_MAX];
	DWORD					m_dwNumForceFeedbackAxis;									//�t�H�[�X�t�B�[�h�o�b�N�i�U���j

	static int				m_nCntPad;

	void SetKeyStateGamepad(int nIDPad);
	int GetTriggerLeft(int nIDPad);
	int GetTriggerRight(int nIDPad);
	static BOOL CALLBACK EnumJoyCallbackGamepad(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);
	static BOOL CALLBACK EnumAxesCallbackGamepad(const DIDEVICEOBJECTINSTANCE  *pdidoi, VOID* pvRef);

};

#endif
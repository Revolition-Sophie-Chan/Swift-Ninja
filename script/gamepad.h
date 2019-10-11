//=============================================================================
//
// ゲームパッド処理 [gamepad.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define NUM_JOYPAD_MAX		(1)		// パッド最大数
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define JOY_MAX_RANGE		(32768)	// パッド有効範囲

//=============================================================================
//クラス定義
//=============================================================================
class CGamepad : public CInput
{
public:

	//マクロ　他でも使う

	// キーの種類
	typedef enum
	{
		JOYPADKEY_X = 0,			// [0] Ｘボタン
		JOYPADKEY_Y,				// [1] Ｙボタン
		JOYPADKEY_A,				// [2] Ａボタン
		JOYPADKEY_B,				// [3] Ｂボタン
		JOYPADKEY_LEFT_SHOULDER,	// [4] 左手前ボタン
		JOYPADKEY_RIGHT_SHOULDER,	// [5] 右手前ボタン
		JOYPADKEY_LEFT_TRIGGER,		// [6] 左トリガー
		JOYPADKEY_RIGHT_TRIGGER,	// [7] 右トリガー
		JOYPADKEY_LEFT_THUMB,		// [8] 左スティックボタン
		JOYPADKEY_RIGHT_THUMB,		// [9] 右スティックボタン
		JOYPADKEY_BACK,				// [10] バックボタン
		JOYPADKEY_START,			// [11] スタートボタン
		JOYPADKEY_LEFT,				// [12] 方向キー[左]
		JOYPADKEY_RIGHT,			// [13] 方向キー[右]
		JOYPADKEY_UP,				// [14] 方向キー[上]
		JOYPADKEY_DOWN,				// [15] 方向キー[下]
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
	static LPDIRECTINPUTDEVICE8	m_apDIDevGamepad[NUM_JOYPAD_MAX];						// IDirectInputDevice8へのポインタ(ジョイパッド)
	LPDIRECTINPUTEFFECT		m_pDIEffect = NULL;											// 振動用
	DIJOYSTATE2				m_aGamepadState[NUM_JOYPAD_MAX];							// ジョイパッド状態を受け取るワーク
	bool					m_aKeyStateGamepad[NUM_JOYPAD_MAX][NUM_KEY_MAX];			// ジョイパッドの押下状態を保持するワーク
	bool					m_aKeyStateTriggerGamepad[NUM_JOYPAD_MAX][NUM_KEY_MAX];		// ジョイパッドのトリガー状態を保持するワーク
	bool					m_aKeyStateReleaseGamepad[NUM_JOYPAD_MAX][NUM_KEY_MAX];		// ジョイパッドのリリース状態を保持するワーク
	D3DXVECTOR3				m_aKeyStateAxis[NUM_JOYPAD_MAX];
	DWORD					m_dwNumForceFeedbackAxis;									//フォースフィードバック（振動）

	static int				m_nCntPad;

	void SetKeyStateGamepad(int nIDPad);
	int GetTriggerLeft(int nIDPad);
	int GetTriggerRight(int nIDPad);
	static BOOL CALLBACK EnumJoyCallbackGamepad(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);
	static BOOL CALLBACK EnumAxesCallbackGamepad(const DIDEVICEOBJECTINSTANCE  *pdidoi, VOID* pvRef);

};

#endif
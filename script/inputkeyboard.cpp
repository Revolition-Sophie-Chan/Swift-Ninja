//=============================================================================
//
// キーボード入力処理 [inputkeyboard.cpp]
// Author : tanaka rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include"inputkeyboard.h"
#include"main.h"
#include"input.h"


//============================================================================================
//コンストラクタ
//============================================================================================
CInputkeyborad::CInputkeyborad()
{
}
//============================================================================================
//デストラクタ
//============================================================================================
CInputkeyborad::~CInputkeyborad()
{
}
 //=============================================================================
 // キーボードの初期化
 //=============================================================================
HRESULT CInputkeyborad::Init(HINSTANCE hInstance, HWND hWnd)
{

	CInput::Init(hInstance, hWnd);

	// 入力デバイス（キーボード）の作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void CInputkeyborad::Uninit(void)
{
	// 入力デバイス(キーボード)の開放
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();//キーのアクセス権
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void CInputkeyborad::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//
	int nCntkey;

	// デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			g_aKeyStateTrigger[nCntkey] = (g_aKeyState[nCntkey] ^ aKeyState[nCntkey]) & aKeyState[nCntkey];
			g_aKeyState[nCntkey] = aKeyState[nCntkey];//
		}
	}
	else
	{
		m_pDevice->Acquire();//
	}
}

//=============================================================================
//　プレス処理
//=============================================================================
bool CInputkeyborad::GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// トリガー処理
//=============================================================================
bool CInputkeyborad::GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=============================================================================
// トリガー処理
//=============================================================================
bool CInputkeyborad::GetKeyboardRelease(int nKey)
{
	return(g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

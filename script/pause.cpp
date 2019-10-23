//=============================================================================
//
// ポーズの処理[Pause.cpp]
// Author：tanaka rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "pause.h"
#include "bg.h"
#include "inputkeyboard.h"
#include "manager.h"
#include "fade.h"
#include "player.h"
#include "texture.h"
#include "gamepad.h"
#include "load.h"

//=============================================================================
//メンバ変数の初期化
//=============================================================================
CPause::PAUSE_STATE CPause::PauseState = PAUSESTATE_CONTINUE;

//=============================================================================
//マクロ定義
//=============================================================================
#define SELECT_CHOOSE					(D3DXCOLOR(0.5f,1.0f,0.5f,1.0f))
#define SELECT_NOT_CHOOSE				(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f))

//=============================================================================
//コンストラクタ
//=============================================================================
CPause::CPause()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
void CPause::Init(void)
{
	m_pPauseTexture[0] = CTexture::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f), 250, 125, CTexture::TYPE_PAUSECONTINUE);
	m_pPauseTexture[1] = CTexture::Create(D3DXVECTOR3(640.0f, 400.0f, 0.0f), 250, 125, CTexture::TYPE_PAUSERETRY);
	m_pPauseTexture[2] = CTexture::Create(D3DXVECTOR3(640.0f, 450.0f, 0.0f), 250, 125, CTexture::TYPE_PAUSEQUIT);

	for (int nCnt = 0; nCnt < PAUSESELECT; nCnt++)
	{
		m_pPauseTexture[nCnt]->SetColor(SELECT_NOT_CHOOSE);
	}
	bSelect = true;
	PauseState = PAUSESTATE_CONTINUE;
	StateCount = 0;
	m_pPauseTexture[0]->SetColor(SELECT_CHOOSE);
}
//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CPause::Uninit(void)
{
	CTexture::Unload();
}
//=============================================================================
// polygon更新処理
//=============================================================================
void CPause::Update(void)
{
	CGamepad *pGamePad = CManager::GetGamePad();
	// キーボードの取得
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	m_pPauseTexture[PauseState]->SetColor(SELECT_NOT_CHOOSE);

	switch (StateCount)
	{
	case 0:
		PauseState = PAUSESTATE_CONTINUE;
		break;
	case 1:
		PauseState = PAUSESTATE_RETRY;
		break;
	case 2:
		PauseState = PAUSESTATE_QUIT;
		break;
	}
	float Stick_X, Stick_Y;
	pGamePad->GetStickLeft(0, &Stick_X, &Stick_Y);
	if (bSelect == false)
	{
		if (Stick_Y == 0)
		{
			bSelect = true;
		}
}
	if (bSelect == true)
	{
		if (pInputKeyborad->GetKeyboardTrigger(DIK_S) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_DOWN))
		{
			if (StateCount == 2)
			{
				StateCount = 0;
			}
			else
			{
				StateCount += 1;
			}
		}
		else if (pInputKeyborad->GetKeyboardTrigger(DIK_W) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_UP))
		{
			if (StateCount == 0)
			{
				StateCount = 2;
			}
			else
			{
				StateCount -= 1;
			}
		}
		else if (Stick_Y <= -3000)
		{
			bSelect = false;
			if (StateCount == 2)
			{
				StateCount = 0;
			}
			else
			{
				StateCount += 1;
			}
		}
		else if (Stick_Y >= 3000)
		{

			bSelect = false;
			if (StateCount == 0)
			{
				StateCount = 2;
			}
			else
			{
				StateCount -= 1;
			}
		}
	}

	m_pPauseTexture[PauseState]->SetColor(SELECT_CHOOSE);

	if (pInputKeyborad->GetKeyboardPress(DIK_RETURN) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_B) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START))
	{
		if (PauseState == PAUSESTATE_CONTINUE)
		{
			//ゲームに戻るとき
			CManager::SetPause(CManager::MODE_GAME);
		}
		if (PauseState == PAUSESTATE_RETRY)
		{
			CFade::SetFade(CManager::MODE_GAME);
		}
		if (PauseState == PAUSESTATE_QUIT)
		{
			CFade::SetFade(CManager::MODE_TITLE);
		}
	}
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CPause::Draw(void)
{
}


//=============================================================================
// ポリゴンの描画
//=============================================================================
void CPause::SetDraw(bool bDraw)
{
	m_pPauseTexture[0]->m_bDraw = bDraw;
	m_pPauseTexture[1]->m_bDraw = bDraw;
	m_pPauseTexture[2]->m_bDraw = bDraw;
}

//=============================================================================
// クリエイト
//=============================================================================
CPause * CPause::Create()
{
	CPause *pPause;
	pPause = new CPause;
	pPause->Init();
	return pPause;
}
//=============================================================================
// 取得
//=============================================================================
CPause::PAUSE_STATE CPause::GetPauseState()
{
	return PauseState;
}
//=============================================================================
// 設定
//=============================================================================
void CPause::SetPauseState(PAUSE_STATE state)
{
	PauseState = state;
}

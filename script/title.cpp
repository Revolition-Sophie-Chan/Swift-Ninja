//=============================================================================
//
// タイトルの処理[Title.cpp]
// Author：tanaka rikiya
//
//=============================================================================
//インクルードファイル
#include "title.h"
#include "bg.h"
#include "inputkeyboard.h"
#include "manager.h"
#include "fade.h"
#include "player.h"
#include "texture.h"
#include "gamepad.h"
#include "load.h"

CLoad *CTitle::m_Load = NULL;

//=============================================================================
//マクロ定義
//=============================================================================
#define FADE_COUNT (600)

//=============================================================================
//こンストラクタ
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
void CTitle::Init(void)
{
	CTexture::Load();
	CTexture::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f), 500, 250, CTexture::TYPE_LOGO);
	CTexture::Create(D3DXVECTOR3(640.0f, 600.0f, 0.0f), 240, 90, CTexture::TYPE_ENTER);
	FadeCount = 0;
}
//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	CTexture::Unload();
}
//=============================================================================
// polygon更新処理
//=============================================================================
void CTitle::Update(void)
{
	FadeCount++;
	CGamepad *pGamePad = CManager::GetGamePad();
	// キーボードの取得
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	if (pInputKeyborad->GetKeyboardTrigger(DIK_RETURN) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START) ||
		pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_B) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_A) && CManager::GetMode() != CManager::MODE_GAME)
	{
		CFade::SetFade(CManager::MODE_TUTORIAL);
	}
	else if (FadeCount >= FADE_COUNT)
	{
		m_Load->LoadData();
		CFade::SetFade(CManager::MODE_RANKING);
		CPlayer::bRankScore = false;
		FadeCount = 0;
	}
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CTitle::Draw(void)
{
}
//=============================================================================
// クリエイト
//=============================================================================
CTitle * CTitle::Create()
{
	CTitle *pTitle;
	pTitle = new CTitle;
	pTitle->Init();
	return pTitle;
}

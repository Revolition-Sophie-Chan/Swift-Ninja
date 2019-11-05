//=============================================================================
//
// タイトルの処理[Title.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "title.h"
#include "inputkeyboard.h"
#include "manager.h"
#include "fade.h"
#include "player.h"
#include "texture.h"
#include "gamepad.h"
#include "load.h"
#include "sound.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
CLoad *CTitle::m_Load = NULL;

//=============================================================================
//マクロ定義
//=============================================================================
#define FADE_COUNT (600)

//=============================================================================
//コンストラクタ
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
//生成処理
//=============================================================================
CTitle * CTitle::Create()
{
	CTitle *pTitle;
	pTitle = new CTitle;
	pTitle->Init();
	return pTitle;
}

//=============================================================================
//初期化
//=============================================================================
void CTitle::Init(void)
{
	CTexture::Load();
	CTexture::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f), 500, 250, CTexture::TYPE_LOGO);
	CTexture::Create(D3DXVECTOR3(640.0f, 600.0f, 0.0f), 240, 90, CTexture::TYPE_ENTER);
	FadeCount = 0;
}

//=============================================================================
//終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	CTexture::Unload();
}

//=============================================================================
//更新処理
//=============================================================================
void CTitle::Update(void)
{
	// ゲームパッドの取得
	CGamepad *pGamePad = CManager::GetGamePad();

	// キーボードの取得
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	//サウンドの取得
	CSound *pSound = CManager::GetSound();

	FadeCount++;
	if (pInputKeyborad->GetKeyboardTrigger(DIK_RETURN) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START) ||
		pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_B) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_A) && CManager::GetMode() != CManager::MODE_GAME)
	{
		if (CFade::GetFade() == CManager::MODE_TITLE)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_DECISION);
		}
		CFade::SetFade(CManager::MODE_TUTORIAL);
	}
	else if (FadeCount >= FADE_COUNT)
	{//一定時間でランキングに遷移
		m_Load->LoadData();
		CFade::SetFade(CManager::MODE_RANKING);
		CPlayer::bRankScore = false;
		FadeCount = 0;
	}
}

//=============================================================================
//描画
//=============================================================================
void CTitle::Draw(void)
{
}

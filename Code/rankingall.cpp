//=============================================================================
//
// ランキング処理 [rankingall.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include <stdio.h>
#include "load.h"
#include "ranking.h"
#include "fade.h"
#include "score.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "rankingall.h"
#include "texture.h"
#include "gamepad.h"
#include "sound.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
CRanking *CRankingAll::pRanking = NULL;

//=============================================================================
//マクロ定義
//=============================================================================
#define FADE_COUNT (600)

//=============================================================================
//コンストラクタ
//=============================================================================
CRankingAll::CRankingAll()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CRankingAll::~CRankingAll()
{
}

//=============================================================================
//生成処理
//=============================================================================
CRankingAll * CRankingAll::Create()
{
	CRankingAll *pRankingAll;
	pRankingAll = new CRankingAll();
	pRankingAll->Init();
	return pRankingAll;
}

//=============================================================================
//初期化
//=============================================================================
HRESULT CRankingAll::Init(void)
{
	CNumber::Load();
	CRanking::Create();
	CTexture::Create(D3DXVECTOR3(640.0f, 600.0f, 0.0f), 240, 80, CTexture::TYPE_ENTER);
	FadeCount = 0;
	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void CRankingAll::Uninit(void)
{
	CTexture::Unload();
	CNumber::Unload();
}

//=============================================================================
//更新
//=============================================================================
void CRankingAll::Update(void)
{
	CInputkeyborad *pKeyboard = CManager::GetInputKeyboard();
	CGamepad *pGamePad = CManager::GetGamePad();
	CSound *pSound = CManager::GetSound();

	CPlayer *pPlayer = CPlayer::GetPlayer();

	if (CPlayer::bRankScore == false)
	{//タイトルから遷移したとき
		FadeCount++;
		if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START) ||
			FadeCount >= FADE_COUNT)
		{
			if (CFade::GetFade() == CManager::MODE_RANKING)
			{
				pSound->PlaySound(CSound::SOUND_LABEL_SE_DECISION);
			}
			CFade::SetFade(CManager::MODE_TITLE);
			FadeCount = 0;
		}
	}
	else
	{//ゲームから遷移したときには時間で自動遷移しない
		if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START))
		{
			if (CFade::GetFade() == CManager::MODE_RANKING)
			{
				pSound->PlaySound(CSound::SOUND_LABEL_SE_DECISION);
			}
			CFade::SetFade(CManager::MODE_TITLE);
		}
	}
}

//=============================================================================
//描画
//=============================================================================
void CRankingAll::Draw(void)
{
}

//=============================================================================
//
// �����L���O���� [rankingall.cpp]
// Author : tanaka rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include <stdio.h>
#include "load.h"
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "RankingAll.h"
#include "ranking.h"
#include "texture.h"
#include "gamepad.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
CRanking *CRankingAll::pRanking = NULL;

//=============================================================================
//�}�N����`
//=============================================================================
#define FADE_COUNT (600)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRankingAll::CRankingAll()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRankingAll::~CRankingAll()
{
}

//=============================================================================
// ������
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
// �I��
//=============================================================================
void CRankingAll::Uninit(void)
{
	CTexture::Unload();
	CNumber::Unload();
}

//=============================================================================
// �X�V
//=============================================================================
void CRankingAll::Update(void)
{
	CInputkeyborad *pKeyboard = CManager::GetInputKeyboard();
	CGamepad *pGamePad = CManager::GetGamePad();

	CPlayer *pPlayer = CPlayer::GetPlayer();
	if (CPlayer::bRankScore == false)
	{//�^�C�g������J�ڂ����Ƃ�
		FadeCount++;
		if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START) ||
			FadeCount >= FADE_COUNT)
		{
			CFade::SetFade(CManager::MODE_TITLE);
			FadeCount = 0;
		}
	}
	else
	{//�Q�[������J�ڂ����Ƃ�
		if (pKeyboard->GetKeyboardTrigger(DIK_RETURN) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START))
		{
			CFade::SetFade(CManager::MODE_TITLE);

		}
	}

}

//=============================================================================
// �`��
//=============================================================================
void CRankingAll::Draw(void)
{
}

//=============================================================================
// �N���G�C�g
//=============================================================================
CRankingAll * CRankingAll::Create()
{
	CRankingAll *pRankingAll;

	pRankingAll = new CRankingAll();

	pRankingAll->Init();

	return pRankingAll;
}

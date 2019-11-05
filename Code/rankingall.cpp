//=============================================================================
//
// �����L���O���� [rankingall.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
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
//�ÓI�����o�ϐ��̏�����
//=============================================================================
CRanking *CRankingAll::pRanking = NULL;

//=============================================================================
//�}�N����`
//=============================================================================
#define FADE_COUNT (600)

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CRankingAll::CRankingAll()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CRankingAll::~CRankingAll()
{
}

//=============================================================================
//��������
//=============================================================================
CRankingAll * CRankingAll::Create()
{
	CRankingAll *pRankingAll;
	pRankingAll = new CRankingAll();
	pRankingAll->Init();
	return pRankingAll;
}

//=============================================================================
//������
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
//�I��
//=============================================================================
void CRankingAll::Uninit(void)
{
	CTexture::Unload();
	CNumber::Unload();
}

//=============================================================================
//�X�V
//=============================================================================
void CRankingAll::Update(void)
{
	CInputkeyborad *pKeyboard = CManager::GetInputKeyboard();
	CGamepad *pGamePad = CManager::GetGamePad();
	CSound *pSound = CManager::GetSound();

	CPlayer *pPlayer = CPlayer::GetPlayer();

	if (CPlayer::bRankScore == false)
	{//�^�C�g������J�ڂ����Ƃ�
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
	{//�Q�[������J�ڂ����Ƃ��ɂ͎��ԂŎ����J�ڂ��Ȃ�
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
//�`��
//=============================================================================
void CRankingAll::Draw(void)
{
}

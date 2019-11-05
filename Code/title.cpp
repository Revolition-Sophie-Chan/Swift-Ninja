//=============================================================================
//
// �^�C�g���̏���[Title.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
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
//�ÓI�����o�ϐ��̏�����
//=============================================================================
CLoad *CTitle::m_Load = NULL;

//=============================================================================
//�}�N����`
//=============================================================================
#define FADE_COUNT (600)

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
//��������
//=============================================================================
CTitle * CTitle::Create()
{
	CTitle *pTitle;
	pTitle = new CTitle;
	pTitle->Init();
	return pTitle;
}

//=============================================================================
//������
//=============================================================================
void CTitle::Init(void)
{
	CTexture::Load();
	CTexture::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f), 500, 250, CTexture::TYPE_LOGO);
	CTexture::Create(D3DXVECTOR3(640.0f, 600.0f, 0.0f), 240, 90, CTexture::TYPE_ENTER);
	FadeCount = 0;
}

//=============================================================================
//�I������
//=============================================================================
void CTitle::Uninit(void)
{
	CTexture::Unload();
}

//=============================================================================
//�X�V����
//=============================================================================
void CTitle::Update(void)
{
	// �Q�[���p�b�h�̎擾
	CGamepad *pGamePad = CManager::GetGamePad();

	// �L�[�{�[�h�̎擾
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	//�T�E���h�̎擾
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
	{//��莞�ԂŃ����L���O�ɑJ��
		m_Load->LoadData();
		CFade::SetFade(CManager::MODE_RANKING);
		CPlayer::bRankScore = false;
		FadeCount = 0;
	}
}

//=============================================================================
//�`��
//=============================================================================
void CTitle::Draw(void)
{
}

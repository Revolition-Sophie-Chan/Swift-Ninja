//=============================================================================
//
// �^�C�g���̏���[Title.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================
//�C���N���[�h�t�@�C��
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
//�}�N����`
//=============================================================================
#define FADE_COUNT (600)

//=============================================================================
//�����X�g���N�^
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
// �|���S���̏�����
//=============================================================================
void CTitle::Init(void)
{
	CTexture::Load();
	CTexture::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f), 500, 250, CTexture::TYPE_LOGO);
	CTexture::Create(D3DXVECTOR3(640.0f, 600.0f, 0.0f), 240, 90, CTexture::TYPE_ENTER);
	FadeCount = 0;
}
//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTitle::Uninit(void)
{
	CTexture::Unload();
}
//=============================================================================
// polygon�X�V����
//=============================================================================
void CTitle::Update(void)
{
	FadeCount++;
	CGamepad *pGamePad = CManager::GetGamePad();
	// �L�[�{�[�h�̎擾
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
// �|���S���̕`��
//=============================================================================
void CTitle::Draw(void)
{
}
//=============================================================================
// �N���G�C�g
//=============================================================================
CTitle * CTitle::Create()
{
	CTitle *pTitle;
	pTitle = new CTitle;
	pTitle->Init();
	return pTitle;
}
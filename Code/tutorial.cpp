//=============================================================================
//
// �`���[�g���A���̏���[tutorial.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "Tutorial.h"
#include "player.h"
#include "inputkeyboard.h"
#include "bg.h"
#include "effect.h"
#include "explosion.h"
#include "pointer.h"
#include "icon.h"
#include "fade.h"
#include "score.h"
#include "camera.h"
#include "gauge.h"
#include "texture.h"
#include "time.h"
#include "gamepad.h"
#include "here.h"
#include "sound.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// ��������
//=============================================================================
CTutorial * CTutorial::Create()
{
	CTutorial *pTutorial;
	pTutorial = new CTutorial;
	pTutorial->Init();
	return pTutorial;
}

//=============================================================================
// ����������
//=============================================================================
void CTutorial::Init(void)
{
	TutorialState = TUTORIALSTATE_NORMAL;

	//�e�N�X�`�������[�h
	LoadAll();

	CPlayer::Create(D3DXVECTOR3(105.0f, 200.0f, 0.0f),6);
	CPointer::Create();
	CIcon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 60, 0.0f));
	CBg::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	CScore::Create(0);
	CHere::Create();
	CTime::Create(100);

	//�摜���N���G�C�g
	CTexture::Create(D3DXVECTOR3(1225.0f, 685.0f, 0.0f), 70, 50, CTexture::TYPE_KO);
	CTexture::Create(D3DXVECTOR3(30.0f, 660.0f, 0.0f), 80, 50, CTexture::TYPE_HP);
	CTexture::Create(D3DXVECTOR3(360.0f, 660.0f, 0.0f), 83, 60, CTexture::TYPE_TIME);
	CTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 83.0f, 670.0f, 0.0f), 88, 80, CTexture::TYPE_FEVER);
	CTexture::Create(D3DXVECTOR3(780.0f, 105.0f, 0.0f), 560.0f, 256.0f, CTexture::TYPE_TUTORIAL00);
	CTexture::Create(D3DXVECTOR3(780.1f, 310.0f, 0.0f), 560.0f, 256.0f, CTexture::TYPE_TUTORIAL01);
	CTexture::Create(D3DXVECTOR3(780.1f, 515.0f, 0.0f), 560.0f, 256.0f, CTexture::TYPE_TUTORIAL02);
	CTexture::Create(D3DXVECTOR3(140.0f, 125.0f, 0.0f), 150.0f, 75.0f, CTexture::TYPE_START);

	//�Q�[�W���N���G�C�g
	CGauge::Create(D3DXVECTOR3(770.0f, 635.0f, 0.0f), D3DXCOLOR(0.2f, 0.0f, 0.0f, 1.0f), 10, 50, CGauge::UITYPE_FEVERMAX);
	CGauge::Create(D3DXVECTOR3(770.0f,635.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 50, CGauge::UITYPE_FEVER);
	CGauge::Create(D3DXVECTOR3(60.0f, 635.0f, 0.0f), D3DXCOLOR(0.2f, 0.0f, 0.0f, 1.0f), 40, 50, CGauge::UITYPE_HPMAX);
	CGauge::Create(D3DXVECTOR3(60.0f, 635.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, 50, CGauge::UITYPE_HP);

}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	CBg			::Unload();
	CIcon		::Unload();
	CHere		::Unload();
	CGauge		::Unload();
	CPlayer		::Unload();
	CNumber		::Unload();
	CEffect		::Unload();
	CPointer	::Unload();
	CTexture	::Unload();
	CExplosion	::Unload();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
{
	// �v���C���[�̎擾
	CPlayer *pPlayer = CPlayer::GetPlayer();

	// �J�����̎擾
	CCamera *pCamera = CCamera::GetCamera();

	// �Q�[���p�b�h�̎擾
	CGamepad *pGamePad = CManager::GetGamePad();

	// �L�[�{�[�h�̎擾
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	// �T�E���h�̎擾
	CSound *pSound = CManager::GetSound();

	if (pInputKeyborad->GetKeyboardTrigger(DIK_RETURN) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START))
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_DECISION);
		CFade::SetFade(CManager::MODE_GAME);
	}

}
//=============================================================================
// �т傤������
//=============================================================================
void CTutorial::Draw(void)
{

}

//=============================================================================
// �S�ă��[�h
//=============================================================================
void CTutorial::LoadAll(void)
{
	CBg			::Load();
	CHere		::Load();
	CIcon		::Load();
	CGauge		::Load();
	CEffect		::Load();
	CPlayer		::Load();
	CNumber		::Load();
	CPointer	::Load();
	CTexture	::Load();
	CExplosion	::Load();
}

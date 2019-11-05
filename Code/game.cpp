//=============================================================================
//
// �Q�[���{�҂̏���[game.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "game.h"
#include "player.h"
#include "inputkeyboard.h"
#include "bg.h"
#include "effect.h"
#include "enemy.h"
#include "explosion.h"
#include "pointer.h"
#include "icon.h"
#include "fade.h"
#include "hit.h"
#include "score.h"
#include "camera.h"
#include  "gauge.h"
#include "load.h"
#include "save.h"
#include "texture.h"
#include "time.h"
#include "gamepad.h"
#include "here.h"
#include "sound.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
CGame *CGame::m_pGame = NULL;

//=============================================================================
//�}�N����`
//=============================================================================
#define SHAKE_COUNT (20)

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
//��������
//=============================================================================
CGame * CGame::Create()
{
	CGame *pGame;
	pGame = new CGame;
	pGame->Init();
	return pGame;
}

//=============================================================================
//����������
//=============================================================================
void CGame::Init(void)
{
	nCountGame	 = 0;
	nCountTime	 = 0;
	nCountDamage = 0;
	nCountCamera = 0;

	//�e�N�X�`�������[�h
	 LoadAll();

	CBg::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	CSave::Create();
	CLoad::Create();
	CCamera::Create();
	CPlayer::Create(D3DXVECTOR3(505.0f, 200.0f, 0.0f),6);
	CPointer::Create();
	CHere::Create();
	CIcon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 60, 0.0f));
	CScore::Create(0);
	CTime::Create(100);
	CHit::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 0, 20);
	CHit::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 1, 20);
	CHit::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 2 ,20);

	//�摜���N���G�C�g
	CTexture::Create(D3DXVECTOR3(1225.0f, 685.0f, 0.0f), 70, 50, CTexture::TYPE_KO);
	CTexture::Create(D3DXVECTOR3(30.0f, 660.0f, 0.0f), 80, 50, CTexture::TYPE_HP);
	CTexture::Create(D3DXVECTOR3(360.0f, 660.0f, 0.0f), 83, 60, CTexture::TYPE_TIME);
	CTexture::Create(D3DXVECTOR3(SCREEN_WIDTH/2+83.0f, 670.0f, 0.0f), 88, 80, CTexture::TYPE_FEVER);
	CTexture::Create(D3DXVECTOR3(-700.0f, 400.0f, 0.0f), 610, 150, CTexture::TYPE_IN_FEVER01);
	CTexture::Create(D3DXVECTOR3(1900.0f, 200.0f, 0.0f), 610, 150, CTexture::TYPE_IN_FEVER02);
	CTexture::Create(D3DXVECTOR3(550.0f, 660.0f, 0.0f), 65, 65, CTexture::TYPE_10PLUS);
	CTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50.0f, 0.0f), 350, 300, CTexture::TYPE_FINISH);

	//�Q�[�W���N���G�C�g
	CGauge::Create(D3DXVECTOR3(770.0f, 635.0f, 0.0f), D3DXCOLOR(0.2f, 0.0f, 0.0f, 1.0f), 10, 50, CGauge::UITYPE_FEVERMAX);
	CGauge::Create(D3DXVECTOR3(770.0f,635.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 50, CGauge::UITYPE_FEVER);
	CGauge::Create(D3DXVECTOR3(60.0f, 635.0f, 0.0f), D3DXCOLOR(0.2f, 0.0f, 0.0f, 1.0f), 40, 50, CGauge::UITYPE_HPMAX);
	CGauge::Create(D3DXVECTOR3(60.0f, 635.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, 50, CGauge::UITYPE_HP);
}

//=============================================================================
//�I������
//=============================================================================
void CGame::Uninit(void)
{
	CBg			::Unload();
	CHit		::Unload();
	CHere		::Unload();
	CIcon		::Unload();
	CGauge		::Unload();
	CEnemy		::Unload();
	CEffect		::Unload();
	CPlayer		::Unload();
	CNumber		::Unload();
	CPointer	::Unload();
	CTexture	::Unload();
	CExplosion	::Unload();
}

//=============================================================================
//�X�V����
//=============================================================================
void CGame::Update(void)
{
	CNumber *pNumber;
	pNumber = CTime::GetaTime();
	
	//�v���C���[�̎擾
	CPlayer *pPlayer = CPlayer::GetPlayer();

	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();

	// �L�[�{�[�h�̎擾
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CGamepad *pGamePad = CManager::GetGamePad();

	//�J�����̎擾
	CCamera *pCamera = CCamera::GetCamera();

	//�G���o��������
	EnemySpawn();

	//��ʂ�h�炷
	CameraShake();

	if (CPlayer::bFinish == false)
	{
		nCountTime++;
		nCountGame++;
	}
	//40�t���[�����ƂɎc�莞�Ԃ�1�����炷
	if (nCountTime % 40 == 0)
	{
		((CTime*)pNumber)->AddTime(-1);
	}
	//�|�[�Y
	if (pInputKeyborad->GetKeyboardTrigger(DIK_P) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START))
	{
		if (CPlayer::PlayerState != CPlayer::PLAYERSTATE_FINISH && CPlayer::PlayerState != CPlayer::PLAYERSTATE_DEATH)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			CManager::SetPause(CManager::MODE_PAUSE);
		}
	}
//+++++++++++++++++++++++++++�f�o�b�O�L�[+++++++++++++++++++++++++++
#ifdef _DEBUG
	if (pInputKeyborad->GetKeyboardTrigger(DIK_F))
	{//�t�B�[�o�[���[�h�ɋ����I�Ɉڍs�܂��͉���
		if (CPlayer::bFever == true)
		{
			CPlayer::bFever = false;
		}
		else
		{
			CPlayer::bFever = true;
		}
	}
#endif
}

//=============================================================================
//�`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
//�Q�[���擾
//=============================================================================
CGame * CGame::GetGame(void)
{
	return m_pGame;
}

//=============================================================================
//��ʂ��h��鏈��
//=============================================================================
void CGame::CameraShake(void)
{
	if (CPlayer::bShake == true)
	{
		nCountCamera++;
		if (nCountCamera % 3 == 0)
		{
			CCamera::MoveCamera(D3DXVECTOR3(rand() % 16 - 8.0f, rand() % 16 - 8.0f, 0.0f));
		}
		if (nCountCamera >= SHAKE_COUNT)
		{
			CCamera::ResetCamera();
			CPlayer::bShake = false;
			nCountCamera = 0;
		}
	}
}

//=============================================================================
//�G�𐶐����鏈��
//=============================================================================
void CGame::EnemySpawn(void)
{
	if (nCountGame % 50 == 0)
	{
		CEnemy::Create(D3DXVECTOR3(rand() % 1280 + 302.0f, 0.0f, 0.0f), D3DXVECTOR3(rand() % 1 - 2.0f, 2.0f, 0.0f), 1);
	}
	if (nCountGame % 140 == 0)
	{
		CEnemy::Create(D3DXVECTOR3(rand() % 400 + 0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 0.0f), 1);
	}
	if (nCountGame % 200 == 0)
	{
		CEnemy::Create(D3DXVECTOR3(1280.0f, rand() % 300 + 270.0f, 0.0f), D3DXVECTOR3(rand() % 1 - 3.0f, 0.0f, 0.0f), 1);
	}
	if (CPlayer::bFever == true)
	{
		if (nCountGame % 3 == 0)
		{
			CEnemy::Create(D3DXVECTOR3(rand() % 1280 - 2.0f, 0.0f, 0.0f), D3DXVECTOR3(rand() % 8 - 4.0f, 4.0f, 0.0f), 1);
		}
		if (nCountGame % 11 == 0)
		{
			CEnemy::Create(D3DXVECTOR3(rand() % 400 + 0.0f, 0.0f, 0.0f), D3DXVECTOR3(rand() % 8 + 0.0f, 4.0f, 0.0f), 1);
		}
	}
}

//=============================================================================
//�S�ă��[�h
//=============================================================================
void CGame::LoadAll(void)
{
	CBg			::Load();
	CHit		::Load();
	CIcon		::Load();
	CHere		::Load();
	CGauge		::Load();
	CEnemy		::Load();
	CPlayer		::Load();
	CNumber		::Load();
	CEffect		::Load();
	CPointer	::Load();
	CTexture	::Load();
	CExplosion	::Load();
}

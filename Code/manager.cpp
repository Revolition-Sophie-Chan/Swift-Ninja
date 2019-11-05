//=============================================================================
//
// �Ǘ�����[manager.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "inputkeyboard.h"
#include "player.h"
#include "bg.h"
#include "effect.h"
#include "enemy.h"
#include "explosion.h"
#include "icon.h"
#include "title.h"
#include "game.h"
#include "fade.h"
#include  "sound.h"
#include "gamepad.h"
#include "ranking.h"
#include "rankingall.h"
#include "tutorial.h"
#include "pause.h"

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wPARAM, LPARAM lPARAM);

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputkeyborad *CManager::m_pKeyborad = NULL;
CManager::MODE CManager::m_Mode = MODE_TITLE;
CTitle *CManager::m_pTitle = NULL;
CGame *CManager::m_pGame = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGamepad *CManager::m_pGamepad = NULL;
CRankingAll *CManager::m_pRanking = NULL;
CSound *CManager::m_pSound = NULL;
CPause *CManager::m_pPause = NULL;

//============================================================================================
//�R���X�g���N�^
//============================================================================================
CManager::CManager()
{
}

//============================================================================================
//�f�X�g���N�^
//============================================================================================
CManager::~CManager()
{
}

//=============================================================================
//������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, bool bWindow)
{
	m_pRenderer = new CRenderer;
	m_pKeyborad = new CInputkeyborad;
	m_pGamepad = new CGamepad;
	m_pSound = new CSound;
	m_pGamepad->Init(hinstance, hWnd);
	m_pKeyborad->Init(hinstance, hWnd);
	m_pRenderer->Init(hWnd, bWindow);
	m_pSound->InitSound(hWnd);

	SetMode(m_Mode);
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();
	m_pSound->UninitSound();
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

}

//=============================================================================
//�X�V����
//=============================================================================
void CManager::Update(void)
{
	m_pRenderer->UpDate();
	m_pKeyborad->Update();
	m_pGamepad->Update();

	switch (m_Mode)
	{
	case MODE_TITLE:
		m_pTitle->Update();
		break;
	case MODE_TUTORIAL:
		m_pTutorial->Update();
		break;
	case MODE_GAME:
		m_pGame->Update();
		break;
	case MODE_PAUSE:
		m_pPause->Update();
		break;
	case MODE_RANKING:
		m_pRanking->Update();
		break;
	}
}

//=============================================================================
//�`��
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//=============================================================================
//���[�h�ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_pSound->StopSound();
	if (mode != MODE_PAUSE)
	{
		switch (m_Mode)
		{
		case MODE_TITLE:
			m_pTitle->Uninit();
			break;

		case MODE_TUTORIAL:
			m_pTutorial->Uninit();
			break;

		case MODE_GAME:
			m_pGame->Uninit();
			break;

		case MODE_PAUSE:
			break;

		case MODE_RANKING:
			m_pRanking->Uninit();
			break;
		}
		CScene::ReleaseAll();
	}

	m_Mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		m_pSound->PlaySound(CSound::SOUND_LABEL_TITLE);
		m_pTitle = CTitle::Create();
		break;

	case MODE_TUTORIAL:
		m_pTutorial = CTutorial::Create();
		break;

	case MODE_GAME:
		if (mode != MODE_PAUSE)
		{
			m_pSound->PlaySound(CSound::SOUND_LABEL_BATTLE);
			m_pGame = CGame::Create();

			//�|�[�Y���N���G�C�g
			m_pPause = CPause::Create();
			//�`���false
			m_pPause->SetDraw(false);
		}
		break;

	case MODE_RANKING:
		m_pSound->PlaySound(CSound::SOUND_LABEL_RANKING);
		m_pRanking = CRankingAll::Create();
		break;
	}
}

//=============================================================================
//�|�[�Y�ݒ�
//=============================================================================
CManager::MODE CManager::SetPause(CManager::MODE mode)
{
	switch (mode)
	{
	case MODE_GAME:
		//�`���
		m_pPause->SetDraw(false);
		break;
	case MODE_PAUSE:
		//�`���false
		m_pPause->SetDraw(true);
		break;
	}
	return m_Mode = mode;
}

//=============================================================================
//�擾
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_Mode;
}
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}
CInputkeyborad *CManager::GetInputKeyboard(void)
{
	return m_pKeyborad;
}
CInputkeyborad *CManager::m_pInputKeyboard(void)
{
	return m_pKeyborad;
}
CGamepad * CManager::GetGamePad(void)
{
	return m_pGamepad;
}
CRankingAll *CManager::GetRanking(void)
{
	return m_pRanking;
}
CTutorial * CManager::GetTutorial(void)
{
	return m_pTutorial;
}
CSound *CManager::GetSound(void)
{
	return m_pSound;
}
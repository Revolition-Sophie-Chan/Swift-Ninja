//=============================================================================
//
// �|�[�Y�̏���[pause.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "pause.h"
#include "inputkeyboard.h"
#include "manager.h"
#include "fade.h"
#include "player.h"
#include "texture.h"
#include "gamepad.h"
#include "sound.h"

//=============================================================================
//�����o�ϐ��̏�����
//=============================================================================
CPause::PAUSE_STATE CPause::PauseState = PAUSESTATE_CONTINUE;

//=============================================================================
//�}�N����`
//=============================================================================
#define SELECT_CHOOSE		(D3DXCOLOR(0.1f,1.0f,0.1f,1.0f))
#define SELECT_NOT_CHOOSE	(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f))
#define SIZE_X				(250.0f)
#define SIZE_Y				(125.0f)
#define MAXSIZE_X			(450.0f)
#define MAXSIZE_Y			(225.0f)
#define CHANGESIZE_SPEED	(5.0f)

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPause::CPause()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
//��������
//=============================================================================
CPause * CPause::Create()
{
	CPause *pPause;
	pPause = new CPause;
	pPause->Init();
	return pPause;
}

//=============================================================================
//������
//=============================================================================
void CPause::Init(void)
{
	m_pPauseTexture[0] = CTexture::Create(D3DXVECTOR3(640.0f, 300.0f, 0.0f), SIZE_X, SIZE_Y, CTexture::TYPE_PAUSECONTINUE);
	m_pPauseTexture[1] = CTexture::Create(D3DXVECTOR3(640.0f, 370.0f, 0.0f), SIZE_X, SIZE_Y, CTexture::TYPE_PAUSERETRY);
	m_pPauseTexture[2] = CTexture::Create(D3DXVECTOR3(640.0f, 440.0f, 0.0f), SIZE_X, SIZE_Y, CTexture::TYPE_PAUSEQUIT);
	for (int nCnt = 0; nCnt < PAUSESELECT; nCnt++)
	{
		m_pPauseTexture[nCnt]->SetColor(SELECT_NOT_CHOOSE);
	}
	Size_X		= SIZE_X;
	Size_Y		= SIZE_Y;
	StateCount	= 0;
	bSize		= true;
	bSelect		= true;
	PauseState	= PAUSESTATE_CONTINUE;
	m_pPauseTexture[0]->SetColor(SELECT_CHOOSE);
}

//=============================================================================
//�I������
//=============================================================================
void CPause::Uninit(void)
{
	CTexture::Unload();
}

//=============================================================================
//�X�V����
//=============================================================================
void CPause::Update(void)
{
	CGamepad *pGamePad = CManager::GetGamePad();
	// �L�[�{�[�h�̎擾
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	CSound *pSound = CManager::GetSound();

	m_pPauseTexture[PauseState]->SetColor(SELECT_NOT_CHOOSE);	//�I�΂ꂢ�Ȃ��Ƃ��̐F
	m_pPauseTexture[PauseState]->SetSize(SIZE_X, SIZE_Y);
	switch (StateCount)
	{
	case 0:
		PauseState = PAUSESTATE_CONTINUE;
		break;
	case 1:
		PauseState = PAUSESTATE_RETRY;
		break;
	case 2:
		PauseState = PAUSESTATE_QUIT;
		break;
	}
	float Stick_X, Stick_Y;
	pGamePad->GetStickLeft(0, &Stick_X, &Stick_Y);

	if (bSelect == false)
	{
		if (Stick_Y == 0)
		{
			bSelect = true;
		}
	}
	else
	{
		if (pInputKeyborad->GetKeyboardTrigger(DIK_S) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_DOWN))
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

			if (StateCount == 2)
			{
				StateCount = 0;
			}
			else
			{
				StateCount += 1;
			}
		}
		else if (pInputKeyborad->GetKeyboardTrigger(DIK_W) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_UP))
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

			if (StateCount == 0)
			{
				StateCount = 2;
			}
			else
			{
				StateCount -= 1;
			}
		}
		else if (Stick_Y <= -3000)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

			bSelect = false;
			if (StateCount == 2)
			{
				StateCount = 0;
			}
			else
			{
				StateCount += 1;
			}
		}
		else if (Stick_Y >= 3000)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

			bSelect = false;
			if (StateCount == 0)
			{
				StateCount = 2;
			}
			else
			{
				StateCount -= 1;
			}
		}
	}

	m_pPauseTexture[PauseState]->SetColor(SELECT_CHOOSE);	//�I�΂�Ă���Ƃ��̐F
	SetSelectSize(PauseState);

	if (pInputKeyborad->GetKeyboardTrigger(DIK_RETURN) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_B))
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_DECISION);

		if (PauseState == PAUSESTATE_CONTINUE)
		{//�Q�[���ɖ߂�
			CManager::SetPause(CManager::MODE_GAME);
		}
		else if (PauseState == PAUSESTATE_RETRY)
		{//���Ȃ���
			CFade::SetFade(CManager::MODE_GAME);
		}
		else if (PauseState == PAUSESTATE_QUIT)
		{//�^�C�g���ɖ߂�
			CFade::SetFade(CManager::MODE_TITLE);
		}
	}
	if (pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_A)|| pInputKeyborad->GetKeyboardTrigger(DIK_P))
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_DECISION);
		CManager::SetPause(CManager::MODE_GAME);
	}
}

//=============================================================================
//�`��
//=============================================================================
void CPause::Draw(void)
{
}

//=============================================================================
//�`�悷�鏈��
//=============================================================================
void CPause::SetDraw(bool bDraw)
{
	m_pPauseTexture[0]->m_bDraw = bDraw;
	m_pPauseTexture[1]->m_bDraw = bDraw;
	m_pPauseTexture[2]->m_bDraw = bDraw;
}

//=============================================================================
//�擾
//=============================================================================
CPause::PAUSE_STATE CPause::GetPauseState()
{
	return PauseState;
}

//=============================================================================
//�ݒ�
//=============================================================================
void CPause::SetPauseState(PAUSE_STATE state)
{
	PauseState = state;
}

//=============================================================================
//�T�C�Y�ݒ�
//=============================================================================
void CPause::SetSelectSize(int Size )
{
	Size = StateCount;
	if (Size_X <= SIZE_X && Size_Y <= SIZE_Y || Size_X <= MAXSIZE_X && Size_Y <= MAXSIZE_Y&&bSize != false)
	{
		bSize = true;
	}
	else if (Size_X >= MAXSIZE_X && Size_Y >= MAXSIZE_Y)
	{
		bSize = false;
	}

	if (bSize == true)
	{
		Size_X += CHANGESIZE_SPEED;
		Size_Y += CHANGESIZE_SPEED/2;
	}
	else
	{
		Size_X -= CHANGESIZE_SPEED;
		Size_Y -= CHANGESIZE_SPEED/2;
	}
	m_pPauseTexture[PauseState]->SetSize(Size_X, Size_Y);
}

//=============================================================================
//
// �L�[�{�[�h���͏��� [inputkeyboard.cpp]
// Author : tanaka rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include"inputkeyboard.h"
#include"main.h"
#include"input.h"


//============================================================================================
//�R���X�g���N�^
//============================================================================================
CInputkeyborad::CInputkeyborad()
{
}
//============================================================================================
//�f�X�g���N�^
//============================================================================================
CInputkeyborad::~CInputkeyborad()
{
}
 //=============================================================================
 // �L�[�{�[�h�̏�����
 //=============================================================================
HRESULT CInputkeyborad::Init(HINSTANCE hInstance, HWND hWnd)
{

	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CInputkeyborad::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();//�L�[�̃A�N�Z�X��
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputkeyborad::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//
	int nCntkey;

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			g_aKeyStateTrigger[nCntkey] = (g_aKeyState[nCntkey] ^ aKeyState[nCntkey]) & aKeyState[nCntkey];
			g_aKeyState[nCntkey] = aKeyState[nCntkey];//
		}
	}
	else
	{
		m_pDevice->Acquire();//
	}
}

//=============================================================================
//�@�v���X����
//=============================================================================
bool CInputkeyborad::GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �g���K�[����
//=============================================================================
bool CInputkeyborad::GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �g���K�[����
//=============================================================================
bool CInputkeyborad::GetKeyboardRelease(int nKey)
{
	return(g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

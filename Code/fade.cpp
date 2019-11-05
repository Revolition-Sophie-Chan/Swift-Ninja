//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "fade.h"
#include "renderer.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
CManager::MODE	CFade::m_NextMode		= {};
CFade::FADE		CFade::m_Fade			= FADE_IN;
D3DXCOLOR		CFade::m_FadeColor		= D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

//=============================================================================
//�}�N����`
//=============================================================================
#define FADE_SPEED (0.04f)	//�t�F�[�h�̑���

//=============================================================================
//����������
//=============================================================================
void CFade::InitFade()
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_Fade = FADE_IN;
	m_FadeColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// ������ʁi�s�����j

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"Data/Texture/fade.png",		// �t�@�C���̖��O
		&m_pTextureFade);	// �ǂݍ��ރ������[

	// ���_���̐ݒ�
	VERTEX_2D *pVtx;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_FadeColor;
	pVtx[1].col = m_FadeColor;
	pVtx[2].col = m_FadeColor;
	pVtx[3].col = m_FadeColor;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuffFade->Unlock();
}

//=============================================================================
//�I������
//=============================================================================
void CFade::UninitFade(void)
{
	// �e�N�X�`���̊J��
	if (m_pTextureFade != NULL)
	{
		m_pTextureFade->Release();
		m_pTextureFade = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuffFade != NULL)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CFade::UpdateFade(void)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	if (m_Fade != FADE_NONE)
	{
		if (m_Fade == FADE_IN)
		{
			m_FadeColor.a -= FADE_SPEED;
			if (m_FadeColor.a <= 0.0f)
			{
				m_FadeColor.a = 0.0f;
				m_Fade = FADE_NONE;
			}
		}
		else if (m_Fade == FADE_OUT)//
		{
			m_FadeColor.a += FADE_SPEED;
			if (m_FadeColor.a >= 1.0f)
			{
				m_FadeColor.a = 1.0f;
				m_Fade = FADE_IN;
				//
				CManager::SetMode(m_NextMode);
			}
		}
		// ���_�J���[�̐ݒ�
		pVtx[0].col = m_FadeColor;
		pVtx[1].col = m_FadeColor;
		pVtx[2].col = m_FadeColor;
		pVtx[3].col = m_FadeColor;
		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	m_pVtxBuffFade->Unlock();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CFade::DrawFade(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureFade);

	// �`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//============================================================================================
//�t�F�[�h�ݒ�
//============================================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_Fade = FADE_OUT;
	m_NextMode = modeNext;
}
//============================================================================================
//�t�F�[�h�擾
//============================================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_Fade;
}

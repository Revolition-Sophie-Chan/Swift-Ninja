//=============================================================================
//
// �|���S������[scene2D.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "input.h"
#include "inputkeyboard.h"
#include "camera.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(OBJECT_TYPE type) :CScene(type)
{
	m_pTexture = NULL;//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;//���_�o�b�t�@�ւ̃|�C���^
	CScene2D::m_CountAnim = NULL;
	CScene2D::nPattenAnim = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Size_X = 0.0f;
	m_Size_Y = 0.0f;
	m_bDraw = true;


}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// �|���S���̏�����
//=============================================================================
void CScene2D::Init(void)
{

	m_fRot = 0.0f;
	m_nCountRot = 0;

	m_CountAnim = 0;
	nPattenAnim = 0;

	// �L�[�{�[�h�̎擾
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	//�f�o�C�X�̎擾

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_Size_X, -m_Size_Y, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_Size_X, -m_Size_Y, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_Size_X, m_Size_Y, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_Size_X, m_Size_Y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	////�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();

}
//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
//=============================================================================
// polygon�X�V����
//=============================================================================
void CScene2D::Update(void)
{

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	CCamera *pCamera = CCamera::GetCamera();

	D3DXVECTOR3 CameraPos = pCamera->GetCameraPos();

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(m_Size_X*sinf(atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot + D3DX_PI),
		m_Size_Y*cosf(atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot + D3DX_PI), 0.0f) + CameraPos;

	pVtx[1].pos = m_pos + D3DXVECTOR3(m_Size_X*sinf(-atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot + D3DX_PI),
		m_Size_Y*cosf(-atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot + D3DX_PI), 0.0f) + CameraPos;

	pVtx[2].pos = m_pos + D3DXVECTOR3(m_Size_X*sinf(-atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot),
		m_Size_Y*cosf(-atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot), 0.0f) + CameraPos;

	pVtx[3].pos = m_pos + D3DXVECTOR3(m_Size_X*sinf(atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot),
		m_Size_Y*cosf(atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot), 0.0f) + CameraPos;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();

}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CScene2D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	if (m_bDraw)
	{
		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓��ꂩ��
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


		//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	}

}
//=============================================================================
// �e�N�X�`����ݒ�
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 m_pSetTexture)
{
	m_pTexture = m_pSetTexture;
}

//=============================================================================
// �A�j���[�V����
//=============================================================================
void CScene2D::SetAnim(int nNumber, int nPatten, int nStage)
{
	VERTEX_2D *pVtx;
	float nHeight;
	nHeight = 1 / (float)nNumber;
	//���L���X�g���ʓ��̕ϐ��^�ɕύX�ł���
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nStage == 0)//��̒i
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + nPatten*nHeight, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nHeight + nPatten*nHeight, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nPatten*nHeight, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(nHeight + nPatten*nHeight, 0.5f);
	}
	else if (nStage == 1)//���̒i
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + nPatten*nHeight, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(nHeight + nPatten*nHeight, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nPatten*nHeight, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nHeight + nPatten*nHeight, 1.0f);
	}
	else if (nStage == 2)//�S��
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + nPatten*nHeight, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nHeight + nPatten*nHeight, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nPatten*nHeight, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nHeight + nPatten*nHeight, 1.0f);
	}

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �|�W�V�����̐ݒ�
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//=============================================================================
// ���[�u�̐ݒ�
//=============================================================================
void CScene2D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}
//=============================================================================
// ��]�̐ݒ�
//=============================================================================
void CScene2D::SetRot(float m_rot)
{
	m_fRot = m_rot;
}
//=============================================================================
// �J���[�ݒ�
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
//=============================================================================
// �T�C�Y�ݒ�
//=============================================================================
void CScene2D::SetSize(float fSize_X, float fSize_Y)
{
	m_Size_X = fSize_X;
	m_Size_Y = fSize_Y;
}
//=============================================================================
// �ݒ�
//=============================================================================
void CScene2D::SetRadius(float Radius)
{
	m_Radius = Radius;
}

//=============================================================================
// ���C�t�ݒ�
//=============================================================================
void CScene2D::SetLife(int nLife)
{
	m_Life = nLife;
}

//=============================================================================
// �Q�[�W
//=============================================================================
void CScene2D::SetGauge(float nWight, float nHeight)
{
	VERTEX_2D *pVtx;

	CCamera *pCamera = CCamera::GetCamera();
	D3DXVECTOR3 CameraPos = pCamera->GetCameraPos();
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f) + CameraPos;
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + nWight, m_pos.y, 0.0f) + CameraPos;
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + nHeight, 0.0f) + CameraPos;
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + nWight, m_pos.y + nHeight, 0.0f) + CameraPos;

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �|�W�V�����̎擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
// ���[�u�̎擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetMove(void)
{
	return m_move;
}
//=============================================================================
// ��]�̎擾
//=============================================================================
float CScene2D::GetRot(void)
{
	return m_fRot;
}
//=============================================================================
// �J���[�̎擾
//=============================================================================
D3DXCOLOR CScene2D::GetColor(void)
{
	return m_col;
}
//=============================================================================
// �T�C�Y�̎擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetSize(void)
{
	return D3DXVECTOR3(m_Size_X, m_Size_Y, 0.0f);
}

//=============================================================================
// ���C�t�̎擾
//=============================================================================
int CScene2D::GetLife(void)
{
	return m_Life;
}

//=============================================================================
// �w�i��������
//=============================================================================
void CScene2D::TextureMove(void)
{
	CPlayer *pPlayer = CPlayer::GetPlayer();

	float move;

	if (CPlayer::bFever == false)
	{
		move = 0.0005f;
	}
	else
	{
		move = 0.03f;
	}
	m_Movetex += move;
	VERTEX_2D *pVtx;
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].tex = D3DXVECTOR2(0.0f + m_Movetex, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + m_Movetex, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_Movetex, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + m_Movetex, 1.0f);

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �e�N�X�`��������
//=============================================================================
void CScene2D::InitTex(int Height, float Weight)
{
	float nHeight;
	nHeight = 1 / (float)Height;
	VERTEX_2D *pVtx;
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nHeight, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, Weight);
	pVtx[3].tex = D3DXVECTOR2(nHeight, Weight);
	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

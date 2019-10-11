//=============================================================================
//
// ��������[Number.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================
#include"renderer.h"
#include"Number.h"
#include"manager.h"
#include"Scene2D.h"
#include"camera.h"

LPDIRECT3DTEXTURE9 CNumber::m_pTextureNumber=NULL;
//============================================================================================
//�}�N����`
//============================================================================================
#define	TEXTURE_SCORE		"Data/Texture/number002.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_HEART		"Data/Texture/heart.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
//============================================================================================
//�����X�g���N�^
//============================================================================================
CNumber::CNumber()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_size_X = 0;
	m_size_Y = 0;
	m_nNumber = 0;
}

//============================================================================================
//�f�X�g���N�^
//============================================================================================
CNumber::~CNumber()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CNumber::Init()
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 , D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffNumber, NULL);

	//�f�o�C�X�̎擾
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐ݒ�	
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size_X, -m_size_Y, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_size_X, -m_size_Y, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size_X, m_size_Y, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_size_X, m_size_Y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	////�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.1f*m_nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f*m_nNumber+0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f*m_nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f*m_nNumber+0.1f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	m_pVtxBuffNumber->Unlock();
	return S_OK;
}
//=============================================================================
// �|���S���̏I��
//=============================================================================
void CNumber::Uninit(void)
{
	
	if (m_pVtxBuffNumber != NULL)
	{
		m_pVtxBuffNumber->Release();
		m_pVtxBuffNumber = NULL;
	}
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CNumber::Update(void)
{

	CCamera *pCamera = CCamera::GetCamera();
	D3DXVECTOR3 CameraPos = pCamera->GetCameraPos();
	//�f�o�C�X�̎擾
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size_X, -m_size_Y, 0.0f) + CameraPos;
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_size_X, -m_size_Y, 0.0f) + CameraPos;
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size_X, m_size_Y, 0.0f) + CameraPos;
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_size_X, m_size_Y, 0.0f) + CameraPos;


	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�f�[�^�̃A�����b�N
	m_pVtxBuffNumber->Unlock();
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CNumber::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuffNumber, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureNumber);

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓��ꂩ��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CNumber::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXCreateTextureFromFile(pDevice, TEXTURE_SCORE, &m_pTextureNumber);
	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CNumber::Unload(void)
{
		if (m_pTextureNumber != NULL)
		{
			m_pTextureNumber->Release();
			m_pTextureNumber = NULL;
		}
}

//=============================================================================
// �|���S���̃N���G�C�g
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos ,float size_X,float size_Y,int nNumber)
{
	CNumber *pNumber;

	pNumber = new CNumber();

	pNumber->SetNumber(nNumber);

	pNumber->SetPosition(pos);

	pNumber->SetSize(size_X, size_Y);

	pNumber->Init();

	return pNumber;
}


//=============================================================================
// �̗͂̐ݒ�
//=============================================================================
void CNumber::SetHeart(int Heart)
{
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(Heart*0.33f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(Heart*0.33f + 0.33f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(Heart*0.33f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(Heart*0.33f + 0.33f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	m_pVtxBuffNumber->Unlock();
}
//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CNumber::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
//=============================================================================
// �i���o�[�̐ݒ�
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;
}
//=============================================================================
// �|�W�V�����̐ݒ�
//=============================================================================
void CNumber::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//=============================================================================
// �T�C�Y�̐ݒ�
//=============================================================================
void CNumber::SetSize(float size_x, float size_y)
{
	m_size_X = size_x;
	m_size_Y = size_y;
}
//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void CNumber::SetTex(int nDigits)
{
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	////�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.1f*nDigits, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f*nDigits + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f*nDigits, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f*nDigits + 0.1f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	m_pVtxBuffNumber->Unlock();
}

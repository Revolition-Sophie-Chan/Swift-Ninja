//=============================================================================
//
// ���j���o�̏���[hit.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "renderer.h"
#include "hit.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CHit::m_pTexturehit[MAX_HIT] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CHit::CHit(OBJECT_TYPE type = OBJECT_TYPE_POINTER) : CScene2D(type)
{

}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CHit::~CHit()
{
}

//=============================================================================
//��������
//=============================================================================
CHit *CHit::Create(D3DXCOLOR Hitcol,int type,int nLife)
{
	CHit *pHit;
	pHit = new CHit(OBJECT_TYPE_POINTER);
	pHit->Init();
	pHit->InitTex(1, 1.0f);		
	pHit->SetColor(Hitcol);
	pHit->SetLife(nLife);
	pHit->BindTexture(m_pTexturehit[type]);
	return pHit;
}

//=============================================================================
//����������
//=============================================================================
void CHit::Init()
{
	CScene2D::Init();
	m_nLife = GetLife();
}

//=============================================================================
//�I������
//=============================================================================
void CHit::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//�����X�V����
//=============================================================================
void CHit::Update(void)
{
	//�|�W�V�����̎擾
	D3DXVECTOR3 pos = GetPosition();

	//�J���[�̎擾
	D3DXCOLOR col = GetColor();

	//���C�t�̎擾
	m_nLife = GetLife();

	SetSize(SCREEN_WIDTH + 100, SCREEN_HEIGHT + 100);

	col.a -= 0.1f;
	m_nLife--;

	//�|�W�V�����̍X�V
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,0.0f));

	//�J���[�̍X�V
	SetColor(col);

	//���C�t�̍X�V
	SetLife(m_nLife);

	CScene2D::Update();
	if (m_nLife <= 0)
	{
		Release();
	}
}

//=============================================================================
//�`��
//=============================================================================
void CHit::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
//���[�h
//=============================================================================
HRESULT CHit::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/fade.png",			&m_pTexturehit[0]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/white_line.png",	&m_pTexturehit[1]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/black_line.png",	&m_pTexturehit[2]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/fever_line.png",	&m_pTexturehit[3]);
	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CHit::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_HIT; nCnt++)
	{
		if (m_pTexturehit[nCnt] != NULL)
		{
			m_pTexturehit[nCnt]->Release();
			m_pTexturehit[nCnt] = NULL;
		}
	}
}


//=============================================================================
//
// �G�t�F�N�g�̏���[Particle.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================
#include "renderer.h"
#include "particle.h"
#include "enemy.h"
#include "manager.h"
#include "explosion.h"
#include "inputkeyboard.h"
#include "scene2D.h"

LPDIRECT3DTEXTURE9 CParticle::m_pTextureParticle[MAX_TEXTURE] = {};
//=============================================================================
//�����X�g���N�^
//=============================================================================
CParticle::CParticle(OBJECT_TYPE type = OBJECT_TYPE_PARTICLE) : CScene2D(type)
{
	m_pTextureParticle[MAX_TEXTURE] = {};//�e�N�X�`���ւ̃|�C���^
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CParticle::~CParticle()
{

}

//=============================================================================
// �N���G�C�g
//=============================================================================
CParticle *CParticle::Create(D3DXVECTOR3 ParticlePos, D3DXVECTOR3 ParticleMove, D3DXCOLOR ParticleCol, float fRadius)
{
	CParticle *pParticle;
	pParticle = new CParticle(OBJECT_TYPE_PARTICLE);
	pParticle->SetPosition(ParticlePos);
	pParticle->SetMove(ParticleMove);
	pParticle->SetColor(ParticleCol);
	pParticle->SetRadius(fRadius);
	pParticle->BindTexture(m_pTextureParticle[0]);
	pParticle->Init();
	return pParticle;
}

//=============================================================================
// ����������
//=============================================================================
void CParticle::Init()
{
	CScene2D::Init();
	SetObjType(CScene::OBJECT_TYPE_PARTICLE);
	m_nLife = 0;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CParticle::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CParticle::Update(void)
{
	D3DXCOLOR col = GetColor();
	D3DXVECTOR3 size = GetSize();

	m_pos += m_move;

	//col.a -= 0.008f;
	//size *= 0.9f;
	m_nLife--;

	SetColor(col);
	CScene2D::Update();

	if (m_nLife <= 0)
	{
		Release();
	}

}

//=============================================================================
// �J���[�擾
//=============================================================================
D3DXCOLOR CParticle::GetParticleColer(void)
{
	return m_col;
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CParticle::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �����_�[�X�e�[�g(���Z��������)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//�v�Z����
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	//���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//���f�B�X�ƃl�[�V�����J���[�̎w��

	CScene2D::Draw();

	// �����_�[�X�e�[�g(�ʏ�u�����h����)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		//�v�Z����
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	//���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//���f�B�X�ƃl�[�V�����J���[�̎w��

}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CParticle::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/effect001.jpg", &m_pTextureParticle[0]);
	return S_OK;

}

//=============================================================================
// �A�����[�h
//=============================================================================
void CParticle::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_pTextureParticle[nCnt] != NULL)
		{
			m_pTextureParticle[nCnt]->Release();
			m_pTextureParticle[nCnt] = NULL;
		}
	}

}
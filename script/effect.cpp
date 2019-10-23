//=============================================================================
//
// �G�t�F�N�g�̏���[Effect.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include"renderer.h"
#include"effect.h"
#include"enemy.h"
#include"manager.h"
#include"explosion.h"
#include "inputkeyboard.h"
#include "scene2D.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTextureEffect[MAX_EFFECT] = {};
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEffect::CEffect(OBJECT_TYPE type = OBJECT_TYPE_EFFECT) : CScene2D(type)
{
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// �N���G�C�g
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 Effectpos, D3DXCOLOR EffectCol, D3DXVECTOR3 Effectmove,float Size,int EffectNumber,int EffectLife)
{
	CEffect *pEffect;
	pEffect = new CEffect(OBJECT_TYPE_EFFECT);
	pEffect->SetPosition(Effectpos);
	pEffect->SetColor(EffectCol);
	pEffect->SetMove(Effectmove);
	pEffect->SetSize(Size, Size);
	pEffect->SetLife(EffectLife);
	pEffect->BindTexture(m_pTextureEffect[EffectNumber]);
	pEffect->Init();
	return pEffect;
}

//=============================================================================
// ����������
//=============================================================================
void CEffect::Init()
{
	CScene2D::Init();
	m_nLife = 0;
	SetObjType(CScene::OBJECT_TYPE_EFFECT);
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CEffect::Update(void)
{

	CScene2D::Update();

	// �J���[�̎擾
	D3DXCOLOR col = GetColor();
	// �T�C�Y�̎擾
	D3DXVECTOR3 size = GetSize();
	// �|�W�V�����̎擾
	D3DXVECTOR3 pos = GetPosition();
	// ���[�u�̎擾
	D3DXVECTOR3 move = GetMove();
	// ���[�u�̎擾
	m_nLife = GetLife();

	col.a -= 0.002f;
	size.x -= 0.2f;
	size.y -= 0.2f;
	pos += move;

	m_nLife--;

	SetColor(col);
	SetSize(size.x,size.y);
	SetMove(move);
	SetPosition(pos);
	SetLife(m_nLife);
	if (m_nLife <= 0)
	{
		Release();
	}
}

//=============================================================================
// �J���[�擾
//=============================================================================
D3DXCOLOR CEffect::GetEffectColer(void)
{
	return m_col;
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CEffect::Draw(void)
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
HRESULT CEffect::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/effect000.jpg", &m_pTextureEffect[0]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/effect001.jpg", &m_pTextureEffect[1]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/effect002.jpg", &m_pTextureEffect[2]);
	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CEffect::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (m_pTextureEffect[nCnt] != NULL)
		{
			m_pTextureEffect[nCnt]->Release();
			m_pTextureEffect[nCnt] = NULL;
		}
	}

}
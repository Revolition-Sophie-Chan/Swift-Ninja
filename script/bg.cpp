//=============================================================================
//
// �w�i�̏���[Bg.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================
#include"renderer.h"
#include"bg.h"
#include"explosion.h"
#include "inputkeyboard.h"
#include "scene2D.h"


LPDIRECT3DTEXTURE9 CBg::m_pTextureBg = NULL;
//=============================================================================
//�����X�g���N�^
//=============================================================================
CBg::CBg(OBJECT_TYPE type = OBJECT_TYPE_BG) : CScene2D(type)
{
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
// �N���G�C�g
//=============================================================================
CBg *CBg::Create(D3DXVECTOR3 BGpos)
{
	CBg *pBg;
	pBg = new CBg(OBJECT_TYPE_BG);
	pBg->SetPosition(BGpos);
	pBg->Init();
	pBg->InitTex(1, 1.0f);
	pBg->BindTexture(m_pTextureBg);
	return pBg;
}

//=============================================================================
// ����������
//=============================================================================
void CBg::Init()
{
	CScene2D::Init();

}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CBg::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// polygon�X�V����
//=============================================================================
void CBg::Update(void)
{
	CScene2D::Update();
	SetSize(1000.0f, 670.0f);
	TextureMove();
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CBg::Draw(void)
{
	CScene2D::Draw();
}

HRESULT CBg::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/BackGround.png", &m_pTextureBg);
	return S_OK;
}

void CBg::Unload(void)
{

	if (m_pTextureBg != NULL)
	{
		m_pTextureBg->Release();
		m_pTextureBg = NULL;
	}
}


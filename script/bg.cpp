//=============================================================================
//
// 背景の処理[Bg.cpp]
// Author：tanaka rikiya
//
//=============================================================================
#include"renderer.h"
#include"bg.h"
#include"explosion.h"
#include "inputkeyboard.h"
#include "scene2D.h"


LPDIRECT3DTEXTURE9 CBg::m_pTextureBg = NULL;
//=============================================================================
//こンストラクタ
//=============================================================================
CBg::CBg(OBJECT_TYPE type = OBJECT_TYPE_BG) : CScene2D(type)
{
}
//=============================================================================
//デストラクタ
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
// クリエイト
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
// 初期化処理
//=============================================================================
void CBg::Init()
{
	CScene2D::Init();

}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CBg::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// polygon更新処理
//=============================================================================
void CBg::Update(void)
{
	CScene2D::Update();
	SetSize(1000.0f, 670.0f);
	TextureMove();
}
//=============================================================================
// ポリゴンの描画
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


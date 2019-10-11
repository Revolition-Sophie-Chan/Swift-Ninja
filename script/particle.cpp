//=============================================================================
//
// エフェクトの処理[Particle.cpp]
// Author：tanaka rikiya
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
//こンストラクタ
//=============================================================================
CParticle::CParticle(OBJECT_TYPE type = OBJECT_TYPE_PARTICLE) : CScene2D(type)
{
	m_pTextureParticle[MAX_TEXTURE] = {};//テクスチャへのポインタ
}
//=============================================================================
//デストラクタ
//=============================================================================
CParticle::~CParticle()
{

}

//=============================================================================
// クリエイト
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
// 初期化処理
//=============================================================================
void CParticle::Init()
{
	CScene2D::Init();
	SetObjType(CScene::OBJECT_TYPE_PARTICLE);
	m_nLife = 0;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CParticle::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
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
// カラー取得
//=============================================================================
D3DXCOLOR CParticle::GetParticleColer(void)
{
	return m_col;
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CParticle::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// レンダーステート(加算合成処理)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			//計算方式
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	//αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//αディスとネーションカラーの指定

	CScene2D::Draw();

	// レンダーステート(通常ブレンド処理)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		//計算方式
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	//αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//αディスとネーションカラーの指定

}

//=============================================================================
// ロード
//=============================================================================
HRESULT CParticle::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/effect001.jpg", &m_pTextureParticle[0]);
	return S_OK;

}

//=============================================================================
// アンロード
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
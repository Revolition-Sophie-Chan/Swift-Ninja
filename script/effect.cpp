//=============================================================================
//
// エフェクトの処理[Effect.cpp]
// Author：tanaka rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include"renderer.h"
#include"effect.h"
#include"enemy.h"
#include"manager.h"
#include"explosion.h"
#include "inputkeyboard.h"
#include "scene2D.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTextureEffect[MAX_EFFECT] = {};
//=============================================================================
//コンストラクタ
//=============================================================================
CEffect::CEffect(OBJECT_TYPE type = OBJECT_TYPE_EFFECT) : CScene2D(type)
{
}
//=============================================================================
//デストラクタ
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// クリエイト
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
// 初期化処理
//=============================================================================
void CEffect::Init()
{
	CScene2D::Init();
	m_nLife = 0;
	SetObjType(CScene::OBJECT_TYPE_EFFECT);
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CEffect::Update(void)
{

	CScene2D::Update();

	// カラーの取得
	D3DXCOLOR col = GetColor();
	// サイズの取得
	D3DXVECTOR3 size = GetSize();
	// ポジションの取得
	D3DXVECTOR3 pos = GetPosition();
	// ムーブの取得
	D3DXVECTOR3 move = GetMove();
	// ムーブの取得
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
// カラー取得
//=============================================================================
D3DXCOLOR CEffect::GetEffectColer(void)
{
	return m_col;
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CEffect::Draw(void)
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
// アンロード
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
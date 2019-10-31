//=============================================================================
//
// 撃破演出の処理[hit.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "renderer.h"
#include "hit.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CHit::m_pTexturehit[MAX_HIT] = {};

//=============================================================================
//コンストラクタ
//=============================================================================
CHit::CHit(OBJECT_TYPE type = OBJECT_TYPE_POINTER) : CScene2D(type)
{

}
//=============================================================================
//デストラクタ
//=============================================================================
CHit::~CHit()
{
}

//=============================================================================
//生成処理
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
//初期化処理
//=============================================================================
void CHit::Init()
{
	CScene2D::Init();
	m_nLife = GetLife();
}

//=============================================================================
//終了処理
//=============================================================================
void CHit::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//爆発更新処理
//=============================================================================
void CHit::Update(void)
{
	//ポジションの取得
	D3DXVECTOR3 pos = GetPosition();

	//カラーの取得
	D3DXCOLOR col = GetColor();

	//ライフの取得
	m_nLife = GetLife();

	SetSize(SCREEN_WIDTH + 100, SCREEN_HEIGHT + 100);

	col.a -= 0.1f;
	m_nLife--;

	//ポジションの更新
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,0.0f));

	//カラーの更新
	SetColor(col);

	//ライフの更新
	SetLife(m_nLife);

	CScene2D::Update();
	if (m_nLife <= 0)
	{
		Release();
	}
}

//=============================================================================
//描画
//=============================================================================
void CHit::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
//ロード
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
// アンロード
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


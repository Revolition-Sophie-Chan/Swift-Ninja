//=============================================================================
//
// 数字処理[Number.cpp]
// Author：tanaka rikiya
//
//=============================================================================
#include"renderer.h"
#include"Number.h"
#include"manager.h"
#include"Scene2D.h"
#include"camera.h"

LPDIRECT3DTEXTURE9 CNumber::m_pTextureNumber=NULL;
//============================================================================================
//マクロ定義
//============================================================================================
#define	TEXTURE_SCORE		"Data/Texture/number002.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_HEART		"Data/Texture/heart.png"		// 読み込むテクスチャファイル名
//============================================================================================
//こンストラクタ
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
//デストラクタ
//============================================================================================
CNumber::~CNumber()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CNumber::Init()
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 , D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffNumber, NULL);

	//デバイスの取得
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定	
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

	////テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.1f*m_nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f*m_nNumber+0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f*m_nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f*m_nNumber+0.1f, 1.0f);

	//頂点データのアンロック
	m_pVtxBuffNumber->Unlock();
	return S_OK;
}
//=============================================================================
// ポリゴンの終了
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
// ポリゴンの更新
//=============================================================================
void CNumber::Update(void)
{

	CCamera *pCamera = CCamera::GetCamera();
	D3DXVECTOR3 CameraPos = pCamera->GetCameraPos();
	//デバイスの取得
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size_X, -m_size_Y, 0.0f) + CameraPos;
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_size_X, -m_size_Y, 0.0f) + CameraPos;
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size_X, m_size_Y, 0.0f) + CameraPos;
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_size_X, m_size_Y, 0.0f) + CameraPos;


	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データのアンロック
	m_pVtxBuffNumber->Unlock();
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CNumber::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuffNumber, 0, sizeof(VERTEX_2D));

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTextureNumber);

	//バックバッファとフロントバッファの入れかえ
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ロード
//=============================================================================
HRESULT CNumber::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXCreateTextureFromFile(pDevice, TEXTURE_SCORE, &m_pTextureNumber);
	return S_OK;
}

//=============================================================================
// アンロード
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
// ポリゴンのクリエイト
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
// 体力の設定
//=============================================================================
void CNumber::SetHeart(int Heart)
{
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標設定
	pVtx[0].tex = D3DXVECTOR2(Heart*0.33f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(Heart*0.33f + 0.33f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(Heart*0.33f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(Heart*0.33f + 0.33f, 1.0f);

	//頂点データのアンロック
	m_pVtxBuffNumber->Unlock();
}
//=============================================================================
// カラーの設定
//=============================================================================
void CNumber::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
//=============================================================================
// ナンバーの設定
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;
}
//=============================================================================
// ポジションの設定
//=============================================================================
void CNumber::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//=============================================================================
// サイズの設定
//=============================================================================
void CNumber::SetSize(float size_x, float size_y)
{
	m_size_X = size_x;
	m_size_Y = size_y;
}
//=============================================================================
// テクスチャの設定
//=============================================================================
void CNumber::SetTex(int nDigits)
{
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffNumber->Lock(0, 0, (void**)&pVtx, 0);

	////テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.1f*nDigits, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f*nDigits + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f*nDigits, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f*nDigits + 0.1f, 1.0f);

	//頂点データのアンロック
	m_pVtxBuffNumber->Unlock();
}

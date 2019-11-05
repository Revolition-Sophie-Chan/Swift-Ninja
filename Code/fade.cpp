//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "fade.h"
#include "renderer.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
CManager::MODE	CFade::m_NextMode		= {};
CFade::FADE		CFade::m_Fade			= FADE_IN;
D3DXCOLOR		CFade::m_FadeColor		= D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

//=============================================================================
//マクロ定義
//=============================================================================
#define FADE_SPEED (0.04f)	//フェードの早さ

//=============================================================================
//初期化処理
//=============================================================================
void CFade::InitFade()
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_Fade = FADE_IN;
	m_FadeColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// 黒い画面（不透明）

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		"Data/Texture/fade.png",		// ファイルの名前
		&m_pTextureFade);	// 読み込むメモリー

	// 頂点情報の設定
	VERTEX_2D *pVtx;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_FadeColor;
	pVtx[1].col = m_FadeColor;
	pVtx[2].col = m_FadeColor;
	pVtx[3].col = m_FadeColor;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	m_pVtxBuffFade->Unlock();
}

//=============================================================================
//終了処理
//=============================================================================
void CFade::UninitFade(void)
{
	// テクスチャの開放
	if (m_pTextureFade != NULL)
	{
		m_pTextureFade->Release();
		m_pTextureFade = NULL;
	}

	// 頂点バッファの開放
	if (m_pVtxBuffFade != NULL)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = NULL;
	}
}

//=============================================================================
//更新処理
//=============================================================================
void CFade::UpdateFade(void)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	if (m_Fade != FADE_NONE)
	{
		if (m_Fade == FADE_IN)
		{
			m_FadeColor.a -= FADE_SPEED;
			if (m_FadeColor.a <= 0.0f)
			{
				m_FadeColor.a = 0.0f;
				m_Fade = FADE_NONE;
			}
		}
		else if (m_Fade == FADE_OUT)//
		{
			m_FadeColor.a += FADE_SPEED;
			if (m_FadeColor.a >= 1.0f)
			{
				m_FadeColor.a = 1.0f;
				m_Fade = FADE_IN;
				//
				CManager::SetMode(m_NextMode);
			}
		}
		// 頂点カラーの設定
		pVtx[0].col = m_FadeColor;
		pVtx[1].col = m_FadeColor;
		pVtx[2].col = m_FadeColor;
		pVtx[3].col = m_FadeColor;
		pVtx += 4;
	}
	// 頂点データをアンロックする
	m_pVtxBuffFade->Unlock();
}

//=============================================================================
//描画処理
//=============================================================================
void CFade::DrawFade(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTextureFade);

	// 描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//============================================================================================
//フェード設定
//============================================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_Fade = FADE_OUT;
	m_NextMode = modeNext;
}
//============================================================================================
//フェード取得
//============================================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_Fade;
}

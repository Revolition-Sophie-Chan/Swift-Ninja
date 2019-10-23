//=============================================================================
//
// ポリゴン処理[scene2D.cpp]
// Author：tanaka rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "input.h"
#include "inputkeyboard.h"
#include "camera.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CScene2D::CScene2D(OBJECT_TYPE type) :CScene(type)
{
	m_pTexture = NULL;//テクスチャへのポインタ
	m_pVtxBuff = NULL;//頂点バッファへのポインタ
	CScene2D::m_CountAnim = NULL;
	CScene2D::nPattenAnim = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Size_X = 0.0f;
	m_Size_Y = 0.0f;
	m_bDraw = true;


}
//=============================================================================
//デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
void CScene2D::Init(void)
{

	m_fRot = 0.0f;
	m_nCountRot = 0;

	m_CountAnim = 0;
	nPattenAnim = 0;

	// キーボードの取得
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	//デバイスの取得

	VERTEX_2D *pVtx;//頂点情報へのポインタ
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_Size_X, -m_Size_Y, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_Size_X, -m_Size_Y, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_Size_X, m_Size_Y, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_Size_X, m_Size_Y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	////テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データのアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
//=============================================================================
// polygon更新処理
//=============================================================================
void CScene2D::Update(void)
{

	VERTEX_2D *pVtx;//頂点情報へのポインタ
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	CCamera *pCamera = CCamera::GetCamera();

	D3DXVECTOR3 CameraPos = pCamera->GetCameraPos();

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(m_Size_X*sinf(atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot + D3DX_PI),
		m_Size_Y*cosf(atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot + D3DX_PI), 0.0f) + CameraPos;

	pVtx[1].pos = m_pos + D3DXVECTOR3(m_Size_X*sinf(-atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot + D3DX_PI),
		m_Size_Y*cosf(-atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot + D3DX_PI), 0.0f) + CameraPos;

	pVtx[2].pos = m_pos + D3DXVECTOR3(m_Size_X*sinf(-atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot),
		m_Size_Y*cosf(-atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot), 0.0f) + CameraPos;

	pVtx[3].pos = m_pos + D3DXVECTOR3(m_Size_X*sinf(atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot),
		m_Size_Y*cosf(atan2f(m_Size_X / 2, m_Size_Y / 2) + m_fRot), 0.0f) + CameraPos;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データのアンロック
	m_pVtxBuff->Unlock();

}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CScene2D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	if (m_bDraw)
	{
		//頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		//バックバッファとフロントバッファの入れかえ
		pDevice->SetFVF(FVF_VERTEX_2D);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


		//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	}

}
//=============================================================================
// テクスチャを設定
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 m_pSetTexture)
{
	m_pTexture = m_pSetTexture;
}

//=============================================================================
// アニメーション
//=============================================================================
void CScene2D::SetAnim(int nNumber, int nPatten, int nStage)
{
	VERTEX_2D *pVtx;
	float nHeight;
	nHeight = 1 / (float)nNumber;
	//↑キャスト括弧内の変数型に変更できる
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nStage == 0)//上の段
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + nPatten*nHeight, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nHeight + nPatten*nHeight, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nPatten*nHeight, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(nHeight + nPatten*nHeight, 0.5f);
	}
	else if (nStage == 1)//下の段
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + nPatten*nHeight, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(nHeight + nPatten*nHeight, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nPatten*nHeight, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nHeight + nPatten*nHeight, 1.0f);
	}
	else if (nStage == 2)//全体
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + nPatten*nHeight, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nHeight + nPatten*nHeight, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + nPatten*nHeight, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nHeight + nPatten*nHeight, 1.0f);
	}

	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ポジションの設定
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//=============================================================================
// ムーブの設定
//=============================================================================
void CScene2D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}
//=============================================================================
// 回転の設定
//=============================================================================
void CScene2D::SetRot(float m_rot)
{
	m_fRot = m_rot;
}
//=============================================================================
// カラー設定
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
//=============================================================================
// サイズ設定
//=============================================================================
void CScene2D::SetSize(float fSize_X, float fSize_Y)
{
	m_Size_X = fSize_X;
	m_Size_Y = fSize_Y;
}
//=============================================================================
// 設定
//=============================================================================
void CScene2D::SetRadius(float Radius)
{
	m_Radius = Radius;
}

//=============================================================================
// ライフ設定
//=============================================================================
void CScene2D::SetLife(int nLife)
{
	m_Life = nLife;
}

//=============================================================================
// ゲージ
//=============================================================================
void CScene2D::SetGauge(float nWight, float nHeight)
{
	VERTEX_2D *pVtx;

	CCamera *pCamera = CCamera::GetCamera();
	D3DXVECTOR3 CameraPos = pCamera->GetCameraPos();
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f) + CameraPos;
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + nWight, m_pos.y, 0.0f) + CameraPos;
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + nHeight, 0.0f) + CameraPos;
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + nWight, m_pos.y + nHeight, 0.0f) + CameraPos;

	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ポジションの取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
// ムーブの取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetMove(void)
{
	return m_move;
}
//=============================================================================
// 回転の取得
//=============================================================================
float CScene2D::GetRot(void)
{
	return m_fRot;
}
//=============================================================================
// カラーの取得
//=============================================================================
D3DXCOLOR CScene2D::GetColor(void)
{
	return m_col;
}
//=============================================================================
// サイズの取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetSize(void)
{
	return D3DXVECTOR3(m_Size_X, m_Size_Y, 0.0f);
}

//=============================================================================
// ライフの取得
//=============================================================================
int CScene2D::GetLife(void)
{
	return m_Life;
}

//=============================================================================
// 背景動く処理
//=============================================================================
void CScene2D::TextureMove(void)
{
	CPlayer *pPlayer = CPlayer::GetPlayer();

	float move;

	if (CPlayer::bFever == false)
	{
		move = 0.0005f;
	}
	else
	{
		move = 0.03f;
	}
	m_Movetex += move;
	VERTEX_2D *pVtx;
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].tex = D3DXVECTOR2(0.0f + m_Movetex, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + m_Movetex, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_Movetex, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + m_Movetex, 1.0f);

	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// テクスチャ初期化
//=============================================================================
void CScene2D::InitTex(int Height, float Weight)
{
	float nHeight;
	nHeight = 1 / (float)Height;
	VERTEX_2D *pVtx;
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nHeight, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, Weight);
	pVtx[3].tex = D3DXVECTOR2(nHeight, Weight);
	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

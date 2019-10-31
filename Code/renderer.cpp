//=============================================================================
//
// レンダラー処理[renderer.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include"renderer.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;				//Direct3Dオブジェクトのポインタ
	m_pD3DDevice = NULL;	//Direct3Dデバイスのポインタ
}

//=============================================================================
//デストラクタ
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	m_pFont = NULL;
	D3DDISPLAYMODE d3ddm;			// ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	// プレゼンテーションパラメータ

	m_Fade = new CFade;
									// Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// バックバッファの形式
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ(Ｚバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;									// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート(現在の速度に合わせる)
																//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル(VSyncを待って描画)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// クライアント領域を直ちに更新する

																// Direct3Dデバイスの生成
																// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,// ディスプレイアダプタ
		D3DDEVTYPE_HAL,						// デバイスタイプ
		hWnd,								// フォーカスするウインドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,// デバイス作成制御の組み合わせ
		&d3dpp,								// デバイスのプレゼンテーションパラメータ
		&m_pD3DDevice)))					// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	//レンダステートパラメータの設定
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);//αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);//αディスとネーションカラーの指定

	//テクスチャステージパラメーターの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	//
	D3DXCreateFont(m_pD3DDevice,
		30,
		20,
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"HG行書体",
		&m_pFont);
#endif
	m_Fade->InitFade();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRenderer::Uninit()
{
	m_Fade->UninitFade();
	CScene::ReleaseAll();

	if (m_pD3D != NULL)
	{//Direct3Dオブジェクトの開放
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	if (m_pD3D != NULL)
	{//Direct3Dデバイスの開放
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CRenderer::UpDate(void)
{
	m_Fade->UpdateFade();
	CScene::UpdateAll();
}

//=============================================================================
// びょうが処理
//=============================================================================
void CRenderer::Draw(void)
{
	//バックバッファ＆Zバッファのクリア
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene::DrawAll();
#ifdef _DEBUG
		//
		DrawFPS();
#endif
		//描画の終了
		m_pD3DDevice->EndScene();
	}
	m_Fade->DrawFade();
	//バックバッファとフロントバッファの入れかえ
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// FPSの取得
//=============================================================================
#ifdef _DEBUG
//FPS表示
void CRenderer::DrawFPS(void)
{
	m_FPS = GetFPS();

	RECT rect = { 0,0,1280,720 };
	char aStr[256];
	wsprintf(&aStr[0], "FPS:%d\nプレイヤーの状態%d\nモーション%d", m_FPS, CPlayer::State, CPlayer::MState);

	m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
}
#endif
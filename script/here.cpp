//=============================================================================
//
// ポインターの処理[Here.cpp]
// Author：tanaka rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "renderer.h"
#include "here.h"
#include "enemy.h"
#include "explosion.h"
#include "inputkeyboard.h"
#include "scene2D.h"
#include "effect.h"
#include "player.h"
#include "input.h"
#include "gamepad.h"
#include "texture.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CHere::m_pTextureHere=NULL;

//=============================================================================
//マクロ定義
//=============================================================================
#define HITSIZE_X (200)
#define HITSIZE_Y (200)
#define ROLL_SPEED (0.03f)

//=============================================================================
//コンストラクタ
//=============================================================================
CHere::CHere(OBJECT_TYPE type = OBJECT_TYPE_POINTER) : CScene2D(type)
{
}
//=============================================================================
//デストラクタ
//=============================================================================
CHere::~CHere()
{

}

//=============================================================================
// クリエイト
//=============================================================================
CHere *CHere::Create()
{
	CHere *pHere;
	pHere = new CHere(OBJECT_TYPE_POINTER);
	pHere->Init();
	pHere->BindTexture(m_pTextureHere);
	return pHere;
}

//=============================================================================
// 初期化処理
//=============================================================================
void CHere::Init()
{

	bHere = false;
	CScene2D::Init();
	// ポジションの取得
	CPlayer *pPlayer = CPlayer::GetPlayer();
	m_Playerpos = pPlayer->GetPosition();

	SetObjType(CScene::OBJECT_TYPE_POINTER);
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CHere::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// ポリゴン更新処理
//=============================================================================
void CHere::Update(void)
{


	CScene2D::Update();

	// キーボードの取得
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	// キーボードの取得
	CGamepad *pGamepad = CManager::GetGamePad();

	//サイズ設定
	SetSize(60.0f, 60.0f);
	// プレイヤーの取得
	CPlayer *pPlayer = CPlayer::GetPlayer();

	m_Playerpos = pPlayer->GetPosition();//プレイヤーのポジションを取得

	if (m_Playerpos.y <= 0.0f)
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		bHere = true;
	}
	else
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	SetPosition(D3DXVECTOR3(m_Playerpos.x,50.0f,0.0f));

}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CHere::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// ロード
//=============================================================================
HRESULT CHere::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Here.png", &m_pTextureHere);
	return S_OK;
}
//=============================================================================
// アンロード
//=============================================================================
void CHere::Unload(void)
{

		if (m_pTextureHere != NULL)
		{
			m_pTextureHere->Release();
			m_pTextureHere = NULL;
		}

}

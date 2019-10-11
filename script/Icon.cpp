//=============================================================================
//
// アイコンの処理[Icon.cpp]
// Author：tanaka rikiya
//
//=============================================================================
#include "renderer.h"
#include "Icon.h"
#include "enemy.h"
#include "explosion.h"
#include "inputkeyboard.h"
#include "scene2D.h"
#include "effect.h"
#include "player.h"
#include "input.h"

LPDIRECT3DTEXTURE9 CIcon::m_pTextureIcon= {};
//=============================================================================
//こンストラクタ
//=============================================================================
CIcon::CIcon(OBJECT_TYPE type = OBJECT_TYPE_UI) : CScene2D(type)
{
	//m_pTextureIcon[MAX_TEXTURE] = {};//テクスチャへのポインタ
}
//=============================================================================
//デストラクタ
//=============================================================================
CIcon::~CIcon()
{

}

//=============================================================================
// クリエイト
//=============================================================================
CIcon *CIcon::Create(D3DXVECTOR3 Iconpos)
{
	CIcon *pIcon;
	pIcon = new CIcon(OBJECT_TYPE_UI);
	pIcon->Init();
	pIcon->SetPosition(Iconpos);
	pIcon->BindTexture(m_pTextureIcon);
	return pIcon;
}

//=============================================================================
// 初期化処理
//=============================================================================
void CIcon::Init()
{
	CScene2D::Init();
	bFlag = true;
	SetObjType(CScene::OBJECT_TYPE_UI);
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CIcon::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// ポリゴン更新処理
//=============================================================================
void CIcon::Update(void)
{
	//サイズ設定
	SetSize(70.0f, 70.0f);

	// キーボードの取得
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	//プレイヤーの取得
	CPlayer *pPlayer = CPlayer::GetPlayer();

	bFlag = pPlayer->GetPlayerAttackFlag();

	if (bFlag == true)
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	}
	CScene2D::Update();
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CIcon::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// ロード
//=============================================================================
HRESULT CIcon::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Ability_Icon.png", &m_pTextureIcon);
	return S_OK;
}
//=============================================================================
// アンロード
//=============================================================================
void CIcon::Unload(void)
{
	if (m_pTextureIcon != NULL)
	{
		m_pTextureIcon->Release();
		m_pTextureIcon = NULL;
	}
}


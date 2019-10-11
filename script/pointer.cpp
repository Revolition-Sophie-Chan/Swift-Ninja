//=============================================================================
//
// ポインターの処理[pointer.cpp]
// Author：tanaka rikiya
//
//=============================================================================
#include "renderer.h"
#include "pointer.h"
#include "enemy.h"
#include "explosion.h"
#include "inputkeyboard.h"
#include "scene2D.h"
#include "effect.h"
#include "player.h"
#include "input.h"
#include "gamepad.h"

LPDIRECT3DTEXTURE9 CPointer::m_pTexturePointer = 0;

//=============================================================================
//マクロ定義
//=============================================================================
#define HITSIZE_X (200)
#define HITSIZE_Y (200)
#define ROLL_SPEED (0.03f)

//=============================================================================
//こンストラクタ
//=============================================================================
CPointer::CPointer(OBJECT_TYPE type = OBJECT_TYPE_POINTER) : CScene2D(type)
{
}
//=============================================================================
//デストラクタ
//=============================================================================
CPointer::~CPointer()
{

}

//=============================================================================
// クリエイト
//=============================================================================
CPointer *CPointer::Create()
{
	CPointer *pPointer;
	pPointer = new CPointer(OBJECT_TYPE_POINTER);
	pPointer->Init();
	pPointer->BindTexture(m_pTexturePointer);
	return pPointer;
}

//=============================================================================
// 初期化処理
//=============================================================================
void CPointer::Init()
{
	CScene2D::Init();
	//PointRot = 0.0f;
	//SetRot(PointRot);
	// ポジションの取得
	CPlayer *pPlayer = CPlayer::GetPlayer();
	m_Playerpos = pPlayer->GetPosition();
	PointRot = D3DX_PI * 1.0f;
	SetRot(PointRot);

	SetObjType(CScene::OBJECT_TYPE_POINTER);
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CPointer::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// ポリゴン更新処理
//=============================================================================
void CPointer::Update(void)
{
	// キーボードの取得
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	// キーボードの取得
	CGamepad *pGamepad = CManager::GetGamePad();

	//サイズ設定
	SetSize(60.0f, 60.0f);
	// プレイヤーの取得
	CPlayer *pPlayer = CPlayer::GetPlayer();

	m_Playerpos = pPlayer->GetPosition();//プレイヤーのポジションを取得
	
	m_Playerpos += D3DXVECTOR3(sinf(PointRot) * 100, cosf(PointRot) * 100, 0.0f);//プレイヤーから少し離れた位置にポインターを配置

	//プレイヤーの位置を中心として回転する
	if (pInputKeyborad->GetKeyboardPress(DIK_RIGHT))
	{//右
		RotSet(0.5f);
		if ( pInputKeyborad->GetKeyboardPress(DIK_UP))
		{//右上
			RotSet(0.75f);
		}
		else if ( pInputKeyborad->GetKeyboardPress(DIK_DOWN))
		{//右下
			RotSet(0.25f);
		}
	}
	else if (pInputKeyborad->GetKeyboardPress(DIK_LEFT))
	{//左
		RotSet(-0.5f);

		if (pInputKeyborad->GetKeyboardPress(DIK_UP))
		{//左上
			RotSet(-0.75f);
		}
		else if (pInputKeyborad->GetKeyboardPress(DIK_DOWN))
		{//左上
			RotSet(-0.25f);
		}
	}
	else if (pInputKeyborad->GetKeyboardPress(DIK_UP))
	{//上
		RotSet(1.0f);
	}

	else if (pInputKeyborad->GetKeyboardPress(DIK_DOWN))
	{//下
		RotSet(0.0f);
	}

	else if (pInputKeyborad->GetKeyboardPress(DIK_E))
	{//右に矢印が移動する
		m_Playerpos -= D3DXVECTOR3(sinf(D3DX_PI*ROLL_SPEED), cosf(D3DX_PI*ROLL_SPEED), 0.0f);
		PointRot -= D3DX_PI * ROLL_SPEED;
		pPlayer->SetAttackRot(PointRot);//PointRotをプレイヤーの攻撃方向に指定
		SetRot(PointRot);				//PointRotの方向にテクスチャを回転
	}

	else if (pInputKeyborad->GetKeyboardPress(DIK_Q))
	{//左に矢印が移動する
		m_Playerpos += D3DXVECTOR3(sinf(D3DX_PI*ROLL_SPEED), cosf(D3DX_PI*ROLL_SPEED), 0.0f);
		PointRot += D3DX_PI * ROLL_SPEED;
		pPlayer->SetAttackRot(PointRot);//PointRotをプレイヤーの攻撃方向に指定
		SetRot(PointRot);				//PointRotの方向にテクスチャを回転
	}

	//-------------------------------------------------
	float Stick_X, Stick_Y;
	pGamepad->GetStickRight(0, &Stick_X, &Stick_Y);		//右スティックのXとYを取得している
	if (fabsf(Stick_X) >= 3000 ||fabsf(Stick_Y) >= 3000)
	{// ↑絶対値として計算(3000と-3000どっちも)
		PointRot = atan2f(Stick_X, -Stick_Y);
		//			↑二つの点の角度を求めてくれる
		pPlayer->SetAttackRot(PointRot);
		SetRot(PointRot);
	}
	//-------------------------------------------------
	SetPosition(m_Playerpos);

	CScene2D::Update();

}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CPointer::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// 角度設定
//=============================================================================
void CPointer::RotSet(float fRot)
{
	// ポジションの取得
	CPlayer *pPlayer = CPlayer::GetPlayer();
	m_Playerpos += D3DXVECTOR3(sinf(D3DX_PI*fRot), cosf(-D3DX_PI*fRot), 0.0f);
	PointRot = D3DX_PI * fRot;
	pPlayer->SetAttackRot(PointRot);
	SetRot(PointRot);
}
//=============================================================================
// ロード
//=============================================================================
HRESULT CPointer::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/pointer.png", &m_pTexturePointer);
	return S_OK;
}
//=============================================================================
// アンロード
//=============================================================================
void CPointer::Unload(void)
{

	if (m_pTexturePointer != NULL)
	{
		m_pTexturePointer -> Release();
		m_pTexturePointer = NULL;
	}
}

//=============================================================================
//
// 爆発の処理[explosion.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "renderer.h"
#include "explosion.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTextureExplosion[EXPLOSIONTYPE_MAX] = {};

//=============================================================================
//マクロ定義
//=============================================================================
#define EXPLOSION_ANIM		(3)	//アニメーションの早さ
#define JUMPEXPLOSION_ANIM	(4)	//アニメーションの早さ

//============================================================================================
//コンストラクタ
//============================================================================================
CExplosion::CExplosion(OBJECT_TYPE type = OBJECT_TYPE_EXPLOSION) : CScene2D(type)
{
}
//============================================================================================
//デストラクタ
//============================================================================================
CExplosion::~CExplosion()
{
}

//=============================================================================
//生成処理
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 EPpos,int nLife,int nCount, EXPLOSIONTYPE nType)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion(OBJECT_TYPE_EXPLOSION);
	pExplosion->ExplosionType = nType;
	pExplosion->SetPosition(EPpos);
	pExplosion->SetLife(nLife);
	pExplosion->Init();
	pExplosion->InitTex(nCount, 1.0f);
	pExplosion->BindTexture(m_pTextureExplosion[nType]);
	return pExplosion;
}

//=============================================================================
//爆発の種類取得
//=============================================================================
CExplosion::EXPLOSIONTYPE CExplosion::GetType()
{
	return ExplosionType;
}

//=============================================================================
//初期化処理
//=============================================================================
void CExplosion::Init()
{
	CScene2D::Init();

	m_nLife = CScene2D::GetLife();
	nCountExplosionAnim		= 0;
	nPattenExplosionAnim	= 0;
}

//=============================================================================
//終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//爆発更新処理
//=============================================================================
void CExplosion::Update(void)
{
	// ポジションの取得
	D3DXVECTOR3 pos = GetPosition();
	m_nLife--;
	nCountExplosionAnim++;

	//爆発のタイプによってサイズやアニメーションを変える
	TypeManager();

	CScene2D::Update();
}

//=============================================================================
//描画
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
//ロード
//=============================================================================
HRESULT CExplosion::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/explosion001.png", &m_pTextureExplosion[EXPLOSIONTYPE_ENEMY]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/jump_effect.png", &m_pTextureExplosion[EXPLOSIONTYPE_JUMP]);

	return S_OK;
}

//=============================================================================
//アンロード
//=============================================================================
void CExplosion::Unload(void)
{
	for (int nCnt = 0; nCnt < EXPLOSIONTYPE_MAX; nCnt++)
	{
		if (m_pTextureExplosion[nCnt] != NULL)
		{
			m_pTextureExplosion[nCnt]->Release();
			m_pTextureExplosion[nCnt] = NULL;
		}
	}
}

//=============================================================================
//爆発更新処理
//=============================================================================
void CExplosion::TypeManager(void)
{
	switch (ExplosionType)
	{
		//敵が爆発
	case EXPLOSIONTYPE_ENEMY:
		SetSize(80.0f, 80.0f);
		if (nCountExplosionAnim % EXPLOSION_ANIM == 0)
		{
			nPattenExplosionAnim = (nPattenExplosionAnim + 1) % 16;
			SetAnim(16, nPattenExplosionAnim, 2);
			if (nCountExplosionAnim / EXPLOSION_ANIM == 16)
			{
				Release();
			}
		}
		break;

		//二段ジャンプ時のエフェクト
	case EXPLOSIONTYPE_JUMP:
		SetSize(60.0f, 60.0f);
		if (nCountExplosionAnim % JUMPEXPLOSION_ANIM == 0)
		{
			nPattenExplosionAnim = (nPattenExplosionAnim + 1) % 4;
			SetAnim(4, nPattenExplosionAnim, 2);
			if (nCountExplosionAnim / JUMPEXPLOSION_ANIM == 4)
			{
				Release();
			}
		}
		break;
	}
}


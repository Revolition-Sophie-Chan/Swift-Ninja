//=============================================================================
//
// 爆発の処理[Explosion.cpp]
// Author：tanaka rikiya
//
//=============================================================================
#include"renderer.h"
#include"Explosion.h"
#include "inputkeyboard.h"
#include "Scene2D.h"


//=============================================================================
//マクロ定義
//=============================================================================
#define EXPLOSION_ANIM (4)
#define JUMPEXPLOSION_ANIM (4)

LPDIRECT3DTEXTURE9 CExplosion::m_pTextureExplosion[EXPLOSIONTYPE_MAX] = {};
//============================================================================================
//こンストラクタ
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
// クリエイト
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
// 爆発の種類取得
//=============================================================================

CExplosion::EXPLOSIONTYPE CExplosion::GetType()
{
	return ExplosionType;
}

//=============================================================================
// 初期化処理
//=============================================================================
void CExplosion::Init()
{
	CScene2D::Init();
	nPattenExplosionAnim = 0;
	nCountExplosionAnim = 0;
	m_nLife = CScene2D::GetLife();
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 爆発更新処理
//=============================================================================
void CExplosion::Update(void)
{
	// ポジションの取得
	m_pos = GetPosition();

	m_pos += m_move;
	m_nLife--;
	nCountExplosionAnim++;
	// ポジションの更新
	//SetPosition(pos);
	if (ExplosionType == EXPLOSIONTYPE_ENEMY)
	{
		SetSize(80.0f, 80.0f);
		if (nCountExplosionAnim % EXPLOSION_ANIM == 0)
		{
			nPattenExplosionAnim = (nPattenExplosionAnim + 1) % 16;
			SetAnim(16, nPattenExplosionAnim, 2);
		}
		if (m_nLife <= 0)
		{
			Release();
		}
	}
	else if (ExplosionType == EXPLOSIONTYPE_JUMP)
	{
		SetSize(60.0f, 60.0f);
		if (nCountExplosionAnim % JUMPEXPLOSION_ANIM == 0)
		{
			nPattenExplosionAnim = (nPattenExplosionAnim + 1) % 4;
			SetAnim(4, nPattenExplosionAnim, 2);
			if (nCountExplosionAnim / JUMPEXPLOSION_ANIM==4)
			{
				Release();
			}
		}
	}
	else if (ExplosionType == EXPLOSIONTYPE_TIME)
	{
		m_move.y += 5.0f;
		SetSize(55.0f, 55.0f);
		if (m_nLife <= 0)
		{
			Release();
		}
	}
	CScene2D::Update();

}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// ロード
//=============================================================================
HRESULT CExplosion::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/explosion001.png", &m_pTextureExplosion[EXPLOSIONTYPE_ENEMY]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/jump_effect.png", &m_pTextureExplosion[EXPLOSIONTYPE_JUMP]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/10second.png", &m_pTextureExplosion[EXPLOSIONTYPE_TIME]);

	return S_OK;
}
//=============================================================================
// アンロード
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


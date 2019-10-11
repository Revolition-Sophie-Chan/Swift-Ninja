//=============================================================================
//
// 弾の処理[bullet.cpp]
// Author：tanaka rikiya
//
//=============================================================================
#include "renderer.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "inputkeyboard.h"
#include "Scene2D.h"
#include "effect.h"
#include "particle.h"

LPDIRECT3DTEXTURE9 CBullet::m_pTextureBullet[MAX_TEXTURE] = {};
//=============================================================================
//こンストラクタ
//=============================================================================
CBullet::CBullet(OBJECT_TYPE type = OBJECT_TYPE_EXPLOSION) : CScene2D(type)
{
	m_pTextureBullet[MAX_TEXTURE] = {};//テクスチャへのポインタ
}
//=============================================================================
//デストラクタ
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// クリエイト
//=============================================================================
CBullet *CBullet::Create()
{
	CBullet *pBullet;
	pBullet = new CBullet(OBJECT_TYPE_EXPLOSION);
	pBullet->Init();
	pBullet->BindTexture(m_pTextureBullet[0]);
	return pBullet;
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CBullet::CollisionTest(D3DXVECTOR3 pos)
{
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene, OBJECT_TYPE_ENEMY);
		if (pScene != NULL)
		{
			CScene::OBJECT_TYPE objType;

			objType = pScene->GetObjType();

			if (objType == CScene::OBJECT_TYPE_ENEMY)
			{
				D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetEnemyPos();
				if (EnemyPos.x + HITSIZE_X / 2 >= pos.x &&
					EnemyPos.x - HITSIZE_X / 2 <= pos.x &&
					EnemyPos.y + HITSIZE_Y / 2 >= pos.y &&
					EnemyPos.y - HITSIZE_Y / 2 <= pos.y)
				{
					CExplosion *pExplosion = CExplosion::Create(EnemyPos);
					pExplosion->SetPosition(pos);
					pScene->Release();
				}
			}
		}
	}
	return false;
}

//=============================================================================
// エフェクトの作成
//=============================================================================
void CBullet::MakeEffect(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXCOLOR col = GetColor();
	// エフェクトの生成
	CEffect *pEffect = CEffect::Create(pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 0, 100);
	pEffect->SetPosition(pos);
	pEffect->SetColor(col);
	//pEffect->SetSize();
}

//=============================================================================
//　爆発の作成
//=============================================================================
void CBullet::MakeExplosion(void)
{
	D3DXVECTOR3 pos = GetPosition();
	// 爆発の生成
	CExplosion *pExplosion = CExplosion::Create(pos);
	pExplosion->SetPosition(pos);
}

//=============================================================================
// 初期化処理
//=============================================================================
void CBullet::Init()
{
	CScene2D::Init();
	SetObjType(CScene::OBJECT_TYPE_EXPLOSION);
	m_nLife = 100;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// polygon更新処理
//=============================================================================
void CBullet::Update(void)
{	
	// ポジションの取得
	D3DXVECTOR3 pos = GetPosition();

	// エフェクトの作成
	MakeEffect();

	// 移動処理
	m_move.y -= 0.5f;
	pos += m_move;

	// ポジションの更新
	SetPosition(pos);
	CScene2D::Update();

	// ライフをデクリメント
	m_nLife--;
	if (m_nLife <= 0)
	{// 爆発の作成
		MakeExplosion();
		// 開放処理
		Release();
	}

	// 当たり判定
	CollisionTest(pos);
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// ロード
//=============================================================================
HRESULT CBullet::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/KSTW.png", &m_pTextureBullet[0]);
	return S_OK;
}
//=============================================================================
// アンロード
//=============================================================================
void CBullet::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_pTextureBullet[nCnt] != NULL)
		{
			m_pTextureBullet[nCnt]->Release();
			m_pTextureBullet[nCnt] = NULL;
		}
	}

}


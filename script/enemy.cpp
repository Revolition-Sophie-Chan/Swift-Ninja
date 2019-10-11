//=============================================================================
//
// 敵の処理[enemy.cpp]
// Author：tanaka rikiya
//
//=============================================================================
#include "renderer.h"
#include "input.h"
#include "enemy.h"
#include "manager.h"
#include "inputkeyboard.h"
#include "Scene2D.h"
#include "player.h"
#include "explosion.h"
#include "hit.h"
#include "score.h"
#include "effect.h"
#include "camera.h"
#include "game.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 CEnemy::m_apTexturePolygon = NULL;

//=============================================================================
//マクロ定義
//=============================================================================
#define ENEMY_MOVEANIM (8)
#define UNDYING_TIME	(10)	//無敵時間

//=============================================================================
//こンストラクタ
//=============================================================================
CEnemy::CEnemy(OBJECT_TYPE type = OBJECT_TYPE_ENEMY) : CScene2D(type)
{

}
//=============================================================================
//デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
void CEnemy::Init(void)
{
	CScene2D::Init();
	SetObjType(CScene::OBJECT_TYPE_ENEMY);
	m_Life = CScene2D::GetLife();
	nCountCamera = 0;
	nPattenEnemyAnim = 0;
	nCountEnemyAnim = 0;

}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// polygon更新処理
//=============================================================================
void CEnemy::Update(void)
{
	//CEffect::Create(D3DXVECTOR3(m_pos.x + rand() % 50 - 20, m_pos.y + rand() % 100 - 50, 0.0f),  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(1.0f, 1.0f, 0.0f), 20, 20, 1,60);

	SetSize(65.0f, 65.0f);
	CScene2D::Update();

	nCountEnemyAnim++;

	CPlayer *pPlayer = CPlayer::GetPlayer();

	m_pos = CScene2D::GetPosition();

	//pPlayer=
	m_move = GetMove();

	m_pos += m_move;

	//重力
	//m_move.y += 0.5f;

	//ジャンプ減速
	m_move.x += (0 - m_move.x)*0.5f;

	// キーボードの取得
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	//慣性
	m_move.x = (m_move.x)*0.9f;
	m_move.y = (m_move.y)*0.9f;

	D3DXVECTOR3 PlayerPos = 
		GetPosition();
	if (m_move.x >= 0.1f)
	{
		nDirectionEnemyMove = 0;
	}
	else if (m_move.x <= -0.1f)
	{
		nDirectionEnemyMove = 1;
	}
	if (nDirectionEnemyMove == 1)
	{
		if (nCountEnemyAnim % ENEMY_MOVEANIM == 0)
		{
			nPattenEnemyAnim = (nPattenEnemyAnim + 1) % 4;
			SetAnim(4, nPattenEnemyAnim, 1);
		}
	}
	else
	{
		if (nCountEnemyAnim % ENEMY_MOVEANIM == 0)
		{
			nPattenEnemyAnim = (nPattenEnemyAnim + 1) % 4;
			SetAnim(4, nPattenEnemyAnim, 0);
		}
	}
	switch (EnemyState)
	{
	case ENEMYSTATE_NORMAL:
		break;
	case ENEMYSTATE_UNDYING:
		nCountDamage++;
		if (nCountDamage % 5 == 0 && nCountDamage % 10 != 0)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		else if (nCountDamage % 10 == 0)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (nCountDamage >= UNDYING_TIME)
		{
			EnemyState = ENEMYSTATE_NORMAL;
			nCountDamage = 0;
		}
		break;

	}
	//範囲外
	if (m_pos.y >= 750)
	{
		Release();
	}
	else if (m_pos.x <= -100)
	{
		Release();
	}	
	else if (m_pos.x >= 1380)
	{
		Release();
	}
	CScene2D::SetPosition(m_pos);


	//if (pInputKeyborad->GetKeyboardPress(DIK_RETURN))
	//{
	//	MakeParticle();
	//}

}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 Epos, D3DXVECTOR3 Emove,int Elife)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy(OBJECT_TYPE_ENEMY);
	pEnemy->SetPosition(Epos);
	pEnemy->SetMove(Emove);
	pEnemy->SetLife(Elife);
	pEnemy->Init();
	pEnemy->InitTex(4, 0.5f);
	pEnemy->BindTexture(m_apTexturePolygon);

	return pEnemy;
}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CEnemy::HitEnemy(int Damage)
{
	CSound *pSound = CManager::GetSound();
	CNumber *pNumber;
	pNumber = CScore::GetaScore();
	CPlayer *pPlayer = CPlayer::GetPlayer();

	m_Life += Damage;
	if (m_Life <= 0)
	{
		CHit::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 0,5);
		CHit::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1,10);
		CHit::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2,10);

		((CScore*)pNumber)->AddScore(1);

		MakeParticle();
		pSound->PlaySound(CSound::SOUND_LABEL_SE_KO);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_BOMB);
		CExplosion *pExplosion = CExplosion::Create(m_pos,60,16,CExplosion::EXPLOSIONTYPE_ENEMY);
		pExplosion->SetPosition(m_pos);

		CPlayer::bShake = true;
		Release();
	}
	else
	{
		EnemyState = ENEMYSTATE_UNDYING;
	}
}

//=============================================================================
// ロード
//=============================================================================
HRESULT CEnemy::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/shadow_enemy00.png", &m_apTexturePolygon);
	return S_OK;
}
//=============================================================================
// アンロード
//=============================================================================
void CEnemy::Unload(void)
{

	if (m_apTexturePolygon != NULL)
	{
		m_apTexturePolygon->Release();
		m_apTexturePolygon = NULL;
	}
}
//=============================================================================
// ポジション取得
//=============================================================================
D3DXVECTOR3 CEnemy::GetEnemyPos(void)
{
	return m_pos;
}

//=============================================================================
// 状態取得
//=============================================================================

CEnemy::ENEMYSTATE CEnemy::GetEnemyState(void)
{
	return EnemyState;
}
//=============================================================================
// エネミー取得
//=============================================================================
CEnemy * CEnemy::GetEnemy(void)
{
	return m_pEnemy;
}
//=============================================================================
// パーティクル
//=============================================================================
void CEnemy::MakeParticle(void)
{

	float fAngle = 0.0f;
	float fSpeed = 0.0f;
	////////////////////////////////////////////////////

	for (int nCnt = 0; nCnt < 60; nCnt++)
	{
		// 出す向き
		fAngle = float(rand() % 314) / 20.0f - float(rand() % 314) / 20.0f;	// 全方向出す
		D3DXVECTOR3 move0 = D3DXVECTOR3(sinf(fAngle)*(fSpeed + rand() % 12 + 5.0f), cosf(fAngle)*(fSpeed + rand() % 12 + 5.0f), 0.0f);
		D3DXVECTOR3 move1 = D3DXVECTOR3(sinf(fAngle)*fSpeed, 0.0f, cosf(fAngle)*fSpeed);
		D3DXVECTOR3 move2 = D3DXVECTOR3(0.0f, sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed);
		CEffect::Create(m_pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), move0, 9, 2, 10);
	}
}

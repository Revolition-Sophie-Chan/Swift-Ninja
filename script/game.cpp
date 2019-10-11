//=============================================================================
//
// ゲーム本編の処理[game.cpp]
// Author：tanaka rikiya
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"scene2D.h"
#include"game.h"
#include"player.h"
#include"inputkeyboard.h"
#include"bullet.h"
#include"bg.h"
#include"effect.h"
#include"enemy.h"
#include"explosion.h"
#include"pointer.h"
#include"Icon.h"
#include"fade.h"
#include"hit.h"
#include"number.h"
#include"score.h"
#include"camera.h"
#include "gauge.h"
#include"load.h"
#include"save.h"
#include"texture.h"
#include"time.h"
#include"gamepad.h"
#include"here.h"

CGame *CGame::m_pGame = NULL;
bool CGame::bDamage = NULL;
bool CGame::bPause = NULL;
#define DAMAGE_STOP (5)
//=============================================================================
//静的メンバ変数
//=============================================================================
//=============================================================================
//コンストラクタ
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
void CGame::Init(void)
{

	nCountGame = 0;
	nCountTime = 0;
	nCountDamage = 0;

	CPlayer::Load();
	CPointer::Load();
	CExplosion::Load();
	CEffect::Load();
	CEnemy::Load();
	CIcon::Load();
	CHit::Load();
	CNumber::Load();
	CTexture::Load();
	CHere::Load();
	CGauge::Load();
	CBg::Load();

	CSave::Create();
	CLoad::Create();
	CCamera::Create();
	CPlayer::Create(D3DXVECTOR3(505.0f, 200.0f, 0.0f),6);
	CPointer::Create();
	CHere::Create();
	CIcon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 60, 0.0f));
	CBg::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	CScore::Create(0);
	CTime::Create(100);
	CHit::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 0, 20);
	CHit::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 1, 20);
	CHit::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 2 ,20);

	CTexture::Create(D3DXVECTOR3(1225.0f, 685.0f, 0.0f), 70, 50, CTexture::TYPE_KO);
	CTexture::Create(D3DXVECTOR3(30.0f, 660.0f, 0.0f), 80, 50, CTexture::TYPE_HP);
	CTexture::Create(D3DXVECTOR3(360.0f, 660.0f, 0.0f), 83, 60, CTexture::TYPE_TIME);
	CTexture::Create(D3DXVECTOR3(SCREEN_WIDTH/2+83.0f, 670.0f, 0.0f), 88, 80, CTexture::TYPE_FEVER);
	CTexture::Create(D3DXVECTOR3(-700.0f, 400.0f, 0.0f), 610, 150, CTexture::TYPE_IN_FEVER01);
	CTexture::Create(D3DXVECTOR3(1900.0f, 200.0f, 0.0f), 610, 150, CTexture::TYPE_IN_FEVER02);
	CTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50.0f, 0.0f), 350, 300, CTexture::TYPE_FINISH);


	CGauge::Create(D3DXVECTOR3(770.0f, 635.0f, 0.0f), D3DXCOLOR(0.2f, 0.0f, 0.0f, 1.0f), 10, 50, CGauge::UITYPE_FEVERMAX);
	CGauge::Create(D3DXVECTOR3(770.0f,635.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 50, CGauge::UITYPE_FEVER);
	CGauge::Create(D3DXVECTOR3(60.0f, 635.0f, 0.0f), D3DXCOLOR(0.2f, 0.0f, 0.0f, 1.0f), 40, 50, CGauge::UITYPE_HPMAX);
	CGauge::Create(D3DXVECTOR3(60.0f, 635.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, 50, CGauge::UITYPE_HP);

	bDamage = false;
	bPause = false;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	CPlayer::Unload();
	CEnemy::Unload();
	CEffect::Unload();
	CExplosion::Unload();
	CPointer::Unload();
	CHere::Unload();
	CIcon::Unload();
	CBg::Unload();
	CHit::Unload();
	CNumber::Unload();
	CGauge::Unload();
	CTexture::Unload();

}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{

	CNumber *pNumber;
	pNumber = CTime::GetaTime();
	CPlayer *pPlayer = CPlayer::GetPlayer();
	CGamepad *pGamePad = CManager::GetGamePad();

	if (CPlayer::bFinish == false)
	{
		nCountTime++;
		nCountGame++;
	}
	// キーボードの取得
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	CCamera *pCamera = CCamera::GetCamera();
	if (bDamage == false && bPause == false)
	{
		if (pInputKeyborad->GetKeyboardTrigger(DIK_R) && CManager::GetMode() != CManager::MODE_TITLE)
		{
			CFade::SetFade(CManager::MODE_GAME);
		}
#ifdef _DEBUG
		if (pInputKeyborad->GetKeyboardTrigger(DIK_F))
		{
			if (CPlayer::bFever == true)
			{
				CPlayer::bFever = false;
			}
			else
			{
				CPlayer::bFever = true;
			}
		}
#endif

		if (nCountGame % 50 == 0)
		{
			CEnemy::Create(D3DXVECTOR3(rand() % 1280 + 302.0f, 0.0f, 0.0f), D3DXVECTOR3(rand() % 1 - 2.0f, 2.0f, 0.0f), 1);
		}
		if (nCountGame % 140 == 0)
		{
			CEnemy::Create(D3DXVECTOR3(rand() % 400 + 0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 0.0f), 1);
		}
		if (nCountGame % 200 == 0)
		{
			CEnemy::Create(D3DXVECTOR3(1280.0f, rand() % 300 + 270.0f, 0.0f), D3DXVECTOR3(rand() % 1 - 3.0f, 0.0f, 0.0f), 1);
		}
		if (CPlayer::bFever == true)
		{
			if (nCountGame % 3 == 0)
			{
				CEnemy::Create(D3DXVECTOR3(rand() % 1280 - 2.0f, 0.0f, 0.0f), D3DXVECTOR3(rand() % 8 - 4.0f, 4.0f, 0.0f), 1);
			}
			if (nCountGame % 11 == 0)
			{
				CEnemy::Create(D3DXVECTOR3(rand() % 400 + 0.0f, 0.0f, 0.0f), D3DXVECTOR3(rand() % 8 + 0.0f, 4.0f, 0.0f), 1);
			}
		}
		if (nCountTime % 40 == 0)
		{
			((CTime*)pNumber)->AddTime(-1);
		}
		if (pInputKeyborad->GetKeyboardPress(DIK_P) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START))
		{
			if (CPlayer::PlayerState != CPlayer::PLAYERSTATE_FINISH || CPlayer::PlayerState != CPlayer::PLAYERSTATE_DEATH)
			{
				bPause = true;
			}
		}
	}

	else
	{
		if (bDamage == true)
		{
			nCountDamage++;
			if (nCountDamage >= DAMAGE_STOP)
			{
				bDamage = false;
				nCountDamage = 0;
			}
		}
		else
		{
			if (pInputKeyborad->GetKeyboardPress(DIK_P) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START))
			{
				bPause = false;
			}
		}
	}
}
//=============================================================================
// びょうが処理
//=============================================================================
void CGame::Draw(void)
{

}
//=============================================================================
// クリエイト
//=============================================================================
CGame * CGame::Create()
{
	CGame *pGame;
	pGame = new CGame;
	pGame->Init();
	return pGame;
}

CGame * CGame::GetGame(void)
{
	return m_pGame;
}

bool CGame::GetPause(void)
{
	return bPause;
}

bool CGame::GetDamage(void)
{
	return bDamage;
}

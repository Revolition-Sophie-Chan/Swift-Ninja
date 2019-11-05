//=============================================================================
//
// ゲーム本編の処理[game.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "game.h"
#include "player.h"
#include "inputkeyboard.h"
#include "bg.h"
#include "effect.h"
#include "enemy.h"
#include "explosion.h"
#include "pointer.h"
#include "icon.h"
#include "fade.h"
#include "hit.h"
#include "score.h"
#include "camera.h"
#include  "gauge.h"
#include "load.h"
#include "save.h"
#include "texture.h"
#include "time.h"
#include "gamepad.h"
#include "here.h"
#include "sound.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
CGame *CGame::m_pGame = NULL;

//=============================================================================
//マクロ定義
//=============================================================================
#define SHAKE_COUNT (20)

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
//生成処理
//=============================================================================
CGame * CGame::Create()
{
	CGame *pGame;
	pGame = new CGame;
	pGame->Init();
	return pGame;
}

//=============================================================================
//初期化処理
//=============================================================================
void CGame::Init(void)
{
	nCountGame	 = 0;
	nCountTime	 = 0;
	nCountDamage = 0;
	nCountCamera = 0;

	//テクスチャをロード
	 LoadAll();

	CBg::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	CSave::Create();
	CLoad::Create();
	CCamera::Create();
	CPlayer::Create(D3DXVECTOR3(505.0f, 200.0f, 0.0f),6);
	CPointer::Create();
	CHere::Create();
	CIcon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 60, 0.0f));
	CScore::Create(0);
	CTime::Create(100);
	CHit::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 0, 20);
	CHit::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 1, 20);
	CHit::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 2 ,20);

	//画像をクリエイト
	CTexture::Create(D3DXVECTOR3(1225.0f, 685.0f, 0.0f), 70, 50, CTexture::TYPE_KO);
	CTexture::Create(D3DXVECTOR3(30.0f, 660.0f, 0.0f), 80, 50, CTexture::TYPE_HP);
	CTexture::Create(D3DXVECTOR3(360.0f, 660.0f, 0.0f), 83, 60, CTexture::TYPE_TIME);
	CTexture::Create(D3DXVECTOR3(SCREEN_WIDTH/2+83.0f, 670.0f, 0.0f), 88, 80, CTexture::TYPE_FEVER);
	CTexture::Create(D3DXVECTOR3(-700.0f, 400.0f, 0.0f), 610, 150, CTexture::TYPE_IN_FEVER01);
	CTexture::Create(D3DXVECTOR3(1900.0f, 200.0f, 0.0f), 610, 150, CTexture::TYPE_IN_FEVER02);
	CTexture::Create(D3DXVECTOR3(550.0f, 660.0f, 0.0f), 65, 65, CTexture::TYPE_10PLUS);
	CTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50.0f, 0.0f), 350, 300, CTexture::TYPE_FINISH);

	//ゲージをクリエイト
	CGauge::Create(D3DXVECTOR3(770.0f, 635.0f, 0.0f), D3DXCOLOR(0.2f, 0.0f, 0.0f, 1.0f), 10, 50, CGauge::UITYPE_FEVERMAX);
	CGauge::Create(D3DXVECTOR3(770.0f,635.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 50, CGauge::UITYPE_FEVER);
	CGauge::Create(D3DXVECTOR3(60.0f, 635.0f, 0.0f), D3DXCOLOR(0.2f, 0.0f, 0.0f, 1.0f), 40, 50, CGauge::UITYPE_HPMAX);
	CGauge::Create(D3DXVECTOR3(60.0f, 635.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, 50, CGauge::UITYPE_HP);
}

//=============================================================================
//終了処理
//=============================================================================
void CGame::Uninit(void)
{
	CBg			::Unload();
	CHit		::Unload();
	CHere		::Unload();
	CIcon		::Unload();
	CGauge		::Unload();
	CEnemy		::Unload();
	CEffect		::Unload();
	CPlayer		::Unload();
	CNumber		::Unload();
	CPointer	::Unload();
	CTexture	::Unload();
	CExplosion	::Unload();
}

//=============================================================================
//更新処理
//=============================================================================
void CGame::Update(void)
{
	CNumber *pNumber;
	pNumber = CTime::GetaTime();
	
	//プレイヤーの取得
	CPlayer *pPlayer = CPlayer::GetPlayer();

	//サウンド取得
	CSound *pSound = CManager::GetSound();

	// キーボードの取得
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	//ゲームパッドの取得
	CGamepad *pGamePad = CManager::GetGamePad();

	//カメラの取得
	CCamera *pCamera = CCamera::GetCamera();

	//敵を出現させる
	EnemySpawn();

	//画面を揺らす
	CameraShake();

	if (CPlayer::bFinish == false)
	{
		nCountTime++;
		nCountGame++;
	}
	//40フレームごとに残り時間を1ずつ減らす
	if (nCountTime % 40 == 0)
	{
		((CTime*)pNumber)->AddTime(-1);
	}
	//ポーズ
	if (pInputKeyborad->GetKeyboardTrigger(DIK_P) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START))
	{
		if (CPlayer::PlayerState != CPlayer::PLAYERSTATE_FINISH && CPlayer::PlayerState != CPlayer::PLAYERSTATE_DEATH)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			CManager::SetPause(CManager::MODE_PAUSE);
		}
	}
//+++++++++++++++++++++++++++デバッグキー+++++++++++++++++++++++++++
#ifdef _DEBUG
	if (pInputKeyborad->GetKeyboardTrigger(DIK_F))
	{//フィーバーモードに強制的に移行または解除
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
}

//=============================================================================
//描画処理
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
//ゲーム取得
//=============================================================================
CGame * CGame::GetGame(void)
{
	return m_pGame;
}

//=============================================================================
//画面が揺れる処理
//=============================================================================
void CGame::CameraShake(void)
{
	if (CPlayer::bShake == true)
	{
		nCountCamera++;
		if (nCountCamera % 3 == 0)
		{
			CCamera::MoveCamera(D3DXVECTOR3(rand() % 16 - 8.0f, rand() % 16 - 8.0f, 0.0f));
		}
		if (nCountCamera >= SHAKE_COUNT)
		{
			CCamera::ResetCamera();
			CPlayer::bShake = false;
			nCountCamera = 0;
		}
	}
}

//=============================================================================
//敵を生成する処理
//=============================================================================
void CGame::EnemySpawn(void)
{
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
}

//=============================================================================
//全てロード
//=============================================================================
void CGame::LoadAll(void)
{
	CBg			::Load();
	CHit		::Load();
	CIcon		::Load();
	CHere		::Load();
	CGauge		::Load();
	CEnemy		::Load();
	CPlayer		::Load();
	CNumber		::Load();
	CEffect		::Load();
	CPointer	::Load();
	CTexture	::Load();
	CExplosion	::Load();
}

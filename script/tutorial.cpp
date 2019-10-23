//=============================================================================
//
// チュートリアルの処理[Tutorial.cpp]
// Author：tanaka rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"scene2D.h"
#include"Tutorial.h"
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

//=============================================================================
//コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
void CTutorial::Init(void)
{
	State = TUTORIALSTATE_NORMAL;
	nCountTutorial = 0;
	nCountTime = 0;

	CPlayer::Load();
	CPointer::Load();
	CExplosion::Load();
	CEffect::Load();
	CEnemy::Load();
	CIcon::Load();
	CHit::Load();
	CNumber::Load();
	CGauge::Load();
	CTexture::Load();
	CHere::Load();
	CBg::Load();

	CPlayer::Create(D3DXVECTOR3(105.0f, 200.0f, 0.0f),6);
	CPointer::Create();
	CIcon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 60, 0.0f));
	CBg::Create(D3DXVECTOR3(640.0f, 350.0f, 0.0f));
	CScore::Create(0);
	CHere::Create();
	CTime::Create(999);

	CTexture::Create(D3DXVECTOR3(1225.0f, 685.0f, 0.0f), 70, 50, CTexture::TYPE_KO);
	CTexture::Create(D3DXVECTOR3(30.0f, 660.0f, 0.0f), 80, 50, CTexture::TYPE_HP);
	CTexture::Create(D3DXVECTOR3(360.0f, 660.0f, 0.0f), 83, 60, CTexture::TYPE_TIME);
	CTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 83.0f, 670.0f, 0.0f), 88, 80, CTexture::TYPE_FEVER);
	CTexture::Create(D3DXVECTOR3(780.0f, 105.0f, 0.0f), 560.0f, 256.0f, CTexture::TYPE_TUTORIAL00);
	CTexture::Create(D3DXVECTOR3(780.1f, 310.0f, 0.0f), 560.0f, 256.0f, CTexture::TYPE_TUTORIAL01);
	CTexture::Create(D3DXVECTOR3(780.1f, 515.0f, 0.0f), 560.0f, 256.0f, CTexture::TYPE_TUTORIAL02);
	CTexture::Create(D3DXVECTOR3(140.0f, 125.0f, 0.0f), 150.0f, 75.0f, CTexture::TYPE_START);

	CGauge::Create(D3DXVECTOR3(770.0f, 635.0f, 0.0f), D3DXCOLOR(0.2f, 0.0f, 0.0f, 1.0f), 10, 50, CGauge::UITYPE_FEVERMAX);
	CGauge::Create(D3DXVECTOR3(770.0f,635.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 50, CGauge::UITYPE_FEVER);
	CGauge::Create(D3DXVECTOR3(60.0f, 635.0f, 0.0f), D3DXCOLOR(0.2f, 0.0f, 0.0f, 1.0f), 40, 50, CGauge::UITYPE_HPMAX);
	CGauge::Create(D3DXVECTOR3(60.0f, 635.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, 50, CGauge::UITYPE_HP);

}

//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	CPlayer::Unload();
	CEnemy::Unload();
	CEffect::Unload();
	CExplosion::Unload();
	CPointer::Unload();
	CIcon::Unload();
	CBg::Unload();
	CHit::Unload();
	CNumber::Unload();
	CGauge::Unload();
	CTexture::Unload();
	CHere::Unload();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{
	CPlayer *pPlayer = CPlayer::GetPlayer();

	CCamera *pCamera = CCamera::GetCamera();

	CGamepad *pGamePad = CManager::GetGamePad();
	// キーボードの取得
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	if (pInputKeyborad->GetKeyboardTrigger(DIK_RETURN) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_START))
	{
		CFade::SetFade(CManager::MODE_GAME);
	}

}
//=============================================================================
// びょうが処理
//=============================================================================
void CTutorial::Draw(void)
{

}
//=============================================================================
// クリエイト
//=============================================================================
CTutorial * CTutorial::Create()
{
	CTutorial *pTutorial;
	pTutorial = new CTutorial;
	pTutorial->Init();
	return pTutorial;
}

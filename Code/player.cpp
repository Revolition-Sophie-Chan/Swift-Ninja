//=============================================================================
//
// プレイヤー処理[player.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include <time.h>
#include "renderer.h"
#include "player.h"
#include "inputkeyboard.h"
#include "pointer.h"
#include "effect.h"
#include "enemy.h"
#include "explosion.h"
#include "hit.h"
#include "camera.h"
#include "gamepad.h"
#include "game.h"
#include "score.h"
#include "gauge.h"
#include "save.h"
#include "load.h"
#include "time.h"
#include "texture.h"
#include "sound.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_apTexturePolygon[MAX_PLAYER] = {};

CSave *CPlayer::m_Save		= NULL;
CLoad *CPlayer::m_Load		= NULL;
CEnemy *CEnemy::m_pEnemy	= NULL;
CPlayer *CPlayer::m_pPlayer = NULL;
int CPlayer::State			= NULL;
int CPlayer::nFever			= NULL;
int CPlayer::MState			= NULL;
int CPlayer::nScore			= NULL;
bool CPlayer::bRoof			= NULL;
bool CPlayer::bShake		= NULL;
bool CPlayer::bFever		= NULL;
bool CPlayer::bFinish		= NULL;
bool CPlayer::bRankScore	= NULL;
CPlayer::PLAYERSTATE CPlayer::PlayerState = CPlayer::PLAYERSTATE_NORMAL;

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_PLAYER_TEXTURE	(20)	//プレイヤーキャラクターの読み込むテクスチャの最大数
#define PLAYER_SIZE_X		(80)	//プレイヤーキャラクターのXのサイズ
#define PLAYER_SIZE_Y		(80)	//プレイヤーキャラクターのYのサイズ
#define ABILITY_COOLDOWN	(80)	//スキルのリキャストタイム
#define ABILITY_LASTING		(10)	//攻撃判定持続時間
#define DAMAGE_MOTION		(30)	//のけぞり時間
#define MOVESPEED_WAIT		(6)		//待機アニメーションの早さ
#define MOVESPEED_WALK		(4)		//歩くアニメーションの早さ
#define MOVESPEED_ATTACK	(3)		//攻撃アニメーションの早さ
#define MOVESPEED_JUMP		(4)		//ジャンプアニメーションの早さ
#define JUMP_HEIGHT			(45.0f)	//ジャンプの高さ
#define DOUBLEJUMP_HEIGHT	(35.0f)	//二段ジャンプの高さ
#define UNDYING_TIME		(60)	//無敵時間
#define FADE_TIME			(100)	//倒されたときフェードするまでの時間
#define FEVER_TIME			(500)	//Feverタイムの時間
#define FEVER_COUNT			(30)	//Feverタイム突入に必要な撃破数

//=============================================================================
//コンストラクタ
//=============================================================================
CPlayer::CPlayer(OBJECT_TYPE type = OBJECT_TYPE_PLAYER) : CScene2D(type)
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
//生成処理
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 Playerpos, int nLife)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer(OBJECT_TYPE_PLAYER);
	m_pPlayer = pPlayer;
	pPlayer->BindTexture(m_apTexturePolygon[PLAYERMOVESTATE_WAIT]);
	pPlayer->SetLife(nLife);
	pPlayer->SetPosition(Playerpos);
	pPlayer->Init();
	return pPlayer;
}

//=============================================================================
//初期化
//=============================================================================
void CPlayer::Init(void)
{
	CScene2D::Init();
	SetObjType(CScene::OBJECT_TYPE_PLAYER);

	nScore = 0;
	nFever = 0;
	m_Color0	 = 0;
	m_Color1	 = 0;
	m_Color2	 = 0;
	m_randColor0 = 0;
	m_randColor1 = 0;
	m_randColor2 = 0;
	nLife			= CScene2D::GetLife();
	nPattenAnim		= 0;
	nDirectionMove	= 0;
	nCountAnim		= 0;
	nCountFade		= 0;
	nCountFever		= 0;
	nCountAttack	= 0;
	nCountDamage	= 0;
	nCountCoolDown	= 0;
	nCountCoolTime	= 0;
	MoveState		= PLAYERMOVESTATE_WAIT;
	PlayerState		= PLAYERSTATE_NORMAL;
	m_AttackRot		= D3DX_PI;
	bRoof			= false;
	bJump			= false;
	bFever			= false;
	bFinish			= false;
	bRankScore		= false;
	bDoubleJump		= false;
	bDoubleJumpAnim	= false;
	bAttack			= true;
}

//=============================================================================
//終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CPlayer::Update(void)
{
	CNumber *pTime;

	//時間の取得
	pTime = CTime::GetaTime();

	//エネミーの取得
	CEnemy *pEnemy = CEnemy::GetEnemy();

	//カメラの取得
	CCamera *pCamera = CCamera::GetCamera();

	//サイズ設定
	SetSize(PLAYER_SIZE_X, PLAYER_SIZE_Y);

	CScene2D::Update();

	//重力
	m_move.y += 1.0f;

	//ジャンプ減速
	m_move.x += (0 - m_move.x)*0.5f;

	// ポジションの取得
	m_pos = GetPosition();

	//慣性
	m_move.x = (m_move.x)*0.9f;
	m_move.y = (m_move.y)*0.9f;

	m_pos += m_move;

	nCountAnim++;

	//当たり判定
	CollisionPlayer(m_pos);

	//プレイヤーの動き
	PlayerMove();

	//プレイヤーの状態遷移
	PlayerStateChange();

	//プレイヤーのモーション
	PlayerAnim();

	//プレイヤーの場所
	PlayerPosition();

	//フィーバータイム中
	FeverTime();

	//ゲーム中に時間が0になったら終わる
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		if (((CTime*)pTime)->m_nTime == 0)
		{
			if (PlayerState != PLAYERSTATE_DEATH)
			{
				PlayerState = PLAYERSTATE_FINISH;
			}
		}
	}
	//ポジションの更新
	CScene2D::SetPosition(m_pos);

	//ライフの更新
	CScene2D::SetLife(nLife);
#ifdef _DEBUG
	State = static_cast<int>(PlayerState);
	MState = static_cast<int>(MoveState);
#endif
}

//=============================================================================
//描画
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
//ロード
//=============================================================================
HRESULT CPlayer::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Player/New_Hero_Stand.png", &m_apTexturePolygon[PLAYERMOVESTATE_WAIT]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Player/New_Hero_run002.png", &m_apTexturePolygon[PLAYERMOVESTATE_MOVE]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Player/New_Hero_jump.png", &m_apTexturePolygon[PLAYERMOVESTATE_JUMPUP]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Player/New_Hero_jump_Down.png", &m_apTexturePolygon[PLAYERMOVESTATE_JUMPDOWN]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Player/New_Hero_Ability.png", &m_apTexturePolygon[PLAYERMOVESTATE_ATTACK]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Player/New_Hero_Wjump.png", &m_apTexturePolygon[PLAYERMOVESTATE_DOUBLEJUMP]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Player/New_Hero_damage.png", &m_apTexturePolygon[PLAYERMOVESTATE_DAMAGE]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Player/New_Hero_death.png", &m_apTexturePolygon[PLAYERMOVESTATE_DEATH]);
	return S_OK;
}

//=============================================================================
//アンロード
//=============================================================================
void CPlayer::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (m_apTexturePolygon[nCnt] != NULL)
		{
			m_apTexturePolygon[nCnt]->Release();
			m_apTexturePolygon[nCnt] = NULL;
		}
	}
}

//=============================================================================
//回転設定
//=============================================================================
void CPlayer::SetAttackRot(float AttackRot)
{
	m_AttackRot = AttackRot;
}

//=============================================================================
//ポジション取得
//=============================================================================
D3DXVECTOR3 CPlayer::GetPlayerPos(void)
{
	return m_pos;
}

//=============================================================================
//攻撃中判定
//=============================================================================
bool CPlayer::GetPlayerAttackFlag(void)
{
	return bAttack;
}

//=============================================================================
//ダメージ処理
//=============================================================================
void CPlayer::HitPlayer(int nDamege)
{
	nLife += nDamege;
	CHit::Create(D3DXCOLOR(0.7f, 0.0f, 0.0f, 0.7f), 0, 10);
	if (nLife <= 0)
	{
		PlayerState = PLAYERSTATE_DEATH;
	}
	else
	{
		PlayerState = PLAYERSTATE_DAMAGE;
	}
}

//=============================================================================
//当たり判定
//=============================================================================
bool CPlayer::CollisionPlayer(D3DXVECTOR3 pos)
{
	CEnemy *pEnemy = CEnemy::GetEnemy();
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
				//敵との接触判定
				if (PlayerState == PLAYERSTATE_NORMAL&&bFever == false)
				{//STATENORMALの時は敵に接触するとダメージを受ける
					D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetEnemyPos();
					if (EnemyPos.x + PLAYER_SIZE_X / 2 >= pos.x &&
						EnemyPos.x - PLAYER_SIZE_X / 2 <= pos.x &&
						EnemyPos.y + PLAYER_SIZE_Y / 2 >= pos.y &&
						EnemyPos.y - PLAYER_SIZE_Y / 2 <= pos.y)
					{
						HitPlayer(-1);
					}
				}
				//攻撃判定
				else if (PlayerState == PLAYERSTATE_ATK)
				{
					D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetEnemyPos();
					if (EnemyPos.x + PLAYER_SIZE_X >= pos.x &&
						EnemyPos.x - PLAYER_SIZE_X <= pos.x &&
						EnemyPos.y + PLAYER_SIZE_Y >= pos.y &&
						EnemyPos.y - PLAYER_SIZE_Y <= pos.y)
					{
						nScore += 1;
						nFever += 1;
						bAttack = true;
						((CEnemy*)pScene)->HitEnemy(-1);
					}
				}
			}
		}
	}
	return false;
}

//=============================================================================
//プレイヤー取得
//=============================================================================
CPlayer *CPlayer::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
//プレイヤーの操作
//=============================================================================
void CPlayer::PlayerMove(void)
{
	//サウンドの取得
	CSound *pSound = CManager::GetSound();

	// キーボードの取得
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	//ゲームパッドの取得
	CGamepad *pGamePad = CManager::GetGamePad();

	if (PlayerState != PLAYERSTATE_DAMAGE && PlayerState != PLAYERSTATE_DEATH)
	{
		if (bJump == false && bDoubleJumpAnim == false && m_move.y <= 0.1f&&PlayerState != PLAYERSTATE_ATK&&MoveState != PLAYERMOVESTATE_DOUBLEJUMP)
		{//上昇中
			MoveState = PLAYERMOVESTATE_JUMPUP;
		}

		else if (bJump == false && m_move.y >= 0.1f&&PlayerState != PLAYERSTATE_ATK)
		{//下降中
			MoveState = PLAYERMOVESTATE_JUMPDOWN;
		}

		else if (MoveState != PLAYERMOVESTATE_DOUBLEJUMP)
		{//二段ジャンプ
			MoveState = PLAYERMOVESTATE_WAIT;
			SetAnim(4, nPattenAnim, nDirectionMove);
		}

		//待機中
		if (MoveState == PLAYERMOVESTATE_WAIT)
		{
			if (m_move.x > 0.1f)
			{
				MoveState = PLAYERMOVESTATE_MOVE;
				nDirectionMove = 0;
			}
			else if (m_move.x < -0.1f)
			{
				MoveState = PLAYERMOVESTATE_MOVE;
				nDirectionMove = 1;
			}
		}
		//------------------------キー入力------------------------
		float Stick_X, Stick_Y;
		pGamePad->GetStickLeft(0, &Stick_X, &Stick_Y);

		if (PlayerState != PLAYERSTATE_FINISH)
		{
			if (pInputKeyborad->GetKeyboardPress(DIK_A) || pGamePad->GetPress(0, CGamepad::JOYPADKEY_LEFT) ||
				Stick_X <= -3000)
			{
				m_move.x -= 8.6f;
			}
			else if (pInputKeyborad->GetKeyboardPress(DIK_D) || pGamePad->GetPress(0, CGamepad::JOYPADKEY_RIGHT) ||
				Stick_X >= 3000)
			{
				m_move.x += 8.6f;
			}

			//ジャンプ
			if (bJump == true)
			{
				if (pInputKeyborad->GetKeyboardTrigger(DIK_W) ||
					pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_LEFT_TRIGGER) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_LEFT_SHOULDER))
				{
					m_move.y -= JUMP_HEIGHT;
					bJump = false;
					bDoubleJump = true;
				}
			}
			//二段ジャンプ
			else if (bDoubleJump == true && PlayerState != PLAYERSTATE_ATK)
			{
				if (pInputKeyborad->GetKeyboardTrigger(DIK_W) ||
					pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_LEFT_TRIGGER) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_LEFT_SHOULDER))
				{
					CExplosion *pExplosion = CExplosion::Create(m_pos, 20, 4, CExplosion::EXPLOSIONTYPE_JUMP);
					pExplosion->SetPosition(m_pos);
					pSound->PlaySound(CSound::SOUND_LABEL_SE_JUMP);
					SetAnim(4, nPattenAnim, nDirectionMove);
					MoveState = PLAYERMOVESTATE_DOUBLEJUMP;
					m_move.y = 0.0f;
					m_move.y -= DOUBLEJUMP_HEIGHT;
					bDoubleJump = false;
					bDoubleJumpAnim = true;
				}
			}

			//突進攻撃
			if (bAttack == true)
			{
				if (pInputKeyborad->GetKeyboardTrigger(DIK_SPACE) ||
					pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_RIGHT_TRIGGER) || pGamePad->GetTrigger(0, CGamepad::JOYPADKEY_RIGHT_SHOULDER))
				{
					SetAnim(4, nPattenAnim, nDirectionMove);
					PlayerState = PLAYERSTATE_ATK;
					pSound->PlaySound(CSound::SOUND_LABEL_SE_ATK);
					m_move = D3DXVECTOR3(sinf(m_AttackRot) * 400.5f, cosf(m_AttackRot) * 50.5f, 0.0f);
					bAttack = false;
				}
			}

			else
			{
				nCountCoolDown++;
				if (nCountCoolDown >= ABILITY_COOLDOWN + ABILITY_LASTING)
				{
					bAttack = true;
					nCountCoolDown = 0;
				}
			}
		}
	}
}

//=============================================================================
//プレイヤーの状態遷移の管理
//=============================================================================
void CPlayer::PlayerStateChange(void)
{
	m_Color0 = rand() % 10 + 1;
	m_randColor0 = (float)m_Color0;
	m_randColor0 /= 10;
	m_Color1 = rand() % 10 + 1;
	m_randColor1 = (float)m_Color1;
	m_randColor1 /= 10;
	m_Color2 = rand() % 10 + 1;
	m_randColor2 = (float)m_Color2;
	m_randColor2 /= 10;

	switch (PlayerState)
	{
		//通常状態
	case PLAYERSTATE_NORMAL:
		SetRot(0.0f);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		nCountDamage = 0;
		break;

		//攻撃中
	case PLAYERSTATE_ATK:
		bDoubleJump = true;		//二段ジャンプが復活する
		SetRot(m_AttackRot);
		MoveState = PLAYERMOVESTATE_ATTACK;
		nCountAttack++;

		CEffect::Create(D3DXVECTOR3(m_pos.x + rand() % 50 - 20, m_pos.y + rand() % 100 - 50, 0.0f), D3DXCOLOR(m_randColor0, m_randColor1, m_randColor2, 1.0f), D3DXVECTOR3(sinf(m_AttackRot)*-1.0f, cosf(m_AttackRot)*-1.0f, 0.0f), 20, 1, 60);
		CEffect::Create(D3DXVECTOR3(m_pos.x + rand() % 50 - 20, m_pos.y + rand() % 100 - 50, 0.0f), D3DXCOLOR(m_randColor1, m_randColor2, m_randColor0, 1.0f), D3DXVECTOR3(sinf(m_AttackRot)*-1.0f, cosf(m_AttackRot)*-1.0f, 0.0f), 20, 1, 60);

		if (nCountAttack >= ABILITY_LASTING)
		{
			SetRot(0.0f);
			PlayerState = PLAYERSTATE_COOLDOWN;
		}
		break;

		//スキルが使えない状態
	case PLAYERSTATE_COOLDOWN:
		nCountAttack = 0;
		nCountCoolTime++;
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		if (nCountCoolTime >= ABILITY_COOLDOWN)
		{
			nCountCoolTime = 0;
			PlayerState = PLAYERSTATE_NORMAL;
		}
		break;

		//ダメージを受けたとき
	case PLAYERSTATE_DAMAGE:
		MoveState = PLAYERMOVESTATE_DAMAGE;
		nCountDamage++;
		SetColor(D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f));

		if (nCountDamage >= 30)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			PlayerState = PLAYERSTATE_UNDYING;
			nCountDamage = 0;
		}
		break;

		//ダメージを受けた後の無敵時間
	case PLAYERSTATE_UNDYING:
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
			PlayerState = PLAYERSTATE_NORMAL;
			nCountDamage = 0;
		}
		break;

		//HPがなくなった時
	case PLAYERSTATE_DEATH:
		bFinish = true;
		SetRot(0.0f);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		MoveState = PLAYERMOVESTATE_DEATH;
		nCountFade++;
		if (nCountFade >= FADE_TIME)
		{
			CFade::SetFade(CManager::MODE_RANKING);
			bRankScore = true;	//ランキングに遷移したときに獲得したスコアを表示する
			m_Save->SaveData(nScore);
			m_Load->LoadData();
			nCountFade = 0;
		}
		break;

		//タイマーがゼロになった時
	case PLAYERSTATE_FINISH:
		bFinish = true;
		SetRot(0.0f);
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		nCountFade++;
		if (nCountFade >= FADE_TIME)
		{
			CFade::SetFade(CManager::MODE_RANKING);
			bRankScore = true;	//ランキングに遷移したときに獲得したスコアを表示する
			m_Save->SaveData(nScore);
			m_Load->LoadData();
			nCountFade = 0;
		}
		break;
	}
}

//=============================================================================
//プレイヤーのアニメーションの管理
//=============================================================================
void CPlayer::PlayerAnim(void)
{
	switch (MoveState)
	{
		//待機モーション
	case PLAYERMOVESTATE_WAIT:
		BindTexture(m_apTexturePolygon[PLAYERMOVESTATE_WAIT]);
		if (nLife > 3)
		{
			if (nCountAnim % MOVESPEED_WAIT == 0)
			{
				nPattenAnim = (nPattenAnim + 1) % 4;
				SetAnim(4, nPattenAnim, nDirectionMove);
			}
		}
		else
		{//ライフが少ないと待機モーションが高速化
			if (nCountAnim % 4 == 0)
			{
				nPattenAnim = (nPattenAnim + 1) % 4;
				SetAnim(4, nPattenAnim, nDirectionMove);
			}
		}
		break;

		//移動モーション
	case PLAYERMOVESTATE_MOVE:
		BindTexture(m_apTexturePolygon[PLAYERMOVESTATE_MOVE]);
		if (nCountAnim % MOVESPEED_WALK == 0)
		{
			nPattenAnim = (nPattenAnim + 1) % 4;
			SetAnim(4, nPattenAnim, nDirectionMove);
		}
		break;

		//攻撃中モーション
	case PLAYERMOVESTATE_ATTACK:
		BindTexture(m_apTexturePolygon[PLAYERMOVESTATE_ATTACK]);
		if (nCountAnim % MOVESPEED_ATTACK == 0)
		{
			nPattenAnim = (nPattenAnim + 1) % 4;
			SetAnim(4, nPattenAnim, nDirectionMove);
		}
		break;

		//ジャンプ(上昇中)
	case PLAYERMOVESTATE_JUMPUP:
		BindTexture(m_apTexturePolygon[PLAYERMOVESTATE_JUMPUP]);
		SetAnim(1, nPattenAnim, nDirectionMove);
		break;

		//ジャンプ(下降中)
	case PLAYERMOVESTATE_JUMPDOWN:
		BindTexture(m_apTexturePolygon[PLAYERMOVESTATE_JUMPDOWN]);
		SetAnim(1, nPattenAnim, nDirectionMove);
		break;

		//二段ジャンプ
	case PLAYERMOVESTATE_DOUBLEJUMP:
		if (nCountAnim % MOVESPEED_JUMP == 0)
		{
			nPattenAnim = (nPattenAnim + 1) % 4;
			SetAnim(4, nPattenAnim, nDirectionMove);
		}
		BindTexture(m_apTexturePolygon[PLAYERMOVESTATE_DOUBLEJUMP]);
		break;

		//ダメージモーション
	case PLAYERMOVESTATE_DAMAGE:
		BindTexture(m_apTexturePolygon[PLAYERMOVESTATE_DAMAGE]);
		SetAnim(1, nPattenAnim, nDirectionMove);
		break;

		//戦闘不能
	case PLAYERMOVESTATE_DEATH:
		BindTexture(m_apTexturePolygon[PLAYERMOVESTATE_DEATH]);
		SetAnim(1, nPattenAnim, nDirectionMove);
		break;
	}
}

//=============================================================================
//フィーバータイム関連の処理
//=============================================================================
void CPlayer::FeverTime(void)
{
	CNumber *pTime;
	//時間の取得
	pTime = CTime::GetaTime();

	//サウンドの取得
	CSound *pSound = CManager::GetSound();

	if (bFever == true)
	{
		CTexture::bINFever = true;
		nCountFever++;
		if (nCountFever == 1)
		{
			if (nLife < 6)
			{
				nLife += 1;
			}
			pSound->PlaySound(CSound::SOUND_LABEL_SE_FEVER);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_FEVER2);
			CHit::Create(D3DXCOLOR(0.0f, 1.0f, 0.0f, 5.0f), 3, 50);
		}

		CEffect::Create(D3DXVECTOR3(m_pos.x + rand() % 50 - 20, m_pos.y + rand() % 110 - 30, 0.0f),
			D3DXCOLOR(m_randColor1, m_randColor2, m_randColor0, 1.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20, 1,
			60);

		if (nCountFever % 2 == 0)
		{
			SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		}
		if (nCountFever >= FEVER_TIME)
		{
			bFever = false;
			nCountFever = 0;
			nFever = 0;
		}
	}
	else
	{
		CTexture::bINFever = false;
		nCountFever = 0;
		if (nFever >= FEVER_COUNT)
		{
			((CTime*)pTime)->AddTime(+10);
			bFever = true;
		}
	}
}

//=============================================================================
//プレイヤーの場所管理
//=============================================================================
void CPlayer::PlayerPosition(void)
{
	//移動制限
	if (m_pos.y >= 536)
	{
		m_pos.y = 536;
		//接地判定
		bDoubleJumpAnim = false;
		bJump = true;
	}
	if (m_pos.y < 526)
	{
		bJump = false;
	}

	if (m_pos.x <= 20.0f)
	{
		m_pos.x = 20.0f;
	}
	else if (m_pos.x >= 1260.0f)
	{
		m_pos.x = 1260.0f;
	}

	//プレイヤーが画面外にいるかどうか
	if (m_pos.y <= 0)
	{
		bRoof = true;
	}
	else
	{
		bRoof = false;
	}

	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{//チュートリアル中だけの移動制限
		if (m_pos.x >= 255.0f)
		{
			m_pos.x = 255.0f;
		}
	}
}

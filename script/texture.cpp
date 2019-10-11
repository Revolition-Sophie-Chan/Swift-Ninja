//=============================================================================
//
// 画像表示の処理[texture.cpp]
// Author：tanaka rikiya
//
//=============================================================================
#include"renderer.h"
#include"texture.h"
#include"explosion.h"
#include "inputkeyboard.h"
#include "scene2D.h"
#include"game.h"
#include"player.h"

LPDIRECT3DTEXTURE9 CTexture::m_pTexture[TYPE_MAX] = {};
//=============================================================================
//こンストラクタ
//=============================================================================
CTexture::CTexture(OBJECT_TYPE type = OBJECT_TYPE_BG) : CScene2D(type)
{

}
//=============================================================================
//デストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// クリエイト
//=============================================================================
CTexture *CTexture::Create(D3DXVECTOR3 TEXpos, float Weight, float Height, TEXTURE_TYPE Texture)
{
	CTexture *pTexture;
	pTexture = new CTexture(OBJECT_TYPE_UI);
	pTexture->TextureType = Texture;
	pTexture->SetSize(Weight, Height);
	pTexture->SetPosition(TEXpos);
	pTexture->Init();
	pTexture->InitTex(1, 1.0f);
	pTexture->BindTexture(m_pTexture[Texture]);
	return pTexture;
}
//=============================================================================
// テクスチャのタイプ取得
//=============================================================================

CTexture::TEXTURE_TYPE CTexture::GetTextureType(void)
{
	return TextureType ;
}

//=============================================================================
// 初期化処理
//=============================================================================
void CTexture::Init()
{
	CScene2D::Init();
	nCountTexture = 0;
	bINFever = false;
	//m_Texture = 0;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTexture::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CTexture::Update(void)
{
	CScene2D::Update();
	nCountTexture++;
	m_pos = GetPosition();
	m_pos += m_move;
	CPlayer *pPlayer = CPlayer::GetPlayer();

	if (TextureType == TYPE_ENTER|| TextureType == TYPE_START)
	{
		//点滅
		if (nCountTexture % 20 == 0 && nCountTexture % 40 != 0)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		if (nCountTexture % 40 == 0)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	if (TextureType == TYPE_IN_FEVER01|| TextureType == TYPE_IN_FEVER02)
	{
		if (CPlayer::bFever == true)
		{
			bINFever = true;
		}
		else
		{
			bINFever = false;
		}
		if (bINFever == true)
		{
			if (TextureType == TYPE_IN_FEVER01)
			{
				if (m_pos.x >= 500.0f&& m_pos.x <= 700.0f)
				{
					m_move.x = 2.6f;
				}
				else
				{
					m_move.x = 100.6f;
				}

				if (m_pos.x >= 1780.0f)
				{
					m_move.x = 0.0f;
				}
			}
			if (TextureType == TYPE_IN_FEVER02)
			{
				if (m_pos.x >= 595.0f&& m_pos.x <= 800.0f)
				{
					m_move.x = -2.6f;
				}
				else
				{
					m_move.x = -100.6f;
				}
				if (m_pos.x <= -700.0f)
				{
					m_move.x = 0.0f;
				}
			}
		}
		else 
		{
			if (TextureType == TYPE_IN_FEVER01)
			{
				m_pos = (D3DXVECTOR3(-700.0f, 400.0f, 0.0f));
			}
			else if (TextureType == TYPE_IN_FEVER02)
			{
				m_pos = (D3DXVECTOR3(1900.0f, 200.0f, 0.0f));
			}
		}
	}
	if (TextureType == TYPE_FINISH)
	{
		if (CPlayer::PlayerState == CPlayer::PLAYERSTATE_FINISH|| CPlayer::PlayerState == CPlayer::PLAYERSTATE_DEATH)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}

	SetPosition(m_pos);
	SetMove(m_move);

}
//=============================================================================
// ポリゴンの描画
//=============================================================================
void CTexture::Draw(void)
{
	CScene2D::Draw();
}

HRESULT CTexture::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/title000.png", &m_pTexture[TYPE_BG]);				//タイトル背景
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/2DShooting_TitleLogo.png", &m_pTexture[TYPE_LOGO]);//タイトルロゴ
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/press_enter.png", &m_pTexture[TYPE_ENTER]);		//プレスエンター
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/start.png", &m_pTexture[TYPE_START]);		//プレスエンター
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/ranking.png", &m_pTexture[TYPE_RANKING]);			//ランキングの文字
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/1st.png", &m_pTexture[TYPE_1ST]);					//ランキング用の数字
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/2nd.png", &m_pTexture[TYPE_2ND]);					//ランキング用の数字
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/3rd.png", &m_pTexture[TYPE_3RD]);					//ランキング用の数字
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/4th.png", &m_pTexture[TYPE_4TH]);					//ランキング用の数字
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/5th.png", &m_pTexture[TYPE_5TH]);					//ランキング用の数字
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/rankingCount.png", &m_pTexture[TYPE_RANKCOUNT]);	//倒した数の表記
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/New_Hero_break.png", &m_pTexture[TYPE_BREAK]);		//ランキング中のキャラ
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/KO.png", &m_pTexture[TYPE_KO]);					//撃破数を示す
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/HP.png", &m_pTexture[TYPE_HP]);					//HPバーを示す
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/TIME.png", &m_pTexture[TYPE_TIME]);				//時間制限を示す
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/fever.png", &m_pTexture[TYPE_FEVER]);				//フィーバーゲージを示す
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/in_fever.png", &m_pTexture[TYPE_IN_FEVER01]);		//フィーバー突入演出その1
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/10_count.png", &m_pTexture[TYPE_IN_FEVER02]);		//フィーバー突入演出その2
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Game_set.png", &m_pTexture[TYPE_FINISH]);			//ゲーム終了
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/tutorial.png", &m_pTexture[TYPE_TUTORIAL00]);		//チュートリアル
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/advise.png", &m_pTexture[TYPE_TUTORIAL01]);		//チュートリアル
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/advise2.png", &m_pTexture[TYPE_TUTORIAL02]);		//チュートリアル
	return S_OK;
}
void CTexture::Unload(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

}


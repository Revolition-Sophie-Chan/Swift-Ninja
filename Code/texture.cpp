//=============================================================================
//
// 画像表示の処理[texture.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "renderer.h"
#include "texture.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::m_pTexture[TYPE_MAX] = {};
bool CTexture::bINFever=false;

//=============================================================================
//コンストラクタ
//=============================================================================
CTexture::CTexture(OBJECT_TYPE type = OBJECT_TYPE_UI) : CScene2D(type)
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// 生成処理
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
// 初期化処理
//=============================================================================
void CTexture::Init()
{
	CScene2D::Init();
	nCountTexture = 0;
	Count10Time = 0;
	TimeColor = 1.0f;
	bINFever = false;
}

//=============================================================================
// 終了処理
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

	//ポジションの取得
	m_pos = GetPosition();

	m_pos += m_move;

	//テクスチャの動きなど
	TypeManager();

	//ポジションの更新
	SetPosition(m_pos);

	//ムーブの更新
	SetMove(m_move);

}

//=============================================================================
// 描画
//=============================================================================
void CTexture::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ロード
//=============================================================================
HRESULT CTexture::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/title000.png", &m_pTexture[TYPE_BG]);				//タイトル背景
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/SwiftNinja_TitleLogo.png", &m_pTexture[TYPE_LOGO]);//タイトルロゴ
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/press_enter.png", &m_pTexture[TYPE_ENTER]);		//プレスエンター
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/start.png", &m_pTexture[TYPE_START]);				//ゲームスタート
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
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/10second.png", &m_pTexture[TYPE_10PLUS]);			//フィーバー突入演出その3
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/continue.png", &m_pTexture[TYPE_PAUSECONTINUE]);	//つづける
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/retry.png", &m_pTexture[TYPE_PAUSERETRY]);			//やりなおす
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/quit.png", &m_pTexture[TYPE_PAUSEQUIT]);			//タイトルにもどる
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Game_set.png", &m_pTexture[TYPE_FINISH]);			//ゲーム終了
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/tutorial.png", &m_pTexture[TYPE_TUTORIAL00]);		//チュートリアル
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/advise.png", &m_pTexture[TYPE_TUTORIAL01]);		//チュートリアル
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/advise2.png", &m_pTexture[TYPE_TUTORIAL02]);		//チュートリアル
	return S_OK;
}

//=============================================================================
// テクスチャのアンロード
//=============================================================================
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
//=============================================================================
// テクスチャのタイプ取得
//=============================================================================
CTexture::TEXTURE_TYPE CTexture::GetTextureType(void)
{
	return TextureType;
}

//=============================================================================
// テクスチャのタイプごとの管理
//=============================================================================
void CTexture::TypeManager(void)
{
	switch (TextureType)
	{
	case TYPE_ENTER:
	case TYPE_START:
		//点滅
		if (nCountTexture % 20 == 0 && nCountTexture % 40 != 0)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		if (nCountTexture % 40 == 0)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;

	case TYPE_IN_FEVER01:
		if (bINFever == true)
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
		else
		{
			m_pos = (D3DXVECTOR3(-700.0f, 400.0f, 0.0f));
		}
		break;

	case TYPE_IN_FEVER02:
		if (bINFever == true)
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
		break;

	case TYPE_10PLUS:
		if (bINFever == true)
		{
			Count10Time++;
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, TimeColor));
			m_move.y = -0.4f;
			TimeColor -= 0.02f;
			if (Count10Time >= 70)
			{
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}
		else
		{
			m_pos = D3DXVECTOR3(550.0f, 660.0f, 0.0f);
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			TimeColor = 1.0f;
			Count10Time = 0;
		}
		break;

	case TYPE_FINISH:
		if (CPlayer::PlayerState == CPlayer::PLAYERSTATE_FINISH || CPlayer::PlayerState == CPlayer::PLAYERSTATE_DEATH)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		break;
	}
}


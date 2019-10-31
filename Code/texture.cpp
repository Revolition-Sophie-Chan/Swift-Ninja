//=============================================================================
//
// �摜�\���̏���[texture.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "renderer.h"
#include "texture.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::m_pTexture[TYPE_MAX] = {};
bool CTexture::bINFever=false;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTexture::CTexture(OBJECT_TYPE type = OBJECT_TYPE_UI) : CScene2D(type)
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// ��������
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
// ����������
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
// �I������
//=============================================================================
void CTexture::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CTexture::Update(void)
{
	CScene2D::Update();

	nCountTexture++;

	//�|�W�V�����̎擾
	m_pos = GetPosition();

	m_pos += m_move;

	//�e�N�X�`���̓����Ȃ�
	TypeManager();

	//�|�W�V�����̍X�V
	SetPosition(m_pos);

	//���[�u�̍X�V
	SetMove(m_move);

}

//=============================================================================
// �`��
//=============================================================================
void CTexture::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CTexture::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/title000.png", &m_pTexture[TYPE_BG]);				//�^�C�g���w�i
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/SwiftNinja_TitleLogo.png", &m_pTexture[TYPE_LOGO]);//�^�C�g�����S
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/press_enter.png", &m_pTexture[TYPE_ENTER]);		//�v���X�G���^�[
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/start.png", &m_pTexture[TYPE_START]);				//�Q�[���X�^�[�g
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/ranking.png", &m_pTexture[TYPE_RANKING]);			//�����L���O�̕���
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/1st.png", &m_pTexture[TYPE_1ST]);					//�����L���O�p�̐���
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/2nd.png", &m_pTexture[TYPE_2ND]);					//�����L���O�p�̐���
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/3rd.png", &m_pTexture[TYPE_3RD]);					//�����L���O�p�̐���
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/4th.png", &m_pTexture[TYPE_4TH]);					//�����L���O�p�̐���
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/5th.png", &m_pTexture[TYPE_5TH]);					//�����L���O�p�̐���
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/rankingCount.png", &m_pTexture[TYPE_RANKCOUNT]);	//�|�������̕\�L
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/New_Hero_break.png", &m_pTexture[TYPE_BREAK]);		//�����L���O���̃L����
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/KO.png", &m_pTexture[TYPE_KO]);					//���j��������
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/HP.png", &m_pTexture[TYPE_HP]);					//HP�o�[������
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/TIME.png", &m_pTexture[TYPE_TIME]);				//���Ԑ���������
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/fever.png", &m_pTexture[TYPE_FEVER]);				//�t�B�[�o�[�Q�[�W������
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/in_fever.png", &m_pTexture[TYPE_IN_FEVER01]);		//�t�B�[�o�[�˓����o����1
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/10_count.png", &m_pTexture[TYPE_IN_FEVER02]);		//�t�B�[�o�[�˓����o����2
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/10second.png", &m_pTexture[TYPE_10PLUS]);			//�t�B�[�o�[�˓����o����3
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/continue.png", &m_pTexture[TYPE_PAUSECONTINUE]);	//�Â���
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/retry.png", &m_pTexture[TYPE_PAUSERETRY]);			//���Ȃ���
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/quit.png", &m_pTexture[TYPE_PAUSEQUIT]);			//�^�C�g���ɂ��ǂ�
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Game_set.png", &m_pTexture[TYPE_FINISH]);			//�Q�[���I��
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/tutorial.png", &m_pTexture[TYPE_TUTORIAL00]);		//�`���[�g���A��
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/advise.png", &m_pTexture[TYPE_TUTORIAL01]);		//�`���[�g���A��
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/advise2.png", &m_pTexture[TYPE_TUTORIAL02]);		//�`���[�g���A��
	return S_OK;
}

//=============================================================================
// �e�N�X�`���̃A�����[�h
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
// �e�N�X�`���̃^�C�v�擾
//=============================================================================
CTexture::TEXTURE_TYPE CTexture::GetTextureType(void)
{
	return TextureType;
}

//=============================================================================
// �e�N�X�`���̃^�C�v���Ƃ̊Ǘ�
//=============================================================================
void CTexture::TypeManager(void)
{
	switch (TextureType)
	{
	case TYPE_ENTER:
	case TYPE_START:
		//�_��
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


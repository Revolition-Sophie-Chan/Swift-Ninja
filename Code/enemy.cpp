//=============================================================================
//
// �G�̏���[enemy.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "renderer.h"
#include "enemy.h"
#include "inputkeyboard.h"
#include "explosion.h"
#include "hit.h"
#include "score.h"
#include "effect.h"
#include "camera.h"
#include "game.h"
#include "sound.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_apTexturePolygon = NULL;

//=============================================================================
//�}�N����`
//=============================================================================
#define ENEMY_MOVEANIM	(8)		//�A�j���[�V�����̂͂₳
#define ENEMY_SIZE		(65.0f)	//�G�̃T�C�Y

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(OBJECT_TYPE type = OBJECT_TYPE_ENEMY) : CScene2D(type)
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
//��������
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 Epos, D3DXVECTOR3 Emove, int Elife)
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
//������
//=============================================================================
void CEnemy::Init(void)
{
	CScene2D::Init();
	SetObjType(CScene::OBJECT_TYPE_ENEMY);
	m_Life				= CScene2D::GetLife();
	nCountCamera		= 0;
	nCountEnemyAnim		= 0;
	nPattenEnemyAnim	= 0;
	nDirectionEnemyMove = 0;
	bJump = false;
}

//=============================================================================
//�I������
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CEnemy::Update(void)
{
	SetSize(ENEMY_SIZE, ENEMY_SIZE);

	CScene2D::Update();

	nCountEnemyAnim++;

	//�|�W�V�����̎擾
	m_pos = CScene2D::GetPosition();

	//���[�u�̎擾
	m_move = GetMove();
	m_pos += m_move;

	//�W�����v����
	m_move.x += (0 - m_move.x)*0.5f;

	//����
	m_move.x = (m_move.x)*0.9f;
	m_move.y = (m_move.y)*0.9f;

	//�G�l�~�[�̓���
	EnemyMove();

	//�͈͊O�̓G������
	EnemyRelease();

	//�|�W�V�����̍X�V
	CScene2D::SetPosition(m_pos);
}

//=============================================================================
//�`��
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
//�`��
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
}

//=============================================================================
//���[�h
//=============================================================================
HRESULT CEnemy::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/shadow_enemy00.png", &m_apTexturePolygon);
	return S_OK;
}

//=============================================================================
//�A�����[�h
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
//�|�W�V�����擾
//=============================================================================
D3DXVECTOR3 CEnemy::GetEnemyPos(void)
{
	return m_pos;
}

//=============================================================================
//�G�l�~�[�擾
//=============================================================================
CEnemy * CEnemy::GetEnemy(void)
{
	return m_pEnemy;
}

//=============================================================================
//�p�[�e�B�N��
//=============================================================================
void CEnemy::MakeParticle(void)
{

	float fAngle = 0.0f;
	float fSpeed = 0.0f;
	////////////////////////////////////////////////////

	for (int nCnt = 0; nCnt < 50; nCnt++)
	{
		// �o������
		fAngle = float(rand() % 314) / 20.0f - float(rand() % 314) / 20.0f;	// �S�����o��
		D3DXVECTOR3 move0 = D3DXVECTOR3(sinf(fAngle)*(fSpeed + rand() % 12 + 5.0f), cosf(fAngle)*(fSpeed + rand() % 12 + 5.0f), 0.0f);
		D3DXVECTOR3 move1 = D3DXVECTOR3(sinf(fAngle)*fSpeed, 0.0f, cosf(fAngle)*fSpeed);
		D3DXVECTOR3 move2 = D3DXVECTOR3(0.0f, sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed);
		CEffect::Create(m_pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), move0, 9, 2, 10);
	}
}

//=============================================================================
//�G�̓���
//=============================================================================
void CEnemy::EnemyMove(void)
{
	if (m_move.x >= 0.1f)
	{
		nDirectionEnemyMove = 0;
	}
	else if (m_move.x <= -0.1f)
	{
		nDirectionEnemyMove = 1;
	}
	if (nCountEnemyAnim % ENEMY_MOVEANIM == 0)
	{
		nPattenEnemyAnim = (nPattenEnemyAnim + 1) % 4;
		SetAnim(4, nPattenEnemyAnim, nDirectionEnemyMove);
	}
}

//=============================================================================
//�G�̃����[�X
//=============================================================================
void CEnemy::EnemyRelease(void)
{
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
}

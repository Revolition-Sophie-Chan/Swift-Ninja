//=============================================================================
//
// �v���C���[����[player.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include"manager.h"
#include "scene.h"
#include "scene2D.h"
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CLoad;
class CSave;

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_PLAYER (20)

//=============================================================================
//�v���C���[�̃N���X
//=============================================================================
class CPlayer : public CScene2D
{
public:
	typedef enum
	{//���
		PLAYERSTATE_NORMAL = 0,
		PLAYERSTATE_UNDYING,
		PLAYERSTATE_DAMAGE,
		PLAYERSTATE_JUMPUP,
		PLAYERSTATE_DEATH,
		PLAYERSTATE_ATK,
		PLAYERSTATE_COOLDOWN,
		PLAYERSTATE_FINISH,
		PLAYERSTATE_MAX,
	} PLAYERSTATE;

	typedef enum
	{//�s��
		PLAYERMOVESTATE_WAIT = 0,
		PLAYERMOVESTATE_MOVE,
		PLAYERMOVESTATE_ATTACK,
		PLAYERMOVESTATE_JUMPUP,
		PLAYERMOVESTATE_JUMPDOWN,
		PLAYERMOVESTATE_DOUBLEJUMP,
		PLAYERMOVESTATE_DAMAGE,
		PLAYERMOVESTATE_DEATH,
		PLAYERMOVESTATE_MAX,
	} PLAYERMOVESTATE;

	CPlayer(OBJECT_TYPE type);
	~CPlayer();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer *Create(D3DXVECTOR3 Playerpos,int nLife);
	static CPlayer *GetPlayer(void);
	D3DXVECTOR3 GetPlayerPos(void);
	void SetAttackRot(float AttackRot);
	bool GetPlayerAttackFlag(void);
	void HitPlayer(int nDamege);

	static int State;
	static int MState;
	static int nScore;
	static int nFever;
	static int AnimCount;

	static bool bRoof;
	static bool bShake;
	static bool bFever;
	static bool bFinish;
	static bool bRankScore;

	static PLAYERSTATE PlayerState;

private:
	bool CollisionPlayer(D3DXVECTOR3 pos);
	void PlayerMove(void);
	void PlayerStateChange(void);
	void PlayerAnim(void);
	void PlayerPosition(void);
	void FeverTime(void);

	static LPDIRECT3DTEXTURE9 m_apTexturePolygon[MAX_PLAYER];//�e�N�X�`���ւ̃|�C���^

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 PlayerPos;

	PLAYERMOVESTATE MoveState;

	int	  nLife;
	int	  nCountAnim;
	int	  nCountFade;
	int	  nCountFever;
	int	  nPattenAnim;
	int	  nCountAttack;
	int	  nCountDamage;
	int	  nCountCoolTime;
	int	  nDirectionMove;//�L�����̌���
	int	  nCountCoolDown;
	float m_AttackRot;

	int		m_Color0;
	int		m_Color1;
	int		m_Color2;
	float	m_randColor0;
	float	m_randColor1;
	float	m_randColor2;

	bool bJump;
	bool bAttack;
	bool bDoubleJump;
	bool bDoubleJumpAnim;

	static CSave	*m_Save;
	static CLoad	*m_Load;
	static CPlayer	*m_pPlayer;
};
#endif
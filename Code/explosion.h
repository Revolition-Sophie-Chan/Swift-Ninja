//=============================================================================
//
// 爆発の処理[explosion.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=============================================================================
//インクルード
//=============================================================================

//=============================================================================
//爆発のクラス
//=============================================================================
class CExplosion : public CScene2D
{
public:
	typedef enum
	{
		EXPLOSIONTYPE_ENEMY = 0,
		EXPLOSIONTYPE_JUMP,
		EXPLOSIONTYPE_MAX,
	} EXPLOSIONTYPE;

	CExplosion(OBJECT_TYPE type);
	~CExplosion();
	void Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion *Create(D3DXVECTOR3 EPpos,int nLife,int nCount,EXPLOSIONTYPE nType);
	EXPLOSIONTYPE GetType();

private:
	void TypeManager(void);

	static LPDIRECT3DTEXTURE9 m_pTextureExplosion[EXPLOSIONTYPE_MAX];//テクスチャへのポインタ

	int m_nLife;
	int nCountExplosionAnim;
	int nPattenExplosionAnim;

	EXPLOSIONTYPE ExplosionType;

};
#endif
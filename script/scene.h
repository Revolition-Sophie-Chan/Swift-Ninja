//=============================================================================
//
// ポリゴン処理[scene.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_
#define DIRECTINPUT_VERSION (0x0800)


#include"main.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TEXTURE (500)
//=============================================================================
//クラス
//=============================================================================
class CScene
{
public:
	typedef enum
	{//状態
		OBJECT_TYPE_NULL = 0,
		OBJECT_TYPE_BG,
		OBJECT_TYPE_ENEMY,
		OBJECT_TYPE_EXPLOSION,
		OBJECT_TYPE_EFFECT,
		OBJECT_TYPE_PLAYER,
		OBJECT_TYPE_POINTER,
		OBJECT_TYPE_UI,
		OBJECT_TYPE_GAUGE,
		OBJECT_TYPE_MAX,
	} OBJECT_TYPE;

	CScene(OBJECT_TYPE type);
	virtual ~CScene();
	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	OBJECT_TYPE GetObjType(void);
	void SetObjType(OBJECT_TYPE);

	CScene *GetScene(int TypeObj, OBJECT_TYPE type);
	void Release(void);


protected:


private:
	OBJECT_TYPE Obj;
	static CScene *m_apScene[OBJECT_TYPE_MAX][MAX_TEXTURE];
	static int m_NumAll;
	static int nCountSlow;

	int m_bId;
	int m_nID;//自分の番号
};
#endif
//=============================================================================
//
// チュートリアルの処理[Tutorial.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#define _CRT_SECURE_NO_WARNINGS

//インクルードファイル
#include "main.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CRender;
class CInputkeyborad;
class CBg;
class CPlayer;
class CEnemy;
class CBullet;
class CExplosion;
class CNumber;
class CPointer;
class CTutorial;
class CTitle;
class CFade;

//=============================================================================
//クラス
//=============================================================================
class CTutorial
{
public:

	typedef enum
	{
		TUTORIALSTATE_NORMAL = 0,	//何もしていない
		TUTORIALSTATE_ADVISE,		//クリア
		TUTORIALSTATE_MAX
	} TUTORIALSTATE;

	CTutorial();
	~CTutorial();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTutorial *Create(void);
	int nCountTime;

private:
	TUTORIALSTATE State;
	bool bAdvise;
	int nCountTutorial;
};

#endif
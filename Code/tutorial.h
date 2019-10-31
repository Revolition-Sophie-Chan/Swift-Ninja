//=============================================================================
//
// チュートリアルの処理[tutorial.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"

//=============================================================================
//前方宣言
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
//チュートリアルクラス
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

private:
	void LoadAll(void);
	TUTORIALSTATE TutorialState;
	bool bAdvise;
};

#endif
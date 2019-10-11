//=============================================================================
//
// �`���[�g���A���̏���[Tutorial.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#define _CRT_SECURE_NO_WARNINGS

//�C���N���[�h�t�@�C��
#include "main.h"

//=============================================================================
// �O���錾
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
//�N���X
//=============================================================================
class CTutorial
{
public:

	typedef enum
	{
		TUTORIALSTATE_NORMAL = 0,	//�������Ă��Ȃ�
		TUTORIALSTATE_ADVISE,		//�N���A
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
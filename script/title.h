//=============================================================================
//
// �^�C�g���̏���[title.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#define _CRT_SECURE_NO_WARNINGS

//�C���N���[�h�t�@�C��
#include "main.h"
#include "manager.h"

class CLoad;

//=============================================================================
//�N���X
//=============================================================================
class CTitle
{
public:
	CTitle();
	~CTitle();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTitle *Create();
private:
	int FadeCount;
	static CLoad *m_Load;


};
#endif
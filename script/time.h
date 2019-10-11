//=============================================================================
//
// �X�R�A���� [time.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "number.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAXTIMENUM	(3)


class CNumber;
//=============================================================================
//�N���X
//=============================================================================
class CTime : public CScene
{
public:

	CTime(OBJECT_TYPE type);
	~CTime();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTime *Create(int nTime);
	static int GetTime(void);
	static CNumber *GetaTime();

	void AddTime(int nValue);
	void SetTime(int nTime);
	static int m_nTime;				// ����

private:

	static CNumber *m_apTime[MAXTIMENUM];
};
#endif

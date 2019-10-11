//=============================================================================
//
// タイトルの処理[title.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#define _CRT_SECURE_NO_WARNINGS

//インクルードファイル
#include "main.h"
#include "manager.h"

class CLoad;

//=============================================================================
//クラス
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
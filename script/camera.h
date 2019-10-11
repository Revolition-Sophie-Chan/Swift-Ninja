
//=============================================================================
//
// �X�N���[���̏���[camera.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//�C���N���[�h
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//�N���X
//=============================================================================
class CCamera
{
public:
	//typedef struct
	//{
	//	D3DXVECTOR3 m_pos;
	//}CAMERA;

	CCamera();
	~CCamera();
	void InitCamera();
	static void ResetCamera();
	static void MoveCamera(D3DXVECTOR3 move);
	static CCamera *GetCamera(void);
	static D3DXVECTOR3 GetCameraPos(void);
	static CCamera *Create(void);


private:
	static D3DXVECTOR3 m_pos;
	static CCamera *m_pCamera;
};
#endif
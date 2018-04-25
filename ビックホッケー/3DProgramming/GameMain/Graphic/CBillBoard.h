#ifndef CBILLBOARD
#define CBILLBOARD

#include "../Vector/CVector3.h"
#include "../Matrix/CMatrix44.h"
#include "CTexture.h"
#include "../Camera/CCamera.h"

class CBillBoard {
public:
	//�l�p�`�̒��_4��
	CVector3 mVertex[4];
	//�ʒu
	CVector3 mPosition;
	//�����s��
	CMatrix44 mMatrix;
	//�J�����̃|�C���^
	CCamera *mpCamera;
	//�e�N�X�`��
	CTexture *mpTexture;	

	void SetVertex(float left, float right, float bottom, float top);
	void Update();
	void Render();

};

#endif

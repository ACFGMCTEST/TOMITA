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
	CVector3 *mpPosition;
	//�����s��
	CMatrix44 mMatrix;
	//�e�N�X�`��
	CTexture *mpTexture;	
	float mUv[4][2];//�e�N�X�`���}�b�s���O
	/*�T�C�Y�ݒ�*/
	void SetVertex(float left, float top, float right, float bottom, CVector3 *pos);
	void SetVertex(float left, float top, float right, float bottom);
	/*�e�N�X�`���ݒ�*/
	void SetUv(CTexture *t, int left, int top, int right, int bottom);
	/*�R���X�g���N�^*/
	CBillBoard();

	void Update();
	void BeforePosUpdate();
	void Render();

};

#endif

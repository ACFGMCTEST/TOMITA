#ifndef CHPBAR_2D_H
#define CHPBAR_2D_H
#include "CRectangle2.h"
#include "../Task/CTask.h"

class CHpBar2D : public CTask{
public:
	CRectangle2 mFrame;//�t���[��
	CRectangle2 mGauge;//�Q�[�W
	CVector2 mPos;
	float mMax; //�ő�g�o
	float mValue; //���݂g�o
	float mWidth, mHeight; //���ƍ���
	/*�R���X�g���N�^*/
	CHpBar2D(){ CTask::eName = CTask::E_2D; }
	/*�ݒ�*/
	void Init(float max, float value, float widht, float height, CVector2 pos);
	void Init(float max, float value, float left, float top, float right, float bottom);
	/*�e�N�X�`���ݒ�*/
	void SetTex(CTexture *frameName, CTexture *gaugeName, STexVer ver);
	void Update();
	void Render();
};

#endif
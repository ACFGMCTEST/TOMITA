#ifndef CHPBAR_H
#define CHPBAR_H
#include "CBillBoard.h"

class CHpBar{
public:
	CBillBoard mFrame;//�t���[��
	CBillBoard mGauge;//�Q�[�W

	float mMax; //�ő�g�o
	float mValue; //���݂g�o
	float mWidth, mHeight; //���ƍ���
	void Init(float max, float value, float widht, float height, CVector3 *pos);
	void Init(float max, float value, float left, float right, float bottom, float top, CVector3 *pos);
	/*�e�N�X�`���ݒ�*/
	void SetTex(CTexture *frameName, CTexture *gaugeName, int left, int top, int right, int bottom);
	void Update();
	void Render();
};

#endif
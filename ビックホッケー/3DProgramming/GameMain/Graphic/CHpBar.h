#ifndef CHPBAR_H
#define CHPBAR_H
#include "CBillBoard.h"

class CHpBar : public CBillBoard{
public:
	float mMax; //�ő�g�o
	float mValue; //���݂g�o
	float mWidth, mHeight; //���ƍ���
	void Init(float max, float value, float widht, float height);
	void Update();
};

#endif
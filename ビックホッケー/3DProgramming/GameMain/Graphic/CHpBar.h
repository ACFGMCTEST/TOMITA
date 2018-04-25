#ifndef CHPBAR_H
#define CHPBAR_H
#include "CBillBoard.h"

class CHpBar : public CBillBoard{
public:
	float mMax; //Å‘å‚g‚o
	float mValue; //Œ»İ‚g‚o
	float mWidth, mHeight; //•‚Æ‚‚³
	void Init(float max, float value, float widht, float height);
	void Update();
};

#endif
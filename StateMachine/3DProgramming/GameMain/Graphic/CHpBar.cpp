#include "CHpBar.h"

/*
����������
*/

void CHpBar::Init(float max, float value, float widht, float height){
	mMax = max;
	mValue = value;
	mHeight = height;
	mWidth = widht;
	widht /= 2;
	height /= 2;
	//���W�̐ݒ���s��
	SetVertex(-widht, widht, -height, height);
}

void CHpBar::Update(){
//Hp�̊������v�Z
	float per = (float)mValue / mMax;
	if (per < 0.0f){
		per = 0.0f;
	}
	//�o�[�̒������v�Z���܂�
	per = mWidth * per;
	//�o�[�̉E�̍��W���v�Z���܂�
	mVertex[2].x = -mWidth / 2 + per;
	mVertex[3].x = -mWidth / 2 + per;
	//�J�����Ɍ�������
	CBillBoard::Update();
}
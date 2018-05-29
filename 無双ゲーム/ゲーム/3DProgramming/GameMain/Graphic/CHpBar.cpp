#include "CHpBar.h"
#include <cmath>
/*
����������
*/

void CHpBar::Init(float max, float value, float widht, float height, CVector3 *pos){
	mMax = max;
	mValue = value;
	mHeight = height;
	mWidth = widht;
	widht /= 2;
	height /= 2;
	//���W�̐ݒ���s��
	mGauge.SetVertex(-widht, widht, -height, height, pos);
	mFrame.SetVertex(-widht, widht, -height, height, pos);
}
void CHpBar::Init(float max, float value, float left, float right, float bottom, float top, CVector3 *pos){
	mMax = max;
	mValue = value;
	mHeight = abs(left) + abs(right);
	mWidth  = abs(top) + abs(bottom);
	//���W�̐ݒ���s��
	mGauge.SetVertex(left, right, bottom, top, pos);
	mFrame.SetVertex(left, right, bottom, top, pos);
}
void CHpBar::SetTex(CTexture *frameName, CTexture *gaugeName, int left, int top, int right, int bottom){
	mGauge.SetUv(gaugeName, left, top, right, bottom);//�Q�[�W�e�N�X�`���ݒ�
	mFrame.SetUv(frameName, left, top, right, bottom);//�t���[���e�N�X�`���ݒ�
}

void CHpBar::Update(){
	//Hp�̊������v�Z
	float per = (float)mValue / mMax;


	//�o�[�̒������v�Z���܂�
	per = mWidth * per;
	//�o�[�̉E�̍��W���v�Z���܂�
	mGauge.mVertex[2].x = -mWidth / 2 + per;
	mGauge.mVertex[3].x = -mWidth / 2 + per;
	if (mValue <= 0){
		mGauge.mVertex[2].x = 0;
		mGauge.mVertex[3].x = 0;
	}
	//�J�����Ɍ�������
	mGauge.Update();
	mFrame.Update();
}

/*�`��*/
void CHpBar::Render(){
	if (mValue > 0){ mGauge.Render(); }
	mFrame.Render();
}
#include "CHpBar2D.h"
#include <cmath>
/*
����������
*/

void CHpBar2D::Init(float max, float value, float widht, float height, CVector2 pos){
	mMax = max;
	mValue = value;
	mHeight = height;
	mWidth = widht;
	widht /= 2;
	height /= 2;
	//���W�̐ݒ���s��
	mGauge.SetVertex(-widht, height, widht, -height);
	mGauge.mPosition = pos;
	mFrame.SetVertex(-widht, height, widht, -height);
	mFrame.mPosition = pos;
}
void CHpBar2D::Init(float max, float value, float left, float top, float right, float bottom){
	mMax = max;
	mValue = value;
	mHeight = abs(top) + abs(bottom);
	mWidth  = abs(left)  + abs(right);
	//���W�̐ݒ���s��
	mGauge.SetVertex(left, top, right, bottom);
	mFrame.SetVertex(left, top, right, bottom);
}
void CHpBar2D::SetTex(CTexture *frameName, CTexture *gaugeName, STexVer ver){
	mGauge.SetUv(gaugeName, ver.left, ver.top, ver.right, ver.bottom);//�Q�[�W�e�N�X�`���ݒ�
	mFrame.SetUv(frameName, ver.left, ver.top, ver.right, ver.bottom);//�t���[���e�N�X�`���ݒ�
}

void CHpBar2D::Update(){
	mGauge.mPosition = mPos;
	mFrame.mPosition = mPos;
	//Hp�̊������v�Z
	float per = (float)mValue / mMax;
	

	//�o�[�̒������v�Z���܂�
	per = -(mWidth / 2)  +  mWidth * per;

	//�o�[�̉E�̍��W���v�Z���܂�
	mGauge.SetVertex(-mWidth/2,mHeight/2, per,-mHeight / 2);
	if (mValue <= 0){
		mGauge.SetVertex(0, mHeight / 2,0, -mHeight / 2);
	}
}

/*�`��*/
void CHpBar2D::Render(){
	CRectangle2::Disp2D_Start();
	if (mValue > 0) { mGauge.Render(); }
	mFrame.Render();

	CRectangle2::Disp2D_Exit();
}
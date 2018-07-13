#include "CHpBar.h"
#include <cmath>
/*
����������
*/

void CHpBar::Init(CCamera *pCamera,float max, float value, float widht, float height, 
	CVector3 *pos,CVector3 *rot,CVector3 ajust){
	mMax = max;
	mValue = value;
	mHeight = height;
	mWidth = widht;
	widht /= 2;
	height /= 2;
	//���W�̐ݒ���s��
	mGauge.SetVertex(pCamera,SVer(-widht, height, widht, -height), pos, rot,ajust);
	mFrame.SetVertex(pCamera, SVer(-widht, height, widht, -height), pos, rot,ajust);
}

void CHpBar::Init(CCamera *pCamera, float max, float value, float widht, float height,
	CVector3 *pos,CVector3 ajust) {
	mMax = max;
	mValue = value;
	mHeight = height;
	mWidth = widht;
	widht /= 2;
	height /= 2;
	//���W�̐ݒ���s��
	mGauge.SetVertex(pCamera, SVer(-widht, height, widht, -height), pos, ajust);
	mFrame.SetVertex(pCamera, SVer(-widht, height, widht, -height), pos, ajust);
}

void CHpBar::SetTex(CTexture *frameName, CTexture *gaugeName, int left, int top, int right, int bottom){
	mGauge.SetUv(gaugeName, left, top, right, bottom);//�Q�[�W�e�N�X�`���ݒ�
	mFrame.SetUv(frameName, left, top, right, bottom);//�t���[���e�N�X�`���ݒ�
}

void CHpBar::Update(){
	//Hp�̊������v�Z
	float per = (float)mValue / mMax;


	////�o�[�̒������v�Z���܂�
	//per = mWidth * per;
	////�o�[�̉E�̍��W���v�Z���܂�
	//mGauge.mVertex[2].x = -mWidth / 2 + per;
	//mGauge.mVertex[3].x = -mWidth / 2 + per;

	//�o�[�̒������v�Z���܂�
	per = -(mWidth / 2) + (mWidth * per);
	//�o�[�̉E�̍��W���v�Z���܂�
	mGauge.mVertex[2].x =  per;
	mGauge.mVertex[3].x =  per;

	if (mValue <= 0) {
		mGauge.mVertex[2].x = 0;
		mGauge.mVertex[3].x = 0;
	}
	//�J�����Ɍ�������
	mGauge.Update();
	mFrame.BeforePosUpdate();
}

/*�`��*/
void CHpBar::Render(){

	if (mValue > 0){ mGauge.Render(); }
	mFrame.Render();

}
#include "CExplosion.h"


/*�R���X�g���N�^*/
CExplosion::CExplosion() : mEnabled(false), mCount(0){
	mForward = VEC_BACK;
}
/*����������*/
void CExplosion::Init(CVector3 pos, CVector3 rot){
	mPos = CVector4(pos.x, pos.y, pos.z);
	mRot = rot;
	for (int i = 0; i < EXP_ARRAY; i++){
		mSpark[i].Init(mPos);
	}
	mCount = 0;
	mEnabled = true;
}
/*�X�V����*/
void CExplosion::Update(){

	CBase::UpdateMatrix();
	if (mEnabled){
		/*���Ԃ����܂�*/
		if (mCount++ < LIFE_TIME){
			for (int i = 0; i < EXP_ARRAY; i++){
				mSpark[i].Update();
			}
		}
		/*���Ԃ�����*/
		else{
			/*����,�f�o�b�N�p�ɏ��������ă��[�v����悤�ɂ��Ă���*/
			Init(mPos,mRot);
			mEnabled = false;
		}
	}
}
/*�`��*/
void CExplosion::Render(){

	if (mEnabled){
		glPushMatrix();
		CBase::UpdateMatrix();
		glMultMatrixf(mMatrix.f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (int i = 0; i < EXP_ARRAY; i++){
			mSpark[i].Render();
		}
		glDisable(GL_BLEND);
		glPopMatrix();
	}
}
/*�A�j���[�V�������I����*/
void CExplosion::EnabledAnima(){
	/*����̎��̂�*/
	if (mEnabled){
		Init(mPos, mRot);
	}
	mEnabled = true;

}
/*�A�j���[�V�������I�t��*/
void CExplosion::DisableAnima(){
	mEnabled = false;
}
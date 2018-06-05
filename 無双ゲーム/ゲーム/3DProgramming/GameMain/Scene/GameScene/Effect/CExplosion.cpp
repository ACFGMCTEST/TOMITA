#include "CExplosion.h"


/*�R���X�g���N�^*/
CExplosion::CExplosion() : mEnabled(false), mCount(0){
	CTask::eName = CTask::E_BILLBOARD;
}
/*����������*/
void CExplosion::Init(CTexture *tex, float x, float y, STexVer texVer){
	for (int i = 0; i < EXP_ARRAY; i++){
		mSpark[i].Init(tex, x, y, texVer);
	}
	mCount = 0;
	mEnabled = true;
}
/*�����������@�ݒ肳��Ă���ꍇ*/
void CExplosion::Init() {	
	for (int i = 0; i < EXP_ARRAY; i++) {
		mSpark[i].Init();
	}
	mCount = 0;
	mEnabled = true;
}

/*�X�V����*/
void CExplosion::Update(){
	if (mEnabled){
		/*���Ԃ����܂�*/
		if (mCount++ < LIFE_TIME){
			for (int i = 0; i < EXP_ARRAY; i++){
				mSpark[i].Update();
				/*���o �F��a�l,�Z�o*/
				float a = 1.0f - (mCount / LIFE_TIME);
				mSpark[i].SetDiffuse(1.0f, 1.0f, 1.0f, a);
			}
		}
		/*���Ԃ�����*/
		else{
			Init();
			mEnabled = false;
		}
	}
}
/*�������I���������f*/
bool CExplosion::ExpEnd() {
	return (mCount >= LIFE_TIME && mEnabled);
}
/*�`��*/
void CExplosion::Render() {

	for (int i = 0; i < EXP_ARRAY; i++) {
		mSpark[i].Render();
	}
}
/*�A�j���[�V�����Z�b�g*/
void CExplosion::SetAnima(int size, float width) {
	for (int i = 0; i < EXP_ARRAY; i++) {
		mSpark[i].SetAnima(size, width);
	}
}

/*�A�j���[�V�������I����*/
void CExplosion::StartAnima(float speed,CVector3 pos){
	/*���̂�*/
	if (!mEnabled) {
		for (int i = 0; i < EXP_ARRAY; i++) {

			mSpark[i].StartAnima(speed, pos);
		}
		mEnabled = true;
	}

}
/*�A�j���[�V�������I�t��*/
void CExplosion::DisableAnima(){
	for (int i = 0; i < EXP_ARRAY; i++) {
		mSpark[i].DisableAnima();
	}
	mEnabled = false;
}
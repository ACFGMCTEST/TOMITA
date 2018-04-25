#include "CExplosion.h"


/*コンストラクタ*/
CExplosion::CExplosion() : mEnabled(false), mCount(0){
	mForward = VEC_BACK;
}
/*初期化処理*/
void CExplosion::Init(CVector3 pos, CVector3 rot){
	mPos = CVector4(pos.x, pos.y, pos.z);
	mRot = rot;
	for (int i = 0; i < EXP_ARRAY; i++){
		mSpark[i].Init(mPos);
	}
	mCount = 0;
	mEnabled = true;
}
/*更新処理*/
void CExplosion::Update(){

	CBase::UpdateMatrix();
	if (mEnabled){
		/*時間がたつまで*/
		if (mCount++ < LIFE_TIME){
			for (int i = 0; i < EXP_ARRAY; i++){
				mSpark[i].Update();
			}
		}
		/*時間がたつと*/
		else{
			/*現在,デバック用に初期化してループするようにしている*/
			Init(mPos,mRot);
			mEnabled = false;
		}
	}
}
/*描画*/
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
/*アニメーションをオンに*/
void CExplosion::EnabledAnima(){
	/*初回の時のみ*/
	if (mEnabled){
		Init(mPos, mRot);
	}
	mEnabled = true;

}
/*アニメーションをオフに*/
void CExplosion::DisableAnima(){
	mEnabled = false;
}
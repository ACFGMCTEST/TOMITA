#include "CExplosion.h"


/*コンストラクタ*/
CExplosion::CExplosion() : mEnabled(false), mCount(0){
	CTask::eName = CTask::E_BILLBOARD;
}
/*初期化処理*/
void CExplosion::Init(CTexture *tex, float x, float y, STexVer texVer){
	for (int i = 0; i < EXP_ARRAY; i++){
		mSpark[i].Init(tex, x, y, texVer);
	}
	mCount = 0;
	mEnabled = true;
}
/*初期化処理　設定されている場合*/
void CExplosion::Init() {	
	for (int i = 0; i < EXP_ARRAY; i++) {
		mSpark[i].Init();
	}
	mCount = 0;
	mEnabled = true;
}

/*更新処理*/
void CExplosion::Update(){
	if (mEnabled){
		/*時間がたつまで*/
		if (mCount++ < LIFE_TIME){
			for (int i = 0; i < EXP_ARRAY; i++){
				mSpark[i].Update();
				/*演出 色のa値,算出*/
				float a = 1.0f - (mCount / LIFE_TIME);
				mSpark[i].SetDiffuse(1.0f, 1.0f, 1.0f, a);
			}
		}
		/*時間がたつと*/
		else{
			Init();
			mEnabled = false;
		}
	}
}
/*爆発が終了した判断*/
bool CExplosion::ExpEnd() {
	return (mCount >= LIFE_TIME && mEnabled);
}
/*描画*/
void CExplosion::Render() {

	for (int i = 0; i < EXP_ARRAY; i++) {
		mSpark[i].Render();
	}
}
/*アニメーションセット*/
void CExplosion::SetAnima(int size, float width) {
	for (int i = 0; i < EXP_ARRAY; i++) {
		mSpark[i].SetAnima(size, width);
	}
}

/*アニメーションをオンに*/
void CExplosion::StartAnima(float speed,CVector3 pos){
	/*一回のみ*/
	if (!mEnabled) {
		for (int i = 0; i < EXP_ARRAY; i++) {

			mSpark[i].StartAnima(speed, pos);
		}
		mEnabled = true;
	}

}
/*アニメーションをオフに*/
void CExplosion::DisableAnima(){
	for (int i = 0; i < EXP_ARRAY; i++) {
		mSpark[i].DisableAnima();
	}
	mEnabled = false;
}
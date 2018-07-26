#include "CPlayerDied.h"
#include "../CPlayer.h"
#include "../../../Result/CResult.h"
/*アニメのスピード*/
#define ANIMA_SPEED 60 

//変更する関数
void CPlayerDied::ChangeState(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*アニメーションが終わるとリザルト画面を表示*/
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime) {
		CResult::GetInstance()->Over();//ゲームオーバーフラグを立てる
	}

	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}


/*初めに呼び出し*/
void CPlayerDied::Start(){
	
}



/*更新処理*/
void CPlayerDied::Update(){

	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	pl->ChangeAnimation(F_PL_DIED, false, ANIMA_SPEED);

	
}


CPlayerDied::CPlayerDied()
{

}

CPlayerDied::~CPlayerDied()
{
}
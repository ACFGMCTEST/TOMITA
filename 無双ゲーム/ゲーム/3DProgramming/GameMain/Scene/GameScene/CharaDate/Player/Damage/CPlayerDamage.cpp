#include "CPlayerDamage.h"
#include "../CPlayer.h"

/*アニメのスピード*/
#define ANIMA_SPEED 30 

//変更する関数
void CPlayerDamage::ChangeState(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*アイドリングする*/
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime) {
		mNextRegisterName = F_PL_IDLING;
	}
	/*hpがなくなると*/
	if (pl->HP() <= 0) {
		mNextRegisterName = F_PL_DIED;
	}

	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}


/*初めに呼び出し*/
void CPlayerDamage::Start(){
	
}



/*更新処理*/
void CPlayerDamage::Update(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	pl->ChangeAnimation(F_PL_DAMAGE, false, ANIMA_SPEED);

	/*モーション中でないときはノックバック*/
	if (pl->mAnimationTime <=
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime) {
		pl->BlowOff();
	}
}


CPlayerDamage::CPlayerDamage()
{

}

CPlayerDamage::~CPlayerDamage()
{
}
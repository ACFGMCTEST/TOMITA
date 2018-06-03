#include "CSlimeDamage.h"
#include "../CSlime.h"

const float AnimaSpeed = 10;//アニメーションのスピード

//変更する関数
void CSlimeDamage::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*アニメーションが終わると*/
	if (sli->mAnimationTime > 
		sli->mpModel->mAnimationSet[sli->mAnimationIndex]->mMaxTime) {
		mNextRegisterName = SLI_STATE_IDLING;//アイドリングに戻る
		sli->mFlagDamage = false;
	}
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}


/*初めに呼び出し*/
void CSlimeDamage::Start(){
	
}



/*更新処理*/
void CSlimeDamage::Update(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*アイドリングの処理*/
	sli->ChangeAnimation(CSlime::E_DAMAGE, false, AnimaSpeed);
	sli->BlowOff();//吹っ飛ぶ

}

CSlimeDamage::CSlimeDamage()
{

}

CSlimeDamage::~CSlimeDamage()
{
}
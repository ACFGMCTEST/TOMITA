#include "CStateSlimeDamage.h"
#include "../../CSlime.h"


//変更する関数
void CStateSlimeDamage::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*アニメーションが終わると*/
	if (sli->mAnimationTime >
		sli->mpModel->mAnimationSet[sli->mAnimationIndex]->mMaxTime) {
		mNextRegisterName = SLI_STATE_IDLING;//アイドリングに戻る
	}
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}


/*初めに呼び出し*/
void CStateSlimeDamage::Start(){
	
}



/*更新処理*/
void CStateSlimeDamage::Update(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*アイドリングの処理*/
	sli->ChangeAnimation(CTask::E_DAMAGE, true, ANIMA_SPEED);
	sli->BlowOff();//吹っ飛ぶ
}

CStateSlimeDamage::CStateSlimeDamage()
{

}

CStateSlimeDamage::~CStateSlimeDamage()
{
}
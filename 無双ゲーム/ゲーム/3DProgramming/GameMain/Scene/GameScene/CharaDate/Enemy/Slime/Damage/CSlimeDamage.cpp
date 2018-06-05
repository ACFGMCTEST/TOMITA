#include "CSlimeDamage.h"
#include "../CSlime.h"
#include "../../../../../../Convenient/CConvenient.h"

const float AnimaSpeed = 100;//アニメーションのスピード
const float BlowOffTime = 0.1f;//吹き飛ぶ時間
//変更する関数
void CSlimeDamage::ChangeState() {
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*時間がたつとHPが0になると*/
	if (CConvenient::Time(&mCount, BlowOffTime) && sli->HP() > 0) {
		mNextRegisterName = SLI_STATE_IDLING;//アイドリングに戻る
		sli->mFlagDamage = false;
	}
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}


/*初めに呼び出し*/
void CSlimeDamage::Start() {
	mCount = 0;
}



/*更新処理*/
void CSlimeDamage::Update() {
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	if (sli->HP() <= 0) {
		sli->ChangeAnimation(CSlime::E_DAMAGE, false, AnimaSpeed);//アニメーション
		/* ダメージモーションを取り消す*/
		if (sli->mAnimationTime >
			sli->mpModel->mAnimationSet[sli->mAnimationIndex]->mMaxTime) {
			sli->Delete();
		}
	}
	else {
		sli->BlowOff();
	}



}

CSlimeDamage::CSlimeDamage()
{

}

CSlimeDamage::~CSlimeDamage()
{
}
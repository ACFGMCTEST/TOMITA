#include "CSlimeIdling.h"
#include "../CSlime.h"


//変更する関数
void CSlimeIdling::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);

	/*動くフラグがたてば*/
	if ( sli->Search()){
		mNextRegisterName = SLI_STATE_RUN;//走る
	}

	/*ダメージを受けているなら*/
	if (sli->mFlagDamage) {
		mNextRegisterName = SLI_STATE_DAMAGE;//ダメージ
	}
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}


/*初めに呼び出し*/
void CSlimeIdling::Start(){
	
}



/*更新処理*/
void CSlimeIdling::Update(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*アイドリングの処理*/
	sli->ChangeAnimation(CSlime::E_IDLING, true, ANIMA_SPEED);

}

CSlimeIdling::CSlimeIdling()
{

}

CSlimeIdling::~CSlimeIdling()
{
}
#include "CStatePlayerDamage.h"
#include "../../CXCharPlayer.h"


//変更する関数
void CStatePlayerDamage::ChangeState(){
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}


/*初めに呼び出し*/
void CStatePlayerDamage::Start(){
	
}



/*更新処理*/
void CStatePlayerDamage::Update(){
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*アイドリングの処理*/
	pl->ChangeAnimation(CTask::E_DAMAGE, true, ANIMA_SPEED);

}

CStatePlayerDamage::CStatePlayerDamage()
{

}

CStatePlayerDamage::~CStatePlayerDamage()
{
}
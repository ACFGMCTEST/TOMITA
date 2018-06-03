#include "CPlayerDamage.h"
#include "../CPlayer.h"


//変更する関数
void CPlayerDamage::ChangeState(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}


/*初めに呼び出し*/
void CPlayerDamage::Start(){
	
}



/*更新処理*/
void CPlayerDamage::Update(){
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	/*アイドリングの処理*/
	pl->ChangeAnimation(CTask::E_DAMAGE, true, ANIMA_SPEED);

}

CPlayerDamage::CPlayerDamage()
{

}

CPlayerDamage::~CPlayerDamage()
{
}
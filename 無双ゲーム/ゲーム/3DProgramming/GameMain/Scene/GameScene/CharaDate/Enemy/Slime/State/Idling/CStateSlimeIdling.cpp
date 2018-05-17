#include "CStateSlimeIdling.h"
#include "../../CSlime.h"


//変更する関数
void CStateSlimeIdling::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*動くフラグがたてば*/
	if (sli->Search()){
		mNextRegisterName = SLI_STATE_RUN;//走る
	}
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}


/*初めに呼び出し*/
void CStateSlimeIdling::Start(){
	
}



/*更新処理*/
void CStateSlimeIdling::Update(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*アイドリングの処理*/
	sli->ChangeAnimation(CTask::E_IDLING, true, ANIMA_SPEED);

}

CStateSlimeIdling::CStateSlimeIdling()
{

}

CStateSlimeIdling::~CStateSlimeIdling()
{
}
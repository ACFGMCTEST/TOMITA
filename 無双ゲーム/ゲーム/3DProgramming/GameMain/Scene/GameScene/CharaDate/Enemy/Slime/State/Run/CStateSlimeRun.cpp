#include "CStateSlimeRun.h"
#include "../../CSlime.h"

//変更する関数
void CStateSlimeRun::ChangeState(){
}
/*初めに呼び出し*/
void CStateSlimeRun::Start()
{

}

/*更新処理*/
void CStateSlimeRun::Update(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*アイドリングの処理*/
	sli->ChangeAnimation(CTask::E_RUN, true, ANIMA_SPEED_RUN);

	/*動く*/
	SPEED_RUN_ACC(sli->mVelocity);//移動速度計算
	sli->Move();

}

CStateSlimeRun::CStateSlimeRun()
{
}

CStateSlimeRun::~CStateSlimeRun()
{
}
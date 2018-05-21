#include "CStateSlimeRun.h"
#include "../../CSlime.h"
/*進むスピード*/
#define SPEED_RUN 0.01f //MAX走る
#define SPEED_RUN_ACC(v) if (SPEED_RUN > v){v += SPEED_RUN* 0.1f; }else{v = SPEED_RUN;}//加速度計算上限に来た場合

//変更する関数
void CStateSlimeRun::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*フラグがたっていなければ*/
	if (!sli->Search()){
		mNextRegisterName = SLI_STATE_IDLING;//走る
	}
	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
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
	sli->AIMove();
}

CStateSlimeRun::CStateSlimeRun()
{
}

CStateSlimeRun::~CStateSlimeRun()
{
}
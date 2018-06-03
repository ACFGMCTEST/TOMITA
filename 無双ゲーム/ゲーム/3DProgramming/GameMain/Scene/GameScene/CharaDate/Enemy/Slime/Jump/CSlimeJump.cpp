#include "CSlimeJump.h"
#include "../CSlime.h"

/*ジャンプのスピード*/
#define JUMP_SPEED 0.3f//ジャンプするスピード

//変更する関数
void CSlimeJump::ChangeState(){
}
/*初めに呼び出し*/
void CSlimeJump::Start()
{
}
/*更新処理*/
void CSlimeJump::Update()
{
	CSlime *sl = dynamic_cast<CSlime*>(mpParent);
	/*アニメーション*/
	sl->ChangeAnimation(CTask::E_JUMP, true, ANIMA_SPEED_JUMP);

	/*ジャンプ*/
	sl->Move();//移動関数.横(x,z)の移動

	mPrevPosY = sl->mPosition.y;//現在のポジション記憶
	float jumpVilocity = JUMP_SPEED - GRAVITY(sl->mGravitTime);//動かす力
	/*ジャンプが0より大きい場合*/
	sl->mPosition.y += jumpVilocity;

	/*落下中でない場合*/
	if (!mFlagFall){
		sl->mFlagJump = true;//地面から飛ぶときの判定調整用
		/*落下中の場合*/
		float graSpeed = GRAVITY(sl->mGravitTime);
		if (JUMP_SPEED <= graSpeed*2){
			mFlagFall = true;
		}
	}
	


}
//遷移時の処理
// isNextをfalseに戻す処理はここで行うとよい
void CSlimeJump::OnChangeEvent()
{

}

CSlimeJump::CSlimeJump()
{
}

CSlimeJump::~CSlimeJump()
{
}
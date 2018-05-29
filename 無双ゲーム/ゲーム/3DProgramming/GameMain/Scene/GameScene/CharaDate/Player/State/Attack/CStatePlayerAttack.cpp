#include "CStatePlayerAttack.h"
#include "../../CXCharPlayer.h"
/*スピードのフレーム数でvelocityを変更する*/
/*フレーム*/
#define FRAME_VEL_ATTACK1 0
#define FRAME_VEL_ATTACK2 30
#define FRAME_VEL_ATTACK3 40
/*スピード*/
#define BASE_SPEED 0.2f
#define VEL_ATTACK1 BASE_SPEED * 0.5f
#define VEL_ATTACK2 0
#define VEL_ATTACK3 BASE_SPEED * 0.7f

//変更する関数
void CStatePlayerAttack::ChangeState(){
	/*ジャンプする場合*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = PL_STATE_JUMP;//ジャンプ
	}
	/*アイドリングする*/
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime){
		mNextRegisterName = PL_STATE_IDLING;
	}

	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) mFlagNext = true;//文字が入れば
}

/*初めに呼び出し*/
void CStatePlayerAttack::Start(){
	mAnimaSpeed = 0;//初期化
}

/*攻撃の移動速さ調整*/
void CStatePlayerAttack::AttackSpeed(){
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*攻撃の速さをいじる*/
	if (FRAME_VEL_ATTACK1 <= pl->mAnimationTime && pl->mAnimationTime <= FRAME_VEL_ATTACK2){ //少し動く
		pl->mVelocity = VEL_ATTACK1;
		printf("アタック1です\n");
	}
	else if (FRAME_VEL_ATTACK2 <= pl->mAnimationTime && pl->mAnimationTime <= FRAME_VEL_ATTACK3){//ちょっと止まる
		pl->mVelocity = VEL_ATTACK2;
		printf("アタック2です\n");
	}
	else{//一番動く
		pl->mVelocity = VEL_ATTACK3;
		printf("アタック3です\n");
	}

	printf("現在フレーム%f\n", pl->mAnimationTime);
	pl->Move();
}
/*更新処理*/
void CStatePlayerAttack::Update()
{
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(mpParent);
	/*アニメーション*/
	pl->ChangeAnimation(CTask::E_ATTACK, false, ANIMA_SPEED_ATTCK);
	/*攻撃*/
	AttackSpeed();//攻撃で少し前に移動させる
	pl->State(PL_STATE_ATTACK);//ステータスを入れる
}
//遷移時の処理
// isNextをfalseに戻す処理はここで行うとよい
void CStatePlayerAttack::OnChangeEvent()
{

}

CStatePlayerAttack::CStatePlayerAttack()
{
}

CStatePlayerAttack::~CStatePlayerAttack()
{
}
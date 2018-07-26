#include "CSlimeIdling.h"
#include "../CSlime.h"

/*アニメのスピード*/
#define ANIMA_SPEED 60 * 4

//変更する関数
void CSlimeIdling::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);

	/*動くフラグがたてば*/
	if ( sli->Search()){
		mNextRegisterName = F_SLI_RUN;//走る
	}

	/*ダメージを受けているなら*/
	if (sli->mFlagDamage || sli->HP() == 0) {
		mNextRegisterName = F_SLI_DAMAGE;//ダメージ
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
	sli->ChangeAnimation(F_SLI_IDLING,F_SLI_KING_IDLING, true, ANIMA_SPEED);
}

CSlimeIdling::CSlimeIdling()
{

}

CSlimeIdling::~CSlimeIdling()
{
}
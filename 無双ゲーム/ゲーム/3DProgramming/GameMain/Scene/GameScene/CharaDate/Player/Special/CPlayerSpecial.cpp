#include "../CPlayer.h"
#include "CPlayerSpecial.h"
#include "../../../../../Graphic/CLoadTexManager.h"
#include "../../CSceneModel.h"
/*スピードのフレーム数でvelocityを変更する*/
/*フレーム*/
#define FRAME_VEL_ATTACK1 0
#define FRAME_VEL_ATTACK2 30
#define FRAME_VEL_ATTACK3 40
/*スピード*/
#define VEL_ATTACK1 0.05f
#define VEL_ATTACK2 0
#define VEL_ATTACK3 0.07f
/*アニメのスピード*/
#define ANIMA_SPEED 50

//コンストラクタ
CPlayerSpecial::CPlayerSpecial():mpEffect3D(nullptr){}
//デストラクタ
CPlayerSpecial::~CPlayerSpecial() {}
//変更する関数
void CPlayerSpecial::ChangeState(){
	/*ジャンプする場合*/
	if (CKey::once(KEY_JUMP)){
		mNextRegisterName = F_PL_JUMP;//ジャンプ
	}
	/*アイドリングする*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime){
		mNextRegisterName = F_PL_IDLING;
	}

	//名前が入ればフラグを立てる
	if (!mNextRegisterName.empty()) {
		mFlagNext = true;//文字が入れば
		mpEffect->CTask::mKillFlag = true;
	}
}

/*エフェクトの設定*/
#define EFF_SIZE 3.0f,3.0f//サイズ
#define EFF_POS(pos) CVector3(pos.x,pos.y + 2.0f, pos.z)//エフェクトのポジション
#define TEX_EFF_SIZE 0.0f,0.0f,960,192//テクスチャのサイズ
#define EFF_SET_ANIMA 5,192//設定のアニメーション
#define EFF_SPEED  0.02f//再生スピード
/*初めに呼び出し*/
void CPlayerSpecial::Start() {
	/*エフェクトの設定*/
	mpEffect = new CEffect2D();
	mpEffect->Init(CLoadTexManager::GetInstance()->mpSaveUp,
		EFF_SIZE, STexVer(TEX_EFF_SIZE));//画像や頂点数代入
	mpEffect->SetAnima(EFF_SET_ANIMA);//アニメーションの準備
	CTaskManager::GetInstance()->Add(mpEffect);
	
}

/*更新処理*/
void CPlayerSpecial::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);

	/*アニメーション*/
	pl->ChangeAnimation(F_PL_SPECIAL, false, ANIMA_SPEED);

	/*エフェクト設定*/
	CVector3 pos = CVector3();
	mpEffect->StartAnima(EFF_SPEED,
		pos.Transeform(pl->mpCombinedMatrix
			[pl->mpModel->FindFrame("metarig_forearm_L")->mIndex]));
	/*エフェクト作成されておらず　パンチが放たれた場合*/
#define PUNCH_FRAME_SIZE 70//PUNCHのアニメーションのフレーム
	if (!mpEffect3D && pl->mAnimationTime >= PUNCH_FRAME_SIZE) {
		pl->mPower = ATTACK_POWER*2.5f;
		pl->MpUp(-GAUGE_VER);//消す
		/*３Dのエフェクト作成*/
		CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
		CEffect3D *mpEffect3D = new CEffect3D();
		mpEffect3D->Init(pl, &CSceneModel::GetInstance()->mModEffect3D
			, &pl->mPosition, &pl->mRotation);
		CTaskManager::GetInstance()->Add(mpEffect3D);
	}

}

//遷移時の処理
// isNextをfalseに戻す処理はここで行うとよい
void CPlayerSpecial::OnChangeEvent()
{

}
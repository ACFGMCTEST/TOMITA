#include "CEnemyBase.h"
#include "../CSceneModel.h"
/*当たり判定*/
#include "../../../../Collision/ColType/CColCapsule.h"
#include "../../../../Collision/ColType/CColTriangle.h"
#include "../../../../Collision/CCollision.h"

#include <time.h>
/*回転感覚時間*/
#define ROT_PYCK_TIME 1.0f
/*当たり判定*/
/*準備*/
#define OBB_ATTACK_INIT_BOX_SIZE CVector3(20.0f, 4.0f, 20.0f)
#define OBB_ATTACK_INIT_BOX_POS CVector3(-0.01f, -0.06f, -0.1f)

/*攻撃*/
#define OBB_ATTACK_BOX_SIZE CVector3(3.0f, 3.0f, 3.0f)
#define OBB_ATTACK_BOX_POS CVector3(-0.01f, -0.01f, -0.1f)
/*ゴールの方向に向ける*/
#define GOAL_POS_X (rand() % (int)MAPCHIP_SIZE*CMap::GoalCount()) - MAPCHIP_SIZE*CMap::GoalCount()*0.5f

/*コンストラクタ*/
CEnemyBase::CEnemyBase(){
	CXCharPlayer::CXCharPlayer();
	mGravitTime = GRA_INIT_TIME_COUNT;
	mVelocity = 0.0f;
	mFlagKnockback = false;
	mForward = CVector3(FORWARD);
	/*親設定*/
	mpParent = this;
}

/*初期化処理*/
void CEnemyBase::Init(CModelX *model){
	
}


/*動かす関数*/
void CEnemyBase::AIMove(){
	mRotation = mForward.getRotationTowards(CSceneModel::mpPlayer->mPosition + mPosition * -1.0f);
	mForward = CVector3(FORWARD);
	CXCharPlayer::Move();
}

/*更新処理*/
void CEnemyBase::Update(){
	mAdjust = CVector3();
	mPrevPos = mPosition;
	Gravity();/*重力*/
	PosUpdate();//ポジションを更新
}

/*攻撃準備*/
void CEnemyBase::AttackInit(){
}


/*カプセル内当たり判定*/
void CEnemyBase::CapsuleCol(CColCapsule *cc, CColBase* y){
	CColTriangle ct(false);//三角形の当たり判定
	CColCapsule  caps(false);//球の当たり判定

	/*相手のタイプ何か判断*/
	switch (y->mType){
		/*相手が三角の場合*/
	case CColBase::COL_TRIANGLE:
		ct = (*(CColTriangle*)y).GetUpdate();
		/*当たり判定計算*/
		if (CCollision::IntersectTriangleCapsule3(ct.mV[0], ct.mV[1], ct.mV[2],
			cc->mV[0], cc->mV[1], cc->mRadius, &cc->mAdjust)) {
			ColGround();//地面にあった時の処理
			SetAdjust(&mAdjust, cc->mAdjust);
			mPosition = mPosition + mAdjust;
			CMatrix44 rot_y, pos, matrix;
			//回転行列の作成
			rot_y.rotationY(mRotation.y);
			//移動行列を計算する
			pos.translate(mPosition);
			//回転移動行列を求める
			matrix = pos * rot_y;
			//UpdateSkinMatrix(matrix);
			CModelXS::Update(matrix);
		}
		break;
	};
}

//m 自分　y 相手
bool CEnemyBase::Collision(CColBase* m, CColBase* y) {
	CColCapsule cc(false);
	/*自分のタイプが何か判断*/
	switch (m->mType) {

	case CColBase::COL_CAPSULE://自分の当たり判定がカプセルの場合
		cc = *(CColCapsule*)m;//カプセルにする
		CapsuleCol(&cc, y);//カプセルの当たり判定
		break;
	};

	return false;
}

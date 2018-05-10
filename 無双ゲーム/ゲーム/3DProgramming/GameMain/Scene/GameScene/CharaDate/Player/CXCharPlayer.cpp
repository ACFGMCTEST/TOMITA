#include "CXCharPlayer.h"
#include "windows.h"
#include "../../../../Key/CKey.h"
#include "../CSceneModel.h"
#include "../../../../../Define/Define.h"
#include "../../Map/CMap.h"
#include "../../../../Key/CMouse.h"
#include "../../../../Convenient/CConvenient.h"
#include "../../../GameScene/Map/CMap.h"
#include "../../../ItemScene/CItem.h"
#include <math.h>
#include "../../../../Collision/CCollisionManager.h"
#include "../../../../Collision/CCollision.h"
/*ステータス*/
#include "State\Attack\CStatePlayerAttack.h"
#include "State\Idling\CStatePlayeridling.h"
#include "State\Jump\CStatePlayerJump.h"
#include "State\Run\CStatePlayerRun.h"
#include "../../../../../StateMachine/CStateMachine.h"


/*向き*/
#define FORWARD_JUMP  0.0f,1.0f,1.0f//ジャンプ

/*あたり判定の設定値*/
/*胴*/
#define OBB_SPHERE_BODY_SIZE 0.4f
#define OBB_SPHERE_BODY_POS CVector3(0.0f,0.0f,0.0f)
/*武器*/
#define OBB_WEAPON_POS CVector3(0.0f,0.5f,0.0f)
#define OBB_WEAPON_SIZE CVector3(0.4f, 0.7f, 0.4f)
/*足*/
#define OBB_LEG_SIZE 0.3f
#define OBB_LEG_POS CVector3(0.0f,-1.0f,0.0f)

/*HPバーの設定値*/
#define HP_BAR_POS CVector3(mPosition.x,mPosition.y + 1.8f,mPosition.z)
#define HP_BAR_SIZE -0.4f, 0.4f, -0.1f, 0.0f

/*動きの回転する速さ*/
#define TURN_SPEED 10

CXCharPlayer::CXCharPlayer() : mVelocity(0.0f), mFlagKnockback(false), mRotCount(0),
mGravitTime(GRA_INIT_TIME_COUNT), mFlagJump(false), mAdjust(),
mStateMachine(std::make_unique<CStateMachine>())
{
	// 第一引数にステートの「登録名」
	// 第二引数でStateBaseを継承したクラスのshared_ptrオブジェクトを生成
	mStateMachine->Register(PL_STATE_ATTACK, std::make_shared<CStatePlayerAttack>(),this);
	mStateMachine->Register(PL_STATE_IDLING, std::make_shared<CStatePlayerIdling>(),this);
	mStateMachine->Register(PL_STATE_RUN,    std::make_shared<CStatePlayerRun>(),this);
	mStateMachine->Register(PL_STATE_JUMP,   std::make_shared<CStatePlayerJump>(),this);
	// 最初のステートを登録名で指定
	mStateMachine->SetStartState(PL_STATE_IDLING);

	mForward = CVector3(FORWARD);
	mpParent = this;

	mState = E_IDLING;
	ePriority = CTask::E_PLAYER;

};

/*当たり判定初期化*/
void CXCharPlayer::ColInit(){
	/*当たり判定のインスタンス化*/
	//mpCBWeapon = new CCollider(CTask::E_COL_BOX);

	/*ペアレント設定*/
	//mpCBWeapon->mpParent = this;
}
#define COL_POS CVector3(0.0f, 1.5f, 0.0f), CVector3(0.0f, -0.9f, 0.0f)
/*
Init
モデルと衝突判定の設定を行う
*/
void CXCharPlayer::Init(CModelX *model) {
	ColInit();
	//モデルの設定
	CModelXS::Init(model);
	//カプセル　キャラクタ全体
	new CCollider3Capsule(this, COL_POS, 0.5f
		, &mpCombinedMatrix[model->FindFrame("metarig_hips")->mIndex]);

	mPower = ATTACK_POWER;//攻撃力

	PosUpdate();
	mPrevPos = mPosition;
}




/*ポジションのアップデート関数*/
void CXCharPlayer::PosUpdate(){
	CMatrix44 rot_y, pos, matrix;
	//回転行列の作成
	rot_y.rotationY(mRotation.y);

	//移動行列を計算する
	pos.translate(mPosition);
	//回転移動行列を求める
	matrix = pos * rot_y;

	//頂点データの更新
	CModelXS::Update(matrix);
	mPrevPos = mPosition;
}

/*回転関数*/
void CXCharPlayer::PlusRot(float rot){

	mRotation.y += rot;//タス処理
	if (mRotation.y < 0){//回転値がマイナスなら
		mRotation.y = ANGLE_360 + mRotation.y;//３６０以内にとどめる
	}
	if (mRotation.y > ANGLE_360){//３６０以上の場合
		mRotation.y = mRotation.y + ANGLE_360;
	}
}
/*キャラクター回転差が小さい方向に回転する*/
int CXCharPlayer::MoveRotation(int angle){

	/*右回り*/
	int turnRight = angle - mRotation.y;
	/*過剰余剰*/
	LIMIT_ANGLE(turnRight);
	/*左回り*/
	int turnLeft = ANGLE_360 - turnRight;

	//printf("右回転:%d,左回転%d\n", turnRight, turnLeft);
	/*同じの場合 ||
	右に越えてしまう場合 ||
	左に越えてしまう場合 ||
	*/
	if (mRotation.y == angle ||
		mRotation.y <= angle && angle <= mRotation.y + TURN_SPEED ||
		mRotation.y - TURN_SPEED <= angle && angle <= mRotation.y){
		return angle;
	}
	/*右方向確認*/
	if (turnRight < turnLeft){
		return mRotation.y + TURN_SPEED;
	}
	/*方向確認*/
	else{
		return mRotation.y - TURN_SPEED;
	}


}


/*動くときの関数*/
void CXCharPlayer::PlayerMoveRot(){

	LIMIT_ANGLE(mRotation.y);

	if (CKey::push('A')){//左に移動
		mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_90) % 360);
	}
	if (CKey::push('D')){//右に移動
		mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_270) % 360);
	}

	if (CKey::push('W')){//前に移動

		mRotation.y = MoveRotation(((int)MainCamera.Rot().y) % 360);
		if (CKey::push('A')){//左に移動
			mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_45) % 360);
		}
		if (CKey::push('D')){//右に移動
			mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_315) % 360);
		}
	}

	if (CKey::push('S')){
		mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_180) % 360);
		if (CKey::push('A')){//左に移動
			mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_125) % 360);
		}
		if (CKey::push('D')){//右に移動
			mRotation.y = MoveRotation(((int)MainCamera.Rot().y + ANGLE_225) % 360);
		}
	}

	Move();//移動させる

}
/*動かすときの処理
forward = 方向設定
velocity = 力
*/
void CXCharPlayer::Move(){

	CMatrix44 rot_y, pos, matrix;
	CVector3 moveForward = mForward;//参照でいじれないので
	//回転行列の作成
	rot_y.rotationY(mRotation.y);
	///進行方向を計算
	moveForward = mForward * rot_y;
	//移動させる
	mPosition += moveForward * mVelocity;
}


/*重力*/
void CXCharPlayer::Gravity(){
	/*地面についていないなら*/
	mPosition.y -= GRAVITY(mGravitTime);
	mGravitTime += GRA_TIME_UP;//時間が経つ
}
/*グラウンドの設定*/
void CXCharPlayer::ColGround(){
	mGravitTime = GRA_INIT_TIME_COUNT;
	mFlagJump = false;//ジャンプ終了
}

/*更新処理*/
void CXCharPlayer::Update(){
	mAdjust = CVector3();
	mPrevPos = mPosition;
	Gravity();/*重力*/
	PosUpdate();//ポジションを更新

	/*ステータスマシン更新*/
	mStateMachine->Update();
	//状態によりアニメーション変化
	switch (mState)
	{
	case E_IDLING://立ち

		mCountKnockBack = 0;
		break;
	case E_RUN://走る
		break;
	case E_ATTACK_RUN://攻撃走る
		break;
	case E_ATTACK_INIT:
		ChangeAnimation(E_ATTACK_INIT, false, ANIMA_SPEED_ATTCK);
		break;
	case E_ATTACK://攻撃
		break;
	case E_ATTACK_IDLING:
		ChangeAnimation(E_ATTACK_IDLING, true, ANIMA_SPEED_ATTCK);
		break;
	case E_JUMP:
		ChangeAnimation(E_JUMP, false, ANIMA_SPEED_JUMP);
		break;
	case E_ATTACK_JUMP:
		ChangeAnimation(E_ATTACK_JUMP, false, ANIMA_SPEED_JUMP);
		break;
	case E_DMGM://ダメージ
		ChangeAnimation(E_DMGM, false, ANIMA_SPEED);
		if (mCountKnockBack <= 0){ //カウントが０になると
			mCountKnockBack = 0;
		}
		else{
			mCountKnockBack -= 1;
		}
		break;
	};
}



/*Render*/
void CXCharPlayer::Render() {
	//27
	//HPバーの設定
	//mHpBar.mPosition = mPosition;
	//mHpBar.mPosition.y += 1.8f;
	//mHpBar.Update();	//更新
	//mHpBar.Render();	//描画
	CModelXS::Render();
#ifdef _DEBUG
	//	mpCBBody->Render();
	//	mpCBWeapon->Render();
	//	mpCBLeg->Render();
	//	mpColCapsule->Render();
#endif
}

/*エフェクトの描画処理*/
void CXCharPlayer::BillboardRender(){
	CVector3 pos = HAMMER_EFFECT_POS;
	pos = pos * mpCombinedMatrix[mpModel->FindFrame("metarig_WeaponHandle")->mIndex];//マトリックスから

}

/*あたり判定の時に呼び出し*/
void CXCharPlayer::ColMove(int count, CVector3 Forward){
	if (count <= -1){//カウントがマイナスなら
		mVelocity = -KNOCK_BACK; //後ろ向きにする
		count *= -1;//プラスにする
	}
	else
	{
		mVelocity = -KNOCK_BACK;
	}
	mForward = Forward;
	mCountKnockBack = count;
}

/*当たり判定呼び出し
元の場所に戻すための関数
*/
bool CXCharPlayer::Collision(const COBB &box, const CColSphere &sphere) {
	return Collision(&box, &sphere);
}

bool CXCharPlayer::Collision(const COBB *box, const CColSphere *sphere) {
	return true;
}




/*当たり判定*/
bool CXCharPlayer::Collision(CCollider2* me, CCollider2* you) {
	
	switch (me->eColTag) {
	case E_COL_CAPSULE:
		if (you->eColTag == E_COL_TRIANGLE &&
			(you->eTag == E_TAG_GROUND ||
			you->eTag == E_TAG_WALL)) {
			CVector3 cross;
			float length;
			CVector3 adjust;
			if (CCollision::IntersectTriangleCapsule3(you->mV[1][0], you->mV[1][1], you->mV[1][2],
				me->mV[1][0], me->mV[1][1], me->mF[0], &adjust, &cross, &length)) {
				if (cross == CVector3())
					return false;
				//				if (you->eTag == E_TAG_BOX)
				ColGround();//地面にあった時の処理
				mPosition = mPosition + adjust;
			}
		}
		break;
	case E_COL_SPHEPE:
		if (you->eTag == E_TAG_GROUND) {
			if (you->eColTag == E_COL_BOX)
				return Collision((COBB*)&you->mObb, (CColSphere*)&me->mColSphere);
		}
	}

	return false;
}
void SetAdjust(CVector3 *s, const CVector3 &t) {
	//x
	if (s->x > 0) {
		if (t.x > 0) {
			if (s->x < t.x)
				s->x = t.x;
		}
		else {
			if (s->x < -t.x)
				s->x = t.x;
		}
	}
	else {
		if (t.x > 0) {
			if (-s->x < t.x)
				s->x = t.x;
		}
		else {
			if (-s->x < -t.x)
				s->x = t.x;
		}
	}
	//y
	if (s->y > 0) {
		if (t.y > 0) {
			if (s->y < t.y)
				s->y = t.y;
		}
		else {
			if (s->y < -t.y)
				s->y = t.y;
		}
	}
	else {
		if (t.y > 0) {
			if (-s->y < t.y)
				s->y = t.y;
		}
		else {
			if (-s->y < -t.y)
				s->y = t.y;
		}
	}
	//z
	if (s->z > 0) {
		if (t.z > 0) {
			if (s->z < t.z)
				s->z = t.z;
		}
		else {
			if (s->z < -t.z)
				s->z = t.z;
		}
	}
	else {
		if (t.z > 0) {
			if (-s->z < t.z)
				s->z = t.z;
		}
		else {
			if (-s->z < -t.z)
				s->z = t.z;
		}
	}
}
//m 自分　y 相手
bool CXCharPlayer::Collision(CCollider3* m, CCollider3* y) {
	//CCollider3 *m = (CCollider3*)me;
	//CCollider3 *y = (CCollider3*)you;

	switch (m->mType) {
	case CCollider3::COL_CAPSULE:
		CCollider3Capsule *cc = (CCollider3Capsule*)m;
		switch (y->mType) {
		case CCollider3::COL_TRIANGLE:
			CCollider3Triangle ct = (*(CCollider3Triangle*)y).GetUpdate();
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
				UpdateSkinMatrix(matrix);
			}
			break;
		}
		break;
	}

	return false;
}

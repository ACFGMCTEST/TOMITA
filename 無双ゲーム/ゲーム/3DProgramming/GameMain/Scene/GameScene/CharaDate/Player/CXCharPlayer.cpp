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
#include "State\RunAttack\CStatePlayerRunAttack.h"
/*当たり判定*/
#include "../../../../Collision/ColType/CColCapsule.h"
#include "../../../../Collision/ColType/CColTriangle.h"

/*向き*/
#define FORWARD_JUMP  0.0f,1.0f,1.0f//ジャンプ

/*あたり判定の設定値(main)*/
#define COL_RADIUS 0.6f//半径
#define COL_POS CVector3(0,1.5f,0),CVector3(0,-1.0f,0)//ポジションカプセル
#define COL_MATRIX(string) &mpCombinedMatrix[model->FindFrame(string)->mIndex]//マトリックス
/*腕*/
#define COL_ATTACK_RADIUS 0.4f
#define COL_RIGHT_POS CVector3(0.0f,0.5f,0.0f)
#define COL_LEFT_POS  CVector3(0.0f,0.5f,0.0f)
#define COL_LEFT_MATRIX(string)  &mpCombinedMatrix[model->FindFrame (string)->mIndex]//マトリックス
#define COL_RIGHT_MATRIX(string) &mpCombinedMatrix[model->FindFrame(string)->mIndex]//マトリックス


/*HPバーの設定値*/
#define HP_BAR_POS CVector3(mPosition.x,mPosition.y + 1.8f,mPosition.z)
#define HP_BAR_SIZE -0.4f, 0.4f, -0.1f, 0.0f

/*動きの回転する速さ*/
#define TURN_SPEED 10

CXCharPlayer::CXCharPlayer() : mVelocity(0.0f), mFlagKnockback(false), mRotCount(0),
mGravitTime(GRA_INIT_TIME_COUNT), mFlagJump(false), mAdjust()
{
	eName = CTask::E_PLAYER;
	mForward = CVector3(FORWARD);
	mpParent = this;
};
/*
Init
モデルと衝突判定の設定を行う
*/
void CXCharPlayer::Init(CModelX *model) {
	mStateMachine = (std::make_unique<CStateMachine>());
	// 第一引数にステートの「登録名」
	// 第二引数でStateBaseを継承したクラスのshared_ptrオブジェクトを生成
	mStateMachine->Register(PL_STATE_ATTACK, std::make_shared<CStatePlayerAttack>(), this);
	mStateMachine->Register(PL_STATE_IDLING, std::make_shared<CStatePlayerIdling>(), this);
	mStateMachine->Register(PL_STATE_RUN, std::make_shared<CStatePlayerRun>(), this);
	mStateMachine->Register(PL_STATE_JUMP, std::make_shared<CStatePlayerJump>(), this);
	mStateMachine->Register(PL_STATE_RUN_ATTACK, std::make_shared<CStatePlayerRunAttack>(), this);
	// 最初のステートを登録名で指定
	mStateMachine->SetStartState(PL_STATE_IDLING);

	//モデルの設定
	CModelXS::Init(model);

	//カプセル　キャラクタ全体
	new CColCapsule(this, COL_POS, COL_RADIUS, COL_MATRIX("metarig_hips"));
	mpMatrix = COL_MATRIX("metarig_hips");
	//球体　腕.右
	new CColSphere(this, COL_RIGHT_POS, COL_ATTACK_RADIUS, COL_RIGHT_MATRIX("metarig_forearm_L"));
	//球体　腕.左
	new CColSphere(this, COL_LEFT_POS, COL_ATTACK_RADIUS, COL_LEFT_MATRIX("metarig_forearm_R"));

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

}



/*Render*/
void CXCharPlayer::Render() {
	CModelXS::Render();
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



void CXCharPlayer::SetAdjust(CVector3 *s, const CVector3 &t) {
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

/*玉バージョン*/
void CXCharPlayer::Collision(CColSphere *youSphere,CColSphere *sphere) {
	CVector3 savePos = sphere->mPos;//計算用
	float lengthX = mPosition.x - savePos.x;  //球とポジションの距離
	float lengthY = mPosition.y - savePos.y;  //球とポジションの距離
	float lengthZ = mPosition.z - savePos.z;  //球とポジションの距離
	//BoxのX軸方向を求める
	CVector3 vx = *youSphere->mpCombinedMatrix * VEC_RIGHT;
	//BoxのY軸方向を求める
	CVector3 vy = *youSphere->mpCombinedMatrix * VEC_TOP;
	//BoxのZ軸方向を求める
	CVector3 vz = *youSphere->mpCombinedMatrix * VEC_FRONT;
	//四角形から球へのベクトルを求める
	CVector3 vectorBS = savePos - youSphere->mPos;
	//四角形から球へ、四角形のX軸に対する長さとの差を求める
	float dx = sphere->mRadius + youSphere->mRadius - fabs(vx.Dot(vectorBS));
	//四角形から球へ、四角形のY軸に対する長さとの差を求める
	float dy = sphere->mRadius + youSphere->mRadius - fabs(vy.Dot(vectorBS));
	//四角形から球へ、四角形のZ軸に対する長さとの差を求める
	float dz = sphere->mRadius + youSphere->mRadius - fabs(vz.Dot(vectorBS));

	//衝突しているか判定する
	if (dx > 0.0f && dy > 0.0f && dz > 0.0f) {
		if (dx > dy) {
			if (dy > dz) {
				//Z軸で戻す
				if (vz.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vz * dz;
				}
				else {
					mPosition = savePos - vz * dz;
				}
			}
			else {
				/*球がボディの時判定 && ジャンプしていないとき*/
				//Y軸で戻す
				if (vy.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vy * dy;
				}
				else {
					mPosition = savePos - vy * dy;
				}
			}
		}
		else{
			if (dx > dz) {

				//Z軸で戻す
				if (vz.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vz * dz;
				}
				else {
					mPosition = savePos - vz * dz;
				}
			}
			else {

				//X軸で戻す
				if (vx.Dot(vectorBS) > 0.0f) {
					mPosition = savePos + vx * dx;
				}
				else {
					mPosition = savePos - vx * dx;
				}
			}
		}
	}
	mPosition.x += lengthX;
	mPosition.y += lengthY;
	mPosition.z += lengthZ;

	/*マトリックスだけ更新*/
	CMatrix44 rot_y, pos, matrix;
	//回転行列の作成
	rot_y.rotationY(mRotation.y);

	//移動行列を計算する
	pos.translate(mPosition);
	//回転移動行列を求める
	matrix = pos * rot_y;
	//頂点データの更新
	CModelXS::MatrixUpdate(matrix);

}


/*カプセル内当たり判定*/
void CXCharPlayer::CapsuleCol(CColCapsule *cc, CColBase* y){
	CColTriangle ct(false);//三角形の当たり判定
	CColCapsule  caps(false);//カプセルの当たり判定
	/*相手のタイプ何か判断*/
	switch (y->mType) {
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
			CModelXS::Update(matrix);
		}
		break;
		/*相手がカプセルの場合*/
	case CColBase::COL_CAPSULE:
		//caps = (*(CColCapsule*)y).GetUpdate();//カプセルにする
		//
		//if (CCollision::CollisionCapsule(cc, &caps)){
		//	/*球体*/
		//	CColSphere TopColA(cc->mRadius, cc->mV[0], cc->mpCombinedMatrix);
		//	CColSphere TopColB(caps.mRadius, caps.mV[0], caps.mpCombinedMatrix);
		//	CColSphere BottomColA(cc->mRadius, cc->mV[1], cc->mpCombinedMatrix);
		//	CColSphere BottomColB(caps.mRadius, caps.mV[1], caps.mpCombinedMatrix);
		//	/*当たり判定*/
		//	Collision(TopColA, TopColB);
		//};
	


		break;
	};
}
/*球体内の当たり判定*/
void CXCharPlayer::SphereCol(CColSphere *sphere, CColBase *y){
	CColSphere  sph;//球の当たり判定
	/*相手のタイプ何か判断*/
	switch (y->mType) {
		/*相手が球の場合*/
	case CColBase::COL_SPHEPE:
		sph = (*(CColSphere*)y).GetUpdate();
		/*当たり判定計算　*/
		if (CCollision::CollisionShpere(sph,*sphere) && sph.mpParent->eName == CTask::E_SLIME){
			printf("今当たっているエネミーの番号(%d)\n", sph.mpParent->mNumber);
			Collision(&sph,sphere);
		}

	};
}


//m 自分　y 相手
bool CXCharPlayer::Collision(CColBase* m, CColBase* y) {
	//CColBase *m = (CColBase*)me;
	//CColBase *y = (CColBase*)you;
	CColCapsule cc(false);
	CColSphere sph;
	/*自分のタイプが何か判断*/
	switch (m->mType) {

	case CColBase::COL_CAPSULE://自分の当たり判定がカプセルの場合
		cc = *(CColCapsule*)m;//カプセルにする
		CapsuleCol(&cc, y);//カプセルの当たり判定
		break;
		
	case CColBase::COL_SPHEPE:
		sph = *(CColSphere*)m;//球体
		SphereCol(&sph, y);//球体の当たり判定
		
	};

	return false;
}

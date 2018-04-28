#include "CXCharPlayer.h"
#include "windows.h"
#include "../../../Key/CKey.h"
#include "CSceneModel.h"
#include "../../../../Define/Define.h"
#include "../Map/CMap.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "../../GameScene/Map/CMap.h"
#include "../../ItemScene/CItem.h"
#include "../../../Camera/CCamera.h"
#include "../../../Convenient/CConvenient.h"
#include <math.h>


/*向き*/
#define FORWARD_JUMP  0.0f,1.0f,1.0f//ジャンプ

/*動きの回転する速さ*/
#define TURN_SPEED 10
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

/*ジャンプのスピード*/
#define JUMP_SPEED 0.7f//ジャンプするスピード
#define JUMP_MOVE(vel) vel * 0.7f//ジャンプ移動 

/*歩く加速度*/
#define MOVE_ACC SPEED_RUN/10

CXCharPlayer::CXCharPlayer() : mVelocity(0.0f), mFlagKnockback(false), mRotCount(0),
mGoCount(0), mGoPos(0), mGoPosSize(0), mGravitTime(GRA_INIT_TIME_COUNT), mFlagJump(false),mFlagSlpoe(false){
	mForward = CVector3(FORWARD);
	mpParent = this;


	mState = E_IDLING;
	ePriority = CTask::E_PLAYER;

	

};

/*当たり判定初期化*/
void CXCharPlayer::ColInit(){
	/*当たり判定インスタンス作成*/
	mpCBBody = new CCollider(CTask::E_COL_SPHEPE);
	mpCBLeg = new CCollider(CTask::E_COL_SPHEPE);
	
	/*ペアレント設定*/
	mpCBBody->mpParent = this;
	mpCBLeg->mpParent = this;
}

/*Init = モデルと衝突判定の設定を行う*/
void CXCharPlayer::Init(CModelX *model) {
	ColInit();

	//モデルの設定
	CModelXS::Init(model);
	
	/*体の当たり判定*/
	mpCBBody->SetShere(OBB_SPHERE_BODY_SIZE, OBB_SPHERE_BODY_POS
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);
	/*足の当たり判定*/
	mpCBLeg->SetShere(OBB_LEG_SIZE, OBB_LEG_POS
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);


	mpCBBody->SetColor(BLUE_COLOR);//ボディーの色決め
	//mpModel->SetColor(RED_COLOR);//モデルの色決め
	mPower = ATTACK_POWER;//攻撃力

	mVelocity = SPEED_RUN;

	PosUpdate();
	mPrevPos = mPosition;

}

/*速さ制御関数*/
float VelocityMax = SPEED_RUN;//限界値
void CXCharPlayer::MoveSpeed(){


	/*スキル発動時*/
	
		/*攻撃準備中*/
		if (mState == E_ATTACK_IDLING || mState == E_ATTACK_RUN) VelocityMax = SPEED_ATTACK_RUN;
		/*攻撃外*/
		if (mState == E_RUN)VelocityMax = SPEED_RUN;
	
	/*限界値まで加速*/
	if (VelocityMax > mVelocity){
		mVelocity += MOVE_ACC;//加速
	}
	else{
		mVelocity = VelocityMax;//限界値にする
	}

	/*ジャンプ中で移動している場合減速　初回のみ*/
	if (mState == E_ATTACK_JUMP || mState == E_JUMP){
		if (mVelocity == SPEED_ATTACK_RUN_SKILL || mVelocity == SPEED_ATTACK_RUN ||
			mVelocity == SPEED_RUN_SKILL || mVelocity == SPEED_RUN){
			mVelocity -= SPEED_JUMP_DOWN;
		}
	}
	/*動いていない場合*/
	if (mState == E_IDLING || mState == E_ATTACK_IDLING){ mVelocity = 0; }
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
}
/*簡易移動フラグ*/
bool CXCharPlayer::FlagMove(){
	if (CKey::push('A') || CKey::push('D') || CKey::push('S') || CKey::push('W')){
		if (mState != E_ATTACK && mState != E_ATTACK_INIT){//アイドル中か走っているか
			return true;
		}
	}
	return false;
}


/*動くときの関数*/
void CXCharPlayer::MyMove(){
	
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






	/*ステータス設定*/
	if (FlagMove() && mCountKnockBack == 0){//Knockbackしていなければ
		/*走る距離;回転値;走るのアニメに切り替え*/
		AnimaState(E_ATTACK_RUN); //溜めながら走る
		AnimaState(E_RUN);
	}
	else{
		AnimaState(E_ATTACK_IDLING);
		AnimaState(E_IDLING);
	}
	MoveSpeed();//移動量変化関数
	if (FlagMove() && mState != E_IDLING && mState != E_ATTACK_IDLING && mState != E_ATTACK_INIT &&
		mState != E_JUMP && mState != E_ATTACK_JUMP){//走り時は移動
		//進行方向設定　z軸プラスが前方のモデル 坂に上っていないとき
		if (!mFlagSlpoe)mForward = CVector3(FORWARD);
		//else mForward = CVector3(0.0f, 0.5f, 1.0f);

		/*坂をfalseに*/
		mFlagSlpoe = false;

		Move(mForward,mVelocity);//移動させる
	}


}

/*動かすときの処理
forward = 方向設定
velocity = 力
*/
void CXCharPlayer::Move(const CVector3 &forward,float velocity){

	CMatrix44 rot_y, pos, matrix;
	CVector3 moveForward = forward;//参照でいじれないので
	//回転行列の作成
	rot_y.rotationY(mRotation.y);
	///進行方向を計算
	moveForward = forward * rot_y;
	//移動させる
	mPosition += moveForward * velocity;
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
	AnimaState(E_ATTACK_IDLING);
	AnimaState(E_IDLING);
}



/*アタックのステータス*/
bool CXCharPlayer::FlagAttackState(){
	return (mState == E_ATTACK_IDLING || mState == E_ATTACK_INIT || mState == E_ATTACK_RUN);
}

/*簡易アニメーション切り替え*/
void CXCharPlayer::AnimaState(ESTATE state){





	switch (state)
	{
		/*待機中*/
	case CTask::E_IDLING:
		/*攻撃でない場合 ジャンプ出ない場合*/
		if (!FlagAttackState() && !mFlagJump){
			if (mState == E_RUN || mState == E_ATTACK && mAnimationTime > mpModel->mAnimationSet[mAnimationIndex]->mMaxTime)
				mState = state;
		}
		/*ジャンプの場合 フレームが最後の時は処理をしていい*/
		if (mState == E_JUMP && mAnimationTime > mpModel->mAnimationSet[mAnimationIndex]->mMaxTime){
			mState = state;
		}
		//DAMAGEが終わっている場合
		if (mState == E_DMGM && mAnimationTime > mpModel->mAnimationSet[mAnimationIndex]->mMaxTime){
			mState = state;
		}
		break;

		/*走り中*/
	case CTask::E_RUN:
		if (!mFlagJump && mState != E_ATTACK_IDLING && mState != E_ATTACK_JUMP &&
			mState != E_ATTACK_RUN && mState != E_ATTACK){
			mState = state;
		}

		break;


		/*攻撃ため走り中*/
	case CTask::E_ATTACK_RUN:
		/*アタックアイドル中であり移動している場合*/
		if (mState == E_ATTACK_IDLING){
			mState = state;
		}
		break;


		/*攻撃準備中*/
	case CTask::E_ATTACK_INIT:

		/*アタックをしていない時*/
		if (!FlagAttackState() && mState != E_ATTACK && mState != E_ATTACK_JUMP){
				mState = state;
		}

		break;


		/*攻撃中*/
	case CTask::E_ATTACK:
		if (mState == E_ATTACK_INIT || mState == E_ATTACK_IDLING || mState == E_ATTACK_RUN || mState == E_ATTACK_JUMP)
			mState = state;
		break;


		/*攻撃待機中*/
	case CTask::E_ATTACK_IDLING:
		/*攻撃準備が終わったら*/
		if (mState == E_ATTACK_INIT && mAnimationTime > mpModel->mAnimationSet[mAnimationIndex]->mMaxTime){
			mState = state;
		}
		/*走っているとき*/
		if(mState == E_ATTACK_RUN){
			mState = state;
		}
		/*アタックジャンプが終了したとき*/
		if (mState == E_ATTACK_JUMP && mAnimationTime > mpModel->mAnimationSet[mAnimationIndex]->mMaxTime){
			mState = state;
		}
		break;


		/*攻撃ジャンプ*/
	case CTask::E_ATTACK_JUMP:
		if (FlagAttackState() && mState != E_JUMP && mState != E_ATTACK){
			mState = state;
		}
		break;


		/*ジャンプ*/
	case CTask::E_JUMP:

		if (!FlagAttackState() && mState != E_ATTACK_JUMP && mState != E_ATTACK){
			mState = state;
		}
		break;


		/*ダメージ*/
	case CTask::E_DMGM:
		mState = state;
		break;
	default:
		break;
	}
}
/*キャラクター回転差が小さい方向に回転する*/
int CXCharPlayer::MoveRotation(int angle){

	/*右回り*/
	int turnRight = angle - mRotation.y;
	/*過剰余剰*/
	LIMIT_ANGLE(turnRight);
	/*左回り*/
	int turnLeft = ANGLE_360  - turnRight;

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
	else{return mRotation.y - TURN_SPEED;
	}
	
	
}

/*更新処理*/
void CXCharPlayer::Update(){
	mPrevPos = mPosition;
	mFlagSlpoe = false;
	//キャラクターが選ばれているものか判断 && DAMAGEをくらっていない場合
	if (mState != E_DMGM){

		//スキル発動！！！
		if (CKey::push(KEY_SKILL)){
			mSkillTime = mGageLimit;
		}
	

		///*一回押したとき*/
		if (AttackInitKey.push(KEY_ATTACK) || AttackInitKey.push(KEY_ATTACK2) || CMouse::GetInstance()->mOneLeftFlag){//Kボタンか
			AnimaState(E_ATTACK_INIT); //初めのいっかいだけ呼び出す
		}
		/*長押しの時*/
		else if (CKey::push(KEY_ATTACK) || CKey::push(KEY_ATTACK2) || CMouse::GetInstance()->mLeftFlag){
			//スキルゲージ増加
			AnimaState(E_ATTACK_IDLING);
		}
		/*離したとき*/
		else{
			AnimaState(E_ATTACK);
		}

		MyMove();//動く処理

		/*ジャンプ*/
		if (CKey::once(KEY_JUMP) || mFlagJump){
			mFlagJump = true;

			AnimaState(E_ATTACK_JUMP);
			AnimaState(E_JUMP);
		}
	
		
	}

	if (mFlagJump)Jump();//フラグが立っているときジャンプ
	Gravity();/*重力*/
	MoveSpeed();
	PosUpdate();//ポジションを更新


	//当たり判定更新
	mpCBBody->Update();
	mpCBLeg->Update();
	//状態によりアニメーション変化
	switch (mState)
	{
	case E_IDLING://立ち
		
		ChangeAnimation(E_IDLING, true, ANIMA_SPEED_IDOL);
		mCountKnockBack = 0;
		break;
	case E_RUN://走る
		ChangeAnimation(E_RUN, true, ANIMA_SPEED_RUN);
		break;
	case E_ATTACK_RUN://攻撃走る
		ChangeAnimation(E_ATTACK_RUN, true, ANIMA_SPEED_RUN);
		HammerUp();//Hammerの溜める処理
		
		break;
	case E_ATTACK_INIT:
		ChangeAnimation(E_ATTACK_INIT, false, ANIMA_SPEED_ATTCK);
		break;
	case E_ATTACK://攻撃
		ChangeAnimation(E_ATTACK, false, ANIMA_SPEED_ATTCK);
		//アニメーションが終了
		if (mAnimationTime >
			mpModel->mAnimationSet[mAnimationIndex]->mMaxTime){
			HammerInit();
		}
		break;
	case E_ATTACK_IDLING:
		ChangeAnimation(E_ATTACK_IDLING, true, ANIMA_SPEED_ATTCK);
		HammerUp();//Hammerの溜める処理
		break;
	case E_JUMP:
		ChangeAnimation(E_JUMP, false, ANIMA_SPEED_JUMP);
		break;
	case E_ATTACK_JUMP:
		ChangeAnimation(E_ATTACK_JUMP, false, ANIMA_SPEED_JUMP);
		break;
	case E_DMGM://ダメージ
		ChangeAnimation(E_DMGM, false, ANIMA_SPEED_DAMAGE);
		HammerInit();
	
		break;
	};
	AnimaState(E_ATTACK_IDLING);
	AnimaState(E_IDLING);
}

/*Hammerの溜める処理*/
void CXCharPlayer::HammerUp(){
	mPower += POWER_UP;//ためていくと攻撃力が上がる
	if (mPower >= ATTACK_POWER_MAX){
		mPower = ATTACK_POWER_MAX;
	}
	else{
	}
}

/*Hammerの初期化処理*/
void CXCharPlayer::HammerInit(){
	mPower = ATTACK_POWER;//戻す
}

/*Render*/
void CXCharPlayer::Render() {
	
	CModelXS::Render();
#ifdef _DEBUG
	mpCBBody->Render();
	mpCBLeg->Render();
#endif
}

/*エフェクトの描画処理*/
void CXCharPlayer::BillboardRender(){
	CVector3 pos = HAMMER_EFFECT_POS;
	pos = pos * mpCombinedMatrix[mpModel->FindFrame("metarig_WeaponHandle")->mIndex];//マトリックスから計算

}



/*当たり判定呼び出し
元の場所に戻すための関数
*/
void CXCharPlayer::Collision(const COBB &box,const CColSphere &sphere) {



	CVector3 savePos = sphere.mPos;//計算用

	float lengthX = mPosition.x - savePos.x;  //球とポジションの距離
	float lengthY = mPosition.y - savePos.y;  //球とポジションの距離
	float lengthZ = mPosition.z - savePos.z;  //球とポジションの距離


	//BoxのX軸方向を求める
	CVector3 vx = box.mMatrixRotation * VEC_RIGHT;
	//BoxのY軸方向を求める
	CVector3 vy = box.mMatrixRotation * VEC_TOP;
	//BoxのZ軸方向を求める
	CVector3 vz = box.mMatrixRotation * VEC_FRONT;

	vx = box.mAxis[0];
	vy = box.mAxis[1];
	vz = box.mAxis[2];



	//四角形から球へのベクトルを求める
	CVector3 vectorBS = savePos - box.mPos;


	//四角形から球へ、四角形のX軸に対する長さとの差を求める
	float dx = sphere.mRadius + box.mLength[0] - fabs(vx.Dot(vectorBS));
	//四角形から球へ、四角形のY軸に対する長さとの差を求める
	float dy = sphere.mRadius + box.mLength[1] - fabs(vy.Dot(vectorBS));
	//四角形から球へ、四角形のZ軸に対する長さとの差を求める
	float dz = sphere.mRadius + box.mLength[2] - fabs(vz.Dot(vectorBS));

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
				//if (&sphere == &mpCBLeg->mColSphere){
					ColGround();//地面にあった時の処理
					//Y軸で戻す
					if (vy.Dot(vectorBS) > 0.0f) {
						mPosition = savePos + vy * dy;
					}
					else {
						mPosition = savePos - vy * dy;
					}
				//}
			
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

	//当たり判定更新
	mpCBBody->Update();
	mpCBLeg->Update();
	
}
/*玉バージョン*/
void CXCharPlayer::Collision(const CColSphere &youSphere, const CColSphere &sphere) {



	CVector3 savePos = sphere.mPos;//計算用

	float lengthX = mPosition.x - savePos.x;  //球とポジションの距離
	float lengthY = mPosition.y - savePos.y;  //球とポジションの距離
	float lengthZ = mPosition.z - savePos.z;  //球とポジションの距離


	//BoxのX軸方向を求める
	CVector3 vx = youSphere.mMatrixRotation * VEC_RIGHT;
	//BoxのY軸方向を求める
	CVector3 vy = youSphere.mMatrixRotation * VEC_TOP;
	//BoxのZ軸方向を求める
	CVector3 vz = youSphere.mMatrixRotation * VEC_FRONT;



	//四角形から球へのベクトルを求める
	CVector3 vectorBS = savePos - youSphere.mPos;


	//四角形から球へ、四角形のX軸に対する長さとの差を求める
	float dx = sphere.mRadius + youSphere.mRadius - fabs(vx.Dot(vectorBS));
	//四角形から球へ、四角形のY軸に対する長さとの差を求める
	float dy = sphere.mRadius + youSphere.mRadius - fabs(vy.Dot(vectorBS));
	//四角形から球へ、四角形のZ軸に対する長さとの差を求める
	float dz = sphere.mRadius + youSphere.mRadius - fabs(vz.Dot(vectorBS));

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
				//if (&sphere == &mpCBLeg->mColSphere){
					ColGround();//地面にあった時の処理
					//Y軸で戻す
					if (vy.Dot(vectorBS) > 0.0f) {
						mPosition = savePos + vy * dy;
					}
					else {
						mPosition = savePos - vy * dy;
					}
				//}

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

	//当たり判定更新
	mpCBBody->Update();
	mpCBLeg->Update();

}



/*ジャンプ関数*/
void  CXCharPlayer::Jump(){
	Move(mForward, JUMP_MOVE(mVelocity));
	float jumpVilocity = JUMP_SPEED - GRAVITY(mGravitTime);//動かす力
	/*ジャンプが0より大きい場合*/
		mPosition.y += jumpVilocity;
	

}

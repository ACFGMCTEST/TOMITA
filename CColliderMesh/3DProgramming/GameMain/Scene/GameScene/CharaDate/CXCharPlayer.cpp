#include "CXCharPlayer.h"
#include "windows.h"
#include "../../../Key/CKey.h"
#include "CSceneModel.h"
#include "../../../../Define/Define.h"
#include "../Map/CMap.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "../UI/CScoreBoard.h"
#include "../../GameScene/Map/CMap.h"
#include "../../ItemScene/CItem.h"
#include <math.h>
#include "../../../Collision/CCollisionManager.h"
#include "../../../Collision/CCollision.h"


/*向き*/
#define FORWARD_JUMP  0.0f,1.0f,1.0f//ジャンプ

/*あたり判定の設定値*/
/*胴*/
#define OBB_SPHERE_BODY_SIZE 0.4f
#define OBB_SPHERE_BODY_POS CVector3(0.0f,0.0f,0.0f)
/*武器*/
#define OBB_WEAPON_POS CVector3(0.0f,0.5f,0.0f)
#define OBB_WEAPON_SIZE new float[]{0.4f, 0.7f, 0.4f}
/*足*/
#define OBB_LEG_SIZE 0.3f
#define OBB_LEG_POS CVector3(0.0f,-1.0f,0.0f)

/*HPバーの設定値*/
#define HP_BAR_POS CVector3(mPosition.x,mPosition.y + 1.8f,mPosition.z)
#define HP_BAR_SIZE -0.4f, 0.4f, -0.1f, 0.0f

/*ジャンプのスピード*/
#define JUMP_SPEED 0.7f//ジャンプするスピード
#define JUMP_MOVE(vel) vel * 0.7f//ジャンプ移動 



CXCharPlayer::CXCharPlayer() : mVelocity(0.0f), mFlagKnockback(false), mRotCount(0),
mGoCount(0), mGoPos(0), mGoPosSize(0), mGravitTime(GRA_INIT_TIME_COUNT), mFlagJump(false),mFlagSlpoe(false){
	mForward = CVector3(FORWARD);
	mpParent = this;

	mState = E_IDLE;
	ePriority = CTask::E_PLAYER;

};

/*当たり判定初期化*/
void CXCharPlayer::ColInit(){
	/*当たり判定インスタンス作成*/
	mpCBBody = new CCollider(CTask::E_COL_SPHEPE);
	mpCBWeapon = new CCollider(CTask::E_COL_BOX);
	mpCBLeg = new CCollider(CTask::E_COL_SPHEPE);

	mpColCapsule = new CColCapsule();
	mpColCapsule3 = new CCollider3Capsule();

	/*ペアレント設定*/
	mpCBBody->mpParent = this;
	mpCBWeapon->mpParent = this;
	mpCBLeg->mpParent = this;
}

/*
 Init
 モデルと衝突判定の設定を行う
*/
void CXCharPlayer::Init(CModelX *model) {
	ColInit();

	//モデルの設定
	CModelXS::Init(model);
	
	/*体の当たり判定*/
	mpCBBody->SetShere(OBB_SPHERE_BODY_SIZE, OBB_SPHERE_BODY_POS
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);
	/*武器の当たり判定*/
	mpCBWeapon->SetBoxOBB(OBB_WEAPON_POS, OBB_WEAPON_SIZE
		, &mpCombinedMatrix[model->FindFrame("metarig_WeaponHandle")->mIndex]);
	/*足の当たり判定*/
	mpCBLeg->SetShere(OBB_LEG_SIZE, OBB_LEG_POS
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);

//	mpColCapsule->Init(this, CVector3(0.0f, 0.7f, 0.0f), CVector3(0.0f, -0.7f, 0.0f), 0.5f, CVector3(0.0f, 0.0f, 0.0f)
	mpColCapsule->Init(this, CVector3(0.0f, 1.2f, 0.0f), CVector3(0.0f, -1.2f, 0.0f), 0.5f, CVector3(0.0f, 0.0f, 0.0f)
		//		, &mpCombinedMatrix[model->FindFrame("Root")->mIndex]);
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);
	mpColCapsule3->Init(this, CVector3(0.0f, 1.2f, 0.0f), CVector3(0.0f, -1.2f, 0.0f), 0.5f
		, &mpCombinedMatrix[model->FindFrame("metarig_chest")->mIndex]);

	mHammerEffect.Init(CEffect2D::E_STATUS::E_HAMMER);

	mpCBBody->SetColor(BLUE_COLOR);//ボディーの色決め
	//mpModel->SetColor(RED_COLOR);//モデルの色決め
	mPower = ATTACK_POWER;//攻撃力

	mVelocity = SPEED_RUN;

	PosUpdate();
	mPrevPos = mPosition;

//	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PLAYER, mpCBLeg);//あたり判定追加
//	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PLAYER, mpCBBody);//あたり判定追加
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_WEAPON, mpCBWeapon);//あたり判定追加

	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PLAYER, mpColCapsule);//あたり判定追加
	CCollisionManager3::GetInstance()->Add(mpColCapsule3);//あたり判定追加
}

/*速さ制御関数*/
void CXCharPlayer::MoveSpeed(){

	/*スキル発動時*/
	if (CScoreBoard::mFlagSkill0&&CItem::status==CItem::WEAPON0){
		if(mState == E_ATTACK_RUN)	mVelocity = SPEED_ATTACK_RUN_SKILL;

		if (mState == E_RUN)		mVelocity = SPEED_RUN_SKILL;
	}
	else{
		/*攻撃準備中*/
		if (mState == E_ATTACK_IDLE || mState == E_ATTACK_RUN) mVelocity = SPEED_ATTACK_RUN;
		/*攻撃外*/
		if (mState == E_RUN)mVelocity = SPEED_RUN;
	}
	/*ジャンプ中で移動している場合減速　初回のみ*/
	if (mVelocity == SPEED_ATTACK_RUN_SKILL || mVelocity == SPEED_ATTACK_RUN || 
		mVelocity == SPEED_RUN_SKILL || mVelocity == SPEED_RUN){
		mVelocity -= SPEED_JUMP_DOWN;
	}
	/*動いていない場合*/
	if (mState == E_IDLE || mState == E_ATTACK_IDLE){ mVelocity = 0; }
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
/*簡易移動フラグ*/
bool CXCharPlayer::FlagMove(){
	if (CKey::push('A') || CKey::push('D') || CKey::push('S') || CKey::push('W')){
		if (mState != E_ATTACK && mState != E_ATTACK_INIT){//アイドル中か走っているか
			return true;
		}
	}
	return false;
}

/*回転するまで移動しない*/
bool CXCharPlayer::FlagRotMove(int angle){
	int middle = abs((int)mRotation.y) % ANGLE_360;
	
	angle = (abs((int)CSceneModel::mRotation.y) + angle) % ANGLE_360;

	if (middle == angle){
		return true;
	}
	return false;
}


bool CXCharPlayer::FlagRight(){
	float Rot;
	if (mRotation.y <= ANGLE_180){
		Rot =mRotation.y;
	}
	else{
		Rot = mRotation.y - ANGLE_360;
	}

	if (Rot - CSceneModel::mRotation.y < ANGLE_90){

		return true;
	}
	else{
		return false;
	}
}
/*向きの制御*/
bool CXCharPlayer::DirectionAnima(){

	return true;
}

bool CXCharPlayer::FlagLeft(){
	
	float Rot;
	if (mRotation.y <= ANGLE_180){
		Rot = CSceneModel::mRotation.y - mRotation.y;
	}
	else{
		Rot = CSceneModel::mRotation.y - mRotation.y - ANGLE_360;
	}

	if (Rot < -ANGLE_90){
		return true;
	}
	else{
	
		return false;
	}
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

/*動くときの関数*/
void CXCharPlayer::MyMove(){
	if (mRotation.y >= ANGLE_360){
		mRotation.y = 0;
	}
	/*攻撃するときカメラの方向に向く*/
	if (mState == E_ATTACK || mState == E_ATTACK_INIT)	mRotation = CSceneModel::mRotation;


	if (CKey::push('A')){//左に移動
		///*回転*/
		//if (FlagLeft())PlusRot(ANGLE_5);//回転値代入
		//else 
			mRotation.y = ((int)CSceneModel::mRotation.y + ANGLE_90) % 360;

	}
	if (CKey::push('D')){//右に移動
		mRotation.y = ((int)CSceneModel::mRotation.y + ANGLE_270) % 360;
	}




	if (CKey::push('W')){//前に移動

		mRotation.y = CSceneModel::mRotation.y;


		if (CKey::push('A')){//左に移動
			///*回転*/
			//if (FlagLeft())PlusRot(ANGLE_5);//回転値代入
			//else 
			mRotation.y += ANGLE_45;

		}
		if (CKey::push('D')){//右に移動
			mRotation.y -= ANGLE_45;
		}


	}





	if (CKey::push('S')){

		mRotation.y = CSceneModel::mRotation.y;
		mRotation.y -= ANGLE_180;//反対向きにする


		if (CKey::push('A')){//左に移動
			mRotation.y -= ANGLE_45;

		}
		if (CKey::push('D')){//右に移動
			mRotation.y += ANGLE_45;

		}

	}


	/*ステータス設定*/
	if (FlagMove() && mCountKnockBack == 0){//Knockbackしていなければ
		/*走る距離;回転値;走るのアニメに切り替え*/
		AnimaState(E_ATTACK_RUN); //溜めながら走る
		AnimaState(E_RUN);
	}
	else{
		AnimaState(E_ATTACK_IDLE);
		AnimaState(E_IDLE);
	}
	MoveSpeed();//移動量変化関数
	if (FlagMove() && mState != E_IDLE && mState != E_ATTACK_IDLE && mState != E_ATTACK_INIT &&
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
}

/*経路探索　道筋用*/
void CXCharPlayer::CostMapping(int x, int z, int count,int *CostMap, bool FastFlag){
	//count++;
	////if (CMap::mNowMapDate[z][x] == CMap::E_BUIL || CMap::mNowMapDate[z][x] == CMap::E_HOLE) /*障害物判定*/
	//if (CMap::mNowMapDate[z][x] == CMap::E_GOAL_6 ) /*障害物判定*/
	//{
	//	return;//壁があったら
	//}
	//if (CostMap[z*CMap::mMapX + x] == -1){//初期値なら
	//	CostMap[z*CMap::mMapX + x] = count;//カウントを
	//}
	//else if (CostMap[z*CMap::mMapX + x] > count){
	//	CostMap[z*CMap::mMapX + x] = count;//カウントを
	//}
	//else return;
	//if (x < CMap::mMapX - 1) CostMapping(x + 1, z, count, CostMap, false);
	//if (x > 0) CostMapping(x - 1, z, count, CostMap, false);
	//if (z < CMap::mMapZ - 1)CostMapping(x, z + 1, count, CostMap, false);
	//if (z > 0)CostMapping(x, z - 1, count, CostMap, false);
}

/*経路探索　ゴールから自分の場所へ*/
void CXCharPlayer::SearchGoPos(int x, int z, int count, int *Arrysize, const int CostMap[], CVector4 **Pos, bool FastFlag){
	if (CostMap[z*CMap::mMapX + x] > 0){//コストの番号に値が入っている場合
		if (FastFlag){
			CVector4 dummy;
			(*Pos) = &dummy;
			(*Pos) = new CVector4[CostMap[z*CMap::mMapX + x]](); //FastFlag　初めの時だけtrue
			*Arrysize = CostMap[z*CMap::mMapX + x] - 1;//配列数記憶
		}

		(*Pos)[count] = CVector4((x - CMap::mMapX / 2) * (MAPCHIP_SIZE * 2), 0, (z - CMap::mMapZ / 2) * (MAPCHIP_SIZE * 2));//場所保存
		count++;

		if (CostMap[z*CMap::mMapX + x] == 1){
			return;//コストが０だったらこれ以下の処理を行わない
		}

#define  IF_NOLIMIT(z,x) CMap::mNowMapDate[z][x] != 1 &&\
	z >= 0 && x >= 0 && z < CMap::mMapZ && x < CMap::mMapX //障害物がないとき
		/*コストが一つだけ低いところに行く処理*/
		/*上の段*/
		if (CostMap[(z - 1)*CMap::mMapX + (x - 1)] + 1 == CostMap[z * CMap::mMapX + x]){ //左上
			SearchGoPos(x - 1, z - 1, count, Arrysize, CostMap, Pos, false);
			return;
		}
		if (CostMap[(z - 1) * CMap::mMapX + x] + 1 == CostMap[z*CMap::mMapX + x]){ //上
			SearchGoPos(x, z - 1, count, Arrysize, CostMap, Pos, false);
			return;
		}
		if (CostMap[(z - 1) * CMap::mMapX + x + 1] + 1 == CostMap[z*CMap::mMapX + x]){ //右上
			SearchGoPos(x + 1, z - 1, count, Arrysize, CostMap, Pos, false);
			return;
		}
		/*真ん中の段*/
		if (CostMap[z * CMap::mMapX + x - 1] + 1 == CostMap[z * CMap::mMapX + x]){ //左
			SearchGoPos(x - 1, z, count, Arrysize, CostMap, Pos, false);
			return;
		}
		if (CostMap[z * CMap::mMapX + x + 1] + 1 == CostMap[z * CMap::mMapX + x]){ //右
			SearchGoPos(x + 1, z, count, Arrysize, CostMap, Pos, false);
			return;
		}
		/*下の段*/
		if (CostMap[(z + 1) * CMap::mMapX + x - 1] + 1 == CostMap[(z * CMap::mMapX) + x]){ //左下
			SearchGoPos(x - 1, z + 1, count, Arrysize, CostMap, Pos, false);
			return;
		}
		if (CostMap[(z + 1) * CMap::mMapX + x] + 1 == CostMap[z * CMap::mMapX + x]){ //下
			SearchGoPos(x, z + 1, count, Arrysize, CostMap, Pos, false);
			return;
		}
		if (CostMap[(z + 1) * CMap::mMapX + x + 1] + 1 == CostMap[(z * CMap::mMapX) + x]){ //右下
			SearchGoPos(x + 1, z + 1, count, Arrysize, CostMap, Pos, false);
			return;
		}
	}
	return;
}

/*経路探索初期化処理*/
void CXCharPlayer::SearchGoPosInit(){
	/*mGoPosの初期化*/
	if (mGoPos != 0){ //値が入っているなら
		delete[] mGoPos;
		mGoPos = nullptr;
	}
	mGoCount = 0;//元に戻す
	mGoPosSize = 0;
}

/*アタックのステータス*/
bool CXCharPlayer::FlagAttackState(){
	return (mState == E_ATTACK_IDLE || mState == E_ATTACK_INIT || mState == E_ATTACK_RUN);
}

/*簡易アニメーション切り替え*/
void CXCharPlayer::AnimaState(ESTATE state){





	switch (state)
	{
		/*待機中*/
	case CTask::E_IDLE:
		/*攻撃でない場合 ジャンプ出ない場合*/
		if (!FlagAttackState() && !mFlagJump){
			if (mState == E_RUN || mState == E_ATTACK && mAnimationTime > mpModel->mAnimationSet[mAnimationIndex]->mMaxTime)
				mState = state;
		}
		/*ジャンプの場合 フレームが最後の時は処理をしていい*/
		if (mState == E_JUMP && mAnimationTime > mpModel->mAnimationSet[mAnimationIndex]->mMaxTime){
			mState = state;
		}
		break;

		/*走り中*/
	case CTask::E_RUN:
		if (!mFlagJump && mState != E_ATTACK_IDLE && mState != E_ATTACK_JUMP &&
			mState != E_ATTACK_RUN && mState != E_ATTACK){
			mState = state;
		}

		break;


		/*攻撃ため走り中*/
	case CTask::E_ATTACK_RUN:
		/*アタックアイドル中であり移動している場合*/
		if (mState == E_ATTACK_IDLE){
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
		if (mState == E_ATTACK_INIT || mState == E_ATTACK_IDLE || mState == E_ATTACK_RUN || mState == E_ATTACK_JUMP)
			mState = state;
		break;


		/*攻撃待機中*/
	case CTask::E_ATTACK_IDLE:
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

/*更新処理*/
void CXCharPlayer::Update(){
	mPrevPos = mPosition;

	//キャラクターが選ばれているものか判断
	if (CSceneModel::mCharcter == this){

		//スキル発動！！！
		if (CKey::push(KEY_SKILL)){
			if (CScoreBoard::skillgage >= mGageLimit && !CScoreBoard::mFlagSkill0){
				CScoreBoard::mFlagSkill0 = true;
				mSkillTime = mGageLimit;
			}
		}
	
		if (CScoreBoard::mFlagSkill0&&mSkillTime>0.0f){
			CScoreBoard::skillgage -= mGageDecrease;
			mSkillTime -= mGageDecrease;
		}
		else{
			CScoreBoard::mFlagSkill0 = false;
		}


		///*一回押したとき*/
		if (AttackInitKey.Onces(KEY_ATTACK)){//Kボタンか
			AnimaState(E_ATTACK_INIT); //初めのいっかいだけ呼び出す
		}
		/*長押しの時*/
		else if (CKey::push(KEY_ATTACK)){
			//スキルゲージ増加
			if (CScoreBoard::skillgage <= mGageLimit && !CScoreBoard::mFlagSkill0){
				CScoreBoard::skillgage += mGageDecrease;
			}
			AnimaState(E_ATTACK_IDLE);
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
	//mpCBBody->Update();
	//mpCBWeapon->Update();
	//mpCBLeg->Update();

	//状態によりアニメーション変化
	switch (mState)
	{
	case E_IDLE://立ち
		
		ChangeAnimation(E_IDLE, true, ANIMA_SPEED);
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
	case E_ATTACK_IDLE:
		ChangeAnimation(E_ATTACK_IDLE, true, ANIMA_SPEED_ATTCK);
		HammerUp();//Hammerの溜める処理
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
	AnimaState(E_ATTACK_IDLE);
	AnimaState(E_IDLE);
}

/*Hammerの溜める処理*/
void CXCharPlayer::HammerUp(){
	/*ハンマーのアニメ処理*/

	//デフォルトﾊﾝﾏ
	if (CItem::status == CItem::WEAPON0){
		mPower += POWER_UP;//ためていくと攻撃力が上がる
		if (mPower >= ATTACK_POWER_MAX){
			mPower = ATTACK_POWER_MAX;
			mHammerEffect.EnableAnima();//アニメーションを有効にする
		}
		else{
			mHammerEffect.SizeUp(POWER_UP);//サイズを大きくする
			mpCBWeapon->SizeUP(HAMMER_SIZE_UP);
		}
	}
	//武器1
	if (CItem::status == CItem::WEAPON1){
		mPower += W_0_POWER_UP;//ためていくと攻撃力が上がる
		if (!CScoreBoard::mFlagSkill0){//スキルが発動されていないとき
			if (mPower >= ATTACK_W0_POWER_MAX){
				mPower = ATTACK_W0_POWER_MAX;
				mHammerEffect.EnableAnima();//アニメーションを有効にする
			}
			else{
				mHammerEffect.SizeUp(POWER_UP);//サイズを大きくする
				mpCBWeapon->SizeUP(POWER_UP);
			}
		}
		else if (CScoreBoard::mFlagSkill0){//スキル発動時
			if (mPower >= ATTACK_WS0_POWER_MAX){
				mPower = ATTACK_WS0_POWER_MAX;
				mHammerEffect.EnableAnima();//アニメーションを有効にする
			}
			else{
				mHammerEffect.SizeUp(POWER_UP);//サイズを大きくする
				mpCBWeapon->SizeUP(POWER_UP);
			}
		}
	}
	//武器2
	if (CItem::status == CItem::WEAPON2){
		if (mPower >= ATTACK_W1_POWER_MAX){
			mPower = ATTACK_W1_POWER_MAX;
			mHammerEffect.EnableAnima();//アニメーションを有効にする
			if (!CScoreBoard::mFlagSkill0){
				mPower += W_1_POWER_UP;
			}//サイズを大きくする
			else if (CScoreBoard::mFlagSkill0){
				mPower += WS_1_POWER_UP;
			}
		}
		else{
			if (!CScoreBoard::mFlagSkill0){
				mHammerEffect.SizeUp(POWER_UP);
				mpCBWeapon->SizeUP(POWER_UP);
			}
			else if (CScoreBoard::mFlagSkill0){
				mHammerEffect.SizeUp(WS_1_POWER_UP);
				mpCBWeapon->SizeUP(POWER_UP);
			}
		}
	}

	//武器3
	if (CItem::status == CItem::WEAPON3){
		mPower += W_2_POWER_UP;
		if (mPower >= ATTACK_W2_POWER_MAX){
			mPower = ATTACK_W2_POWER_MAX;
			mHammerEffect.EnableAnima();//アニメーションを有効にする
		}
		else{
			mHammerEffect.SizeUp(W_2_POWER_UP);//サイズを大きくする
			mpCBWeapon->SizeUP(W_2_POWER_UP);
		}
	}
	//武器4
	mPower += W_3_POWER_UP;
	if (CItem::status == CItem::WEAPON4){
		if (mPower >= ATTACK_W3_POWER_MAX){
			mPower = ATTACK_W3_POWER_MAX;
			mHammerEffect.EnableAnima();//アニメーションを有効にする
		}
		else{
			mHammerEffect.SizeUp(W_3_POWER_UP);//サイズを大きくする
			mpCBWeapon->SizeUP(W_3_POWER_UP);
		}
	}

}

/*Hammerの初期化処理*/
void CXCharPlayer::HammerInit(){
	mHammerEffect.NoTexInit();
	mHammerEffect.DisableAnima();//アニメーションを無効にする
	mPower = ATTACK_POWER;//戻す
	/*武器の当たり判定*/
	mpCBWeapon->SetBoxOBB(OBB_WEAPON_POS, OBB_WEAPON_SIZE
		, &mpCombinedMatrix[mpModel->FindFrame("metarig_WeaponHandle")->mIndex]);
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
	mpColCapsule->Render();
	mpColCapsule3->Render();
#endif
}

/*エフェクトの描画処理*/
void CXCharPlayer::BillboardRender(){
	CVector3 pos = HAMMER_EFFECT_POS;
	pos = pos * mpCombinedMatrix[mpModel->FindFrame("metarig_WeaponHandle")->mIndex];//マトリックスから計算
	mHammerEffect.Update(pos);//ポジション計算
	mHammerEffect.Render();

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
	SearchGoPosInit();
}

/*当たり判定呼び出し
元の場所に戻すための関数
*/
bool CXCharPlayer::Collision(const COBB &box, const CColSphere &sphere) {
	return Collision(&box, &sphere);
}

bool CXCharPlayer::Collision(const COBB *box, const CColSphere *sphere) {

	CVector3 savePos = sphere->mPos;//計算用

	float lengthX = mPosition.x - savePos.x;  //球とポジションの距離
	float lengthY = mPosition.y - savePos.y;  //球とポジションの距離
	float lengthZ = mPosition.z - savePos.z;  //球とポジションの距離

	//BoxのX軸方向を求める
	CVector3 vx = box->mMatrixRotation * VEC_RIGHT;
	//BoxのY軸方向を求める
	CVector3 vy = box->mMatrixRotation * VEC_TOP;
	//BoxのZ軸方向を求める
	CVector3 vz = box->mMatrixRotation * VEC_FRONT;

	vx = box->mAxis[0];
	vy = box->mAxis[1];
	vz = box->mAxis[2];

	//四角形から球へのベクトルを求める
	CVector3 vectorBS = savePos - box->mPos;

	//四角形から球へ、四角形のX軸に対する長さとの差を求める
	float dx = sphere->mRadius + box->mLength[0] - fabs(vx.Dot(vectorBS));
	//四角形から球へ、四角形のY軸に対する長さとの差を求める
	float dy = sphere->mRadius + box->mLength[1] - fabs(vy.Dot(vectorBS));
	//四角形から球へ、四角形のZ軸に対する長さとの差を求める
	float dz = sphere->mRadius + box->mLength[2] - fabs(vz.Dot(vectorBS));

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
				if (sphere == &mpCBLeg->mColSphere){
					ColGround();//地面にあった時の処理
					//Y軸で戻す
					if (vy.Dot(vectorBS) > 0.0f) {
						mPosition = savePos + vy * dy;
					}
					else {
						mPosition = savePos - vy * dy;
					}
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
	else {
		return false;
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
	//mpCBBody->Update();
	//mpCBWeapon->Update();
	//mpCBLeg->Update();

	return true;
}


/*ジャンプ関数*/
void  CXCharPlayer::Jump(){
	Move(mForward, JUMP_MOVE(mVelocity));
	float jumpVilocity = JUMP_SPEED - GRAVITY(mGravitTime);//動かす力
	/*ジャンプが0より大きい場合*/
		mPosition.y += jumpVilocity;
	

}

/*坂にあった時の判定*/
void CXCharPlayer::ColSlope(){

	///*足(球)と坂(箱)が当たっている場合*/
	//if (CCollision::CollSphereBox(mpCBLeg->mColSphere,slope.mpColBox->mObb)){
	//	//mPosition = slope.MiddlePos(mPosition);
	//}
	mFlagSlpoe = true;
	ColGround();

}

bool CXCharPlayer::Collision(CCollider2* me, CCollider2* you) {

	switch (me->eColTag) {
	case E_COL_CAPSULE:
		if (you->eColTag == E_COL_TRIANGLE &&
			(you->eTag == E_TAG_GROUND ||
			you->eTag == E_TAG_SLOPE ||
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
		if (you->eTag == E_TAG_BOX ||
			you->eTag == E_TAG_GROUND) {
			if (you->eColTag == E_COL_BOX)
				return Collision((COBB*)&you->mObb, (CColSphere*)&me->mColSphere);
		}
	}

	return false;
}

bool CXCharPlayer::Collision(CTask* me, CTask* you) {
	CCollider3 *m = (CCollider3*)me;
	CCollider3 *y = (CCollider3*)you;

	switch (m->mType) {
	case CCollider3::COL_CAPSULE:
		CCollider3Capsule *cc = (CCollider3Capsule*)me;
		switch (y->mType) {
		case CCollider3::COL_TRIANGLE:
			CCollider3Triangle ct = *(CCollider3Triangle*)y;
			ct.Update();
			if (CCollision::IntersectTriangleCapsule3(ct.mV[0], ct.mV[1], ct.mV[2],
				cc->mV[0], cc->mV[1], cc->mRadius, &cc->mAdjust)) {
				/*
//				if (cross == CVector3())
//					return false;
				//				if (you->eTag == E_TAG_BOX)
				*/
				ColGround();//地面にあった時の処理
				mPosition = mPosition + cc->mAdjust;
			}
			break;
		}
		break;
	}

	return false;
}

#include <Windows.h>
#include "CSceneModel.h"
#include "../../../Task/CTaskManager.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
#include "../../../Collision/CCollisionManager.h"
#include "../Map/CMap.h"
#include "../../../Collision/CCollision2D.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "CXCharEnemy.h"
#include "../CGameScene.h"
#include "../Map/Goal/CXGoal.h"
#include "../Puck/CXPuck.h"


#define Char_HP_SIZE 600.0f,600.0f,0.8f,0.1f //キャラのHP
/*キャラクターのポジション*/
#define PLAYER_POS i*2,0.0f,0.0f//プレイヤーのポジション
#define ENEMY_POS i*3.0f,0.0f,10.0f//エネミーのポジション
/*カメラの位置*/
#define CAMERA_OFFSET 0.0f, 0.5f, 4.0f //カメラ位置プレイヤーからの相対位置
#define CAMERA_POS CVector3(mCharcter->mPosition.x,mCharcter->mPosition.y+2.3f,mCharcter->mPosition.z)
/*角度*/
#define ANGLE_360 360
#define ANGLE_90  90
#define ANGLE_50  50
#define ANGLE_5   5.0f
#define ANGLE_180 180.0f
/*サイズ*/
#define COL_INIT_MOUSE_SIZE -DISP_X/2, DISP_Y/2, DISP_X/2, -DISP_Y/2
/*カメラ*/
#define ANGLE_SPEED 3.0f//カメラスピード
#define CAMERA_IF_DIVIDE  50//カメラスピード調整用
#define CAMERA_DIVIDE  10//カメラスピード調整用
#define ARRIVAL_TIME 0.1f//待ち時間

/*モデルのファイル場所*/
#define MODEL_FILE_UNITY			"x\\SDUnity\\SDUniEriHammer.x"
//#define MODEL_FILE_SD_ELIZABETH		"x\\ElizabethWarren\\ElizabethSDWeapon.x"
#define MODEL_FILE_ELIZABETH		"x\\ElizabethWarren\\ElizabethSD.x"
#define MODEL_FILE_PUCK				"x\\Puck\\Puck.x"
#define MODEL_FILE_GOAL				"x\\Goal\\goal.x"
/*アニメーションのファイル場所*/
#define ANIMA_FILE_IDLE				"x\\Anima\\Ani_Idle2.x"
#define ANIMA_FILE_ATTACK_RUN		"x\\Anima\\Ani_AttackRun.x"
#define ANIMA_FILE_RUN				"x\\Anima\\Ani_Run.x"
#define ANIMA_FILE_ATTACK_IDLE		"x\\Anima\\Ani_AttackIdle.x"
#define ANIMA_FILE_ATTACK_INIT		"x\\Anima\\Ani_AttackInit.x"
#define ANIMA_FILE_ATTACK			"x\\Anima\\Ani_Attack.x"
#define ANIMA_FILE_ATTACK_JUMP		"x\\Anima\\Ani_AttackJump.x"
#define ANIMA_FILE_JUMP				"x\\Anima\\Ani_Jump.x"
/*lag回避用*/
#define LAG_SIZE 0.1f //0，1秒間lag回避用
/*パックの初期位置*/
#define PUCK_INIT_POS 0.0f,0.0f,-10.0f
/*静的初期化*/
CXCharPlayer *CSceneModel::mCharcter;
CVector3 CSceneModel::mRotation;
CXPuck *CSceneModel::mpPuck;
CXGoal *CSceneModel::mpGoalPlayer;

/*コンストラクタ*/
CSceneModel::CSceneModel() :mMouseInitCount(0.0f),mLagTime(0.0f){
//	mCharcter = new CXCharPlayer();

}

/*デストラクタ*/
CSceneModel::~CSceneModel(){
	//P_DELETE(mCharcter);

}
/*プレイヤー追加処理*/
void CSceneModel::CPlayerAdd(CVector3 PlayerPos, CModelX *model){
	CXCharPlayer *pl = new CXCharPlayer(); //new作成

	pl->Init(model);
	pl->mPosition = PlayerPos;//ポジション決める

	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PLAYER, pl->mpCBLeg);//あたり判定追加
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PLAYER, pl->mpCBBody);//あたり判定追加
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_WEAPON, pl->mpCBWeapon);//あたり判定追加
	mModelTaskManager.Add(pl);//タスクに追加
	mCharcter = pl; //操作用
}

/*エネミー追加処理*/
void CSceneModel::CEnemyAdd(CVector3 EnemyPos, CModelX *model){

	CXCharEnemy *ene = new CXCharEnemy();//作成

	ene->Init(model);
	ene->mPosition = EnemyPos;
	/*当たり判定追加処理*/
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ENEMY, ene->mpCBLeg);//あたり判定追加
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ENEMY, ene->mpCBBody);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_WEAPON,ene->mpCBWeapon);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ATTACK_INIT_RANGE, ene->mpCBAttackInitBox);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ATTACK_RANGE, ene->mpCBAttackBox);
	mModelTaskManager.Add(ene);
}
/*パック追加処理*/
void CSceneModel::CPuckAdd(CVector3 PuckPos, CModelX *model){
	
	CXPuck *puck = new CXPuck();//作成
	puck->Init(model);
	puck->mPosition = PuckPos;
	/*当たり判定追加*/
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PUCK, puck->mpCBSphere);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_PUCK, puck->mpCBRefBox);
	mModelTaskManager.Add(puck);
	mpPuck = puck;//アクセス用に入れる
}
/*ゴールプレイヤー追加処理*/
void CSceneModel::CGoalPlayerAdd(CVector3 GoalPos, CModelX *model){
	CXGoal *goal = new CXGoal();//作成
	goal->Init(model,GoalPos);
	/*プレイヤーの場合こっちに向ける*/
	goal->mRotation.y -= ANGLE_180;
	/*レンダー順番決める*/
	goal->ePriority = CTask::E_GOAL_PLAYER;
	/*当たり判定追加処理*/
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_GOAL_PLAYER, goal->mCBBox);
	mModelTaskManager.Add(goal);
	mpGoalPlayer = goal;
}

/*ゴールエネミー追加処理*/
void CSceneModel::CGoalEnemyAdd(CVector3 GoalPos, CModelX *model){
	CXGoal *goal = new CXGoal();//作成
	goal->Init(model, GoalPos);
	/*レンダー順番決める*/
	goal->ePriority = CTask::E_GOAL_PLAYER;
	/*当たり判定追加処理*/
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_GOAL_ENEMY, goal->mCBBox);
	mModelTaskManager.Add(goal);
}

void CSceneModel::Init() {
	mMouseInitCount = 0.0f;							//マウスが初期位置に戻るまでの時間
	mLagTime = 0.0f;								//lagによるバグ回避時間
	mCharcter = 0;									//アクセス用 キャラクター操作に使うため 静的に
	mRotation = CVector3(0.0f, 0.0f, 0.0f);		//キャラクター操作に使うため 静的に

	CVector3 mPosition;								//位置　

	//mSaveMousePos = CVector2(0.0f, 0.0f);			//マウスのポジション
	//mColInitMouse.position = CVector2(0.0f, 0.0f);//マウスの初期位置


	/*プレイヤー*/
	mModel.Load(MODEL_FILE_UNITY);
	/*アニメーション追加処理*/
	for (int i = 0; i < CTask::E_STATE_ARRAY; i++)
	{
		switch (i)
		{
		case CTask::E_IDLE:
			mModel.AddAnimationSet(ANIMA_FILE_IDLE);//待機追加_0 
			break;
		case CTask::E_ATTACK_RUN:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_RUN);//ためながら走る追加
			break;
		case CTask::E_RUN:
			mModel.AddAnimationSet(ANIMA_FILE_RUN);//走る追加
			break;
		case CTask::E_ATTACK_IDLE:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_IDLE);//攻撃ためアイドル追加
			break;
		case CTask::E_ATTACK_INIT:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_INIT);//攻撃ためアイドル追加
			break;
		case CTask::E_ATTACK:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK);//攻撃追加_2 
			break;
		case CTask::E_JUMP:
			mModel.AddAnimationSet(ANIMA_FILE_JUMP);//ジャンプ追加
			break;
		case CTask::E_ATTACK_JUMP:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_JUMP);//攻撃中ジャンプ追加 
			break;
		case CTask::E_DMGM:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_JUMP);//ジャンプ追加 
			break;
		}
	}

	CPlayerAdd(CMap::PlayerFirstPos(), &mModel);
	/*エネミー*/
	mModelE.Load(MODEL_FILE_ELIZABETH);

	/*アニメーション追加処理*/
	for (int i = 0; i < CTask::E_STATE_ARRAY; i++)
	{
		switch (i)
		{
		case CTask::E_IDLE:

			mModelE.AddAnimationSet(ANIMA_FILE_IDLE);//待機追加_0 
			break;
		case CTask::E_ATTACK_RUN:
			mModelE.AddAnimationSet(ANIMA_FILE_ATTACK_RUN);//ためながら走る追加
			break;
		case CTask::E_RUN:
			mModelE.AddAnimationSet(ANIMA_FILE_RUN);//走る追加
			break;
		case CTask::E_ATTACK_IDLE:
			mModelE.AddAnimationSet(ANIMA_FILE_ATTACK_IDLE);//攻撃ためアイドル追加
			break;
		case CTask::E_ATTACK_INIT:
			mModelE.AddAnimationSet(ANIMA_FILE_ATTACK_INIT);//攻撃ためアイドル追加
			break;
		case CTask::E_ATTACK:
			mModelE.AddAnimationSet(ANIMA_FILE_ATTACK);//攻撃追加_2 
			break;
		case CTask::E_JUMP:
			mModelE.AddAnimationSet(ANIMA_FILE_JUMP);//ジャンプ追加
			break;
		case CTask::E_ATTACK_JUMP:
			mModelE.AddAnimationSet(ANIMA_FILE_ATTACK_JUMP);//攻撃中ジャンプ追加 
			break;
		case CTask::E_DMGM:
			mModelE.AddAnimationSet(ANIMA_FILE_ATTACK_JUMP);//ジャンプ追加 
			break;
		}
	}

	CEnemyAdd(CMap::EnemyFirstPos(), &mModelE);
	/*パック*/
	mModelPuck.Load(MODEL_FILE_PUCK);						//ロード
	//mModelPuck.Load(MODEL_FILE_GOAL);						//ロード
	mModelPuck.AddAnimationSet(ANIMA_FILE_IDLE);			//から入れ
	CPuckAdd(CVector3(PUCK_INIT_POS), &mModelPuck);				//パック追加処理
	/*ゴールプレイヤー*/
	mModelGoal.Load(MODEL_FILE_GOAL);						//ロード
	mModelGoal.AddAnimationSet(ANIMA_FILE_IDLE);			//から入れ
	CGoalPlayerAdd(CMap::GoalPlayerFirstPos(), &mModelGoal);			//パック追加処理
	/*ゴールエネミー*/
	mModelEGoal.Load(MODEL_FILE_GOAL);						//ロード
	mModelEGoal.AddAnimationSet(ANIMA_FILE_IDLE);			//から入れ
	CGoalEnemyAdd(CMap::GoalEnemyFirstPos(), &mModelEGoal);	//パック追加処理

	///*マウスのサイズ*/
	//mColInitMouse.SetVertex(COL_INIT_MOUSE_SIZE);
	//mColInitMouse.SetColor(WHITE_COLOR);
}

void CSceneModel::Update() {
	if (CGameScene::Transition == CGameScene::E_ACTIVE){

		/*lag回避*/
		if (!CConvenient::Time(&mLagTime, LAG_SIZE)){
			CMouse::mLeftFlag = false;
		}


		/*カメラ設定*/
		if (CKey::push(VK_LEFT)) {//左
			mRotation.y += ANGLE_SPEED;
		}
		if (CKey::push(VK_RIGHT)) {//右
			mRotation.y -= ANGLE_SPEED;
		}
		if (CKey::push(VK_DOWN) && mRotation.x < ANGLE_90) {//下
			mRotation.x += ANGLE_SPEED;
		}
		if (CKey::push(VK_UP) && mRotation.x > -ANGLE_90) {//上
			mRotation.x -= ANGLE_SPEED;
		}
		/*ローテーションがマイナスの場合*/
		if (mRotation.y < 0){
			mRotation.y = ANGLE_360 + mRotation.y;
		}

		///*カメラ設定マウス*/
		//if (CMouse::mPos.x != mSaveMousePos.x && mSaveMousePos.x  > CMouse::mPos.x){//左
		//	mRotation.y += (mSaveMousePos.x - CMouse::mPos.x) / CAMERA_DIVIDE;

		//	CMouse::SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//カーソルをウィンドウの中心にする

		//}
		//if (CMouse::mPos.x != mSaveMousePos.x && mSaveMousePos.x < CMouse::mPos.x){//右
		//	mRotation.y += (mSaveMousePos.x - CMouse::mPos.x) / CAMERA_DIVIDE;

		//	CMouse::SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//カーソルをウィンドウの中心にする
		//}
		//if (CMouse::mPos.y != mSaveMousePos.y && mSaveMousePos.y> CMouse::mPos.y && mRotation.x < ANGLE_50){//下
		//	mRotation.x += (mSaveMousePos.y - CMouse::mPos.y) / CAMERA_DIVIDE;


		//	CMouse::SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//カーソルをウィンドウの中心にする
		//}
		//if (CMouse::mPos.y != mSaveMousePos.y && mSaveMousePos.y   < CMouse::mPos.y && mRotation.x > -ANGLE_50){//上
		//	mRotation.x += (mSaveMousePos.y - CMouse::mPos.y) / CAMERA_DIVIDE;


			CMouse::SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//カーソルをウィンドウの中心にする
		//}
		///*中心からそれると真ん中に戻す処理*/
		//if (CCollision2D::Collision2D(mColInitMouse, CMouse::mRect)){
		//	/*時間が経つと真ん中に戻る*/
		//	if (CConvenient::Time(&mMouseInitCount, ARRIVAL_TIME) &&
		//		mSaveMousePos.x == CMouse::mPos.x &&
		//		mSaveMousePos.y == CMouse::mPos.y){ //0.1秒間動かなければ
		//		CMouse::SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//カーソルをウィンドウの中心にする
		//		mMouseInitCount = 0;//0に戻す

		//	}
		//}
		//else
		//{
		//	CMouse::SetMousePos(WinPosX + DISP_X / 2, WinPosY + DISP_Y / 2);//カーソルをウィンドウの中心にする
		//}

		//mSaveMousePos = CMouse::mPos;//セーブする

		mModelTaskManager.AllUpdate();




	}
	
}

void CSceneModel::Render() {
	mRotation.y =abs(mRotation.y);

	//printf("%f\n", mRotation.y);
	int mRotPercent = mRotation.y;
	//カメラ位置プレイヤーからの相対位置
	CVector3 cp(CAMERA_OFFSET);
	//カメラの回転行列
	CMatrix44 mat;
	//キャラクターの位置からカメラ位置を計算
	CVector3 SavePos = CAMERA_POS;

	/*３人称*/
	cp.z *= -1;
	mRotPercent %= ANGLE_360;
	CVector3 rot = mRotation;
	mRotation.y = mRotPercent;//３６０にする
	rot.y = mRotPercent;
	mat.rotationX(rot.x);
	mat.rotationY(rot.y);

	//カメラを回転させる
	cp = cp * mat;
	cp += SavePos;
	//カメラの視点(eye)と注意点(pos)を設定

	MainCamera.pos[0] = SavePos.x;
	MainCamera.pos[1] = SavePos.y;
	MainCamera.pos[2] = SavePos.z;
	MainCamera.eye[0] = cp.x;
	MainCamera.eye[1] = cp.y;
	MainCamera.eye[2] = cp.z;


	mModelTaskManager.AllRender();

}

void CSceneModel::UpdateEffect(){
	mModelTaskManager.AllBillboardRender();
}
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


#define Char_HP_SIZE 600.0f,600.0f,0.8f,0.1f //キャラのHP
/*キャラクターのポジション*/
#define PLAYER_POS i*2,0.0f,0.0f//プレイヤーのポジション
#define ENEMY_POS  i*3.0f,0.0f,10.0f//エネミーのポジション

/*角度*/
#define ANGLE_360 360
#define ANGLE_90  90
#define ANGLE_50  50
#define ANGLE_5   5.0f
#define ANGLE_180 180.0f
/*サイズ*/
#define COL_INIT_MOUSE_SIZE -DISP_X/2, DISP_Y/2, DISP_X/2, -DISP_Y/2

/*モデルのファイル場所*/
#define MODEL_FILE_UNITY			"x\\SDUnity\\SDUnityBoxing.x"
/*アニメーションのファイル場所*/
#define ANIMA_FILE_IDLING			"x\\Anima\\Idling.x"
#define ANIMA_FILE_ATTACK_RUN		"x\\Anima\\Run.x"
#define ANIMA_FILE_RUN				"x\\Anima\\Run.x"
#define ANIMA_FILE_ATTACK_IDLING	"x\\Anima\\Ani_AttackIdle.x"
#define ANIMA_FILE_ATTACK_INIT		"x\\Anima\\Ani_AttackInit.x"
#define ANIMA_FILE_ATTACK			"x\\Anima\\Attack2.x"
#define ANIMA_FILE_ATTACK_JUMP		"x\\Anima\\Ani_AttackJump.x"
#define ANIMA_FILE_JUMP				"x\\Anima\\Ani_Jump.x"
#define ANIMA_FILE_DAMAGE			"x\\Anima\\Ani_Damage.x"

/*lag回避用*/
#define LAG_SIZE 0.1f //0，1秒間lag回避用
/*パックの初期位置*/
#define PUCK_INIT_POS 0.0f,0.0f,-10.0f


/*静的初期化*/
CXCharPlayer *CSceneModel::mpPlayer;

/*すべてのモデルキャラ削除*/
void CSceneModel::ModelAllKill(){
	mModelTaskManager.AllKill();
}

/*コンストラクタ*/
CSceneModel::CSceneModel() :mMouseInitCount(0.0f),mLagTime(0.0f){


}

/*デストラクタ*/
CSceneModel::~CSceneModel(){
	

}

/*プレイヤー追加処理*/
void CSceneModel::CPlayerAdd(CVector3 PlayerPos, CModelX *model){
	CXCharPlayer *pl = new CXCharPlayer(); //new作成

	pl->Init(model);
	pl->mPosition = PlayerPos;//ポジション決める
	mModelTaskManager.Add(pl);//タスクに追加
	mpPlayer = pl; //操作用
}

/*エネミー追加処理*/
void CSceneModel::CEnemyAdd(CVector3 EnemyPos, CModelX *model){

	CXCharEnemy *ene = new CXCharEnemy();//作成

	ene->Init(model);
	ene->mPosition = EnemyPos;
	/*当たり判定追加処理*/
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ATTACK_INIT_RANGE, ene->mpCBAttackInitBox);
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_ATTACK_RANGE, ene->mpCBAttackBox);
	mModelTaskManager.Add(ene);
}

void CSceneModel::Init() {

	mMouseInitCount = 0.0f;							//マウスが初期位置に戻るまでの時間
	mLagTime = 0.0f;								//lagによるバグ回避時間

	CVector3 mPosition;								//位置　

	/*プレイヤー*/
	mModel.Load(MODEL_FILE_UNITY);

	/*アニメーション追加処理*/
	for (int i = 0; i < CTask::E_STATE_ARRAY; i++)
	{
		switch (i)
		{
		case CTask::E_IDLING:
			mModel.AddAnimationSet(ANIMA_FILE_IDLING);//待機追加_0 
			break;
		case CTask::E_ATTACK_RUN:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_RUN);//ためながら走る追加
			break;
		case CTask::E_RUN:
			mModel.AddAnimationSet(ANIMA_FILE_RUN);//走る追加
			break;
		case CTask::E_ATTACK_IDLING:
			mModel.AddAnimationSet(ANIMA_FILE_ATTACK_IDLING);//攻撃ためアイドル追加
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
			mModel.AddAnimationSet(ANIMA_FILE_DAMAGE);//ダメージ
			break;
		}
	}
	/*キャラクター初期化*/
	CPlayerAdd(CVector3(0.0f, 0.0f, 0.0f), &mModel);

}

void CSceneModel::Update() {
	
		/*lag回避*/
		if (!CConvenient::Time(&mLagTime, LAG_SIZE)){
			CMouse::GetInstance()->mLeftFlag = false;
		}

		
		mModelTaskManager.AllUpdate();




	
}

void CSceneModel::Render() {
	
	mModelTaskManager.AllRender();

}

void CSceneModel::UpdateEffect(){
	mModelTaskManager.AllBillboardRender();
}
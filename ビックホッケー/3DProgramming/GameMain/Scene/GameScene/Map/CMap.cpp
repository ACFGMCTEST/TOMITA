#include "CMap.h"
#include "../../../Collision/CCollisionManager.h"
#include "../../../Graphic/CModelX.h"
#include "../../../../Light/CLight.h"
#include "../../QuestScene/CQuest.h"
#include "Goal\CGoal.h"

/*マップチップ設定インクルード
ゴールはモデルでするのでmodelファイルのところで処理
*/
#include "Net\CNet.h"
#include "FastFloor\CFastFloor.h"
#include "SlowFloor\CSlowFloor.h"
#include "Trampoline\CTrampoline.h"
#include "HighBox\CHighBox.h"
#include "Slope\CSlope.h"
#include "SlopeEnd\CSlopeEnd.h "
/*地面サイズ*/
#define GROUND_SIZE new float[]{MAPCHIP_SIZE*CMap::mMapX, MAPCHIP_SIZE*2, MAPCHIP_SIZE * CMap::mMapZ} 


/*大きさ*/
#define TRAMPOLINE_SIZE -MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f, MAPCHIP_SIZE*0.5f, -MAPCHIP_SIZE, MAPCHIP_SIZE
#define FAST_FLOOR_SIZE -MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f, MAPCHIP_SIZE, -MAPCHIP_SIZE, MAPCHIP_SIZE
#define SLOW_FLOOR_SIZE -MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f, MAPCHIP_SIZE, -MAPCHIP_SIZE, MAPCHIP_SIZE
#define NET_SIZE		-MAPCHIP_SIZE*CMap::mMapX, MAPCHIP_SIZE*CMap::mMapX,\
						- MAPCHIP_SIZE, MAPCHIP_SIZE*2, \
						- MAPCHIP_SIZE*0.2f, MAPCHIP_SIZE*0.2f
/*壁の大きさ*/
#define WALL_SIZE_FRONT (MAPCHIP_SIZE*CMap::mMapZ)
#define WALL_SIZE_BACK  (MAPCHIP_SIZE*CMap::mMapZ)
#define WALL_SIZE_LEFT  (MAPCHIP_SIZE*CMap::mMapX)
#define WALL_SIZE_RIGHT (MAPCHIP_SIZE*CMap::mMapX)
#define WALL_SIZE_TOP abs(WALL_SIZE_RIGHT)
#define WALL_SIZE_BOTTOM -1.0f

/*あたり判定:ボックス設定*/
#define OBB_BOX_POS CVector3(0.0f,0.0f,0.0f) 
#define OBB_BOX_SIZE new float[]{MAPCHIP_SIZE, MAPCHIP_SIZE, MAPCHIP_SIZE} 
#define OBB_BOX_GOAL_SIZE new float[]{MAPCHIP_SIZE, MAPCHIP_SIZE, MAPCHIP_SIZE} 
/*網設定*/
#define OBB_NET_POS CVector3(0.0f,0.0f,0.0f) 
#define OBB_NET_SIZE new float[]{MAPCHIP_SIZE*CMap::mMapX*1.2f, MAPCHIP_SIZE*4, MAPCHIP_SIZE*0.5f} 
/*あたり判定:壁の設定*/
/*サイズ*/
#define OBB_WALL_RIGHT_SIZE new float[]{MAPCHIP_SIZE, MAPCHIP_SIZE*10, MAPCHIP_SIZE*CMap::mMapZ*1.2f} 
#define OBB_WALL_LEFT_SIZE	new float[]{MAPCHIP_SIZE, MAPCHIP_SIZE*10, MAPCHIP_SIZE*CMap::mMapZ*1.2f} 
#define OBB_WALL_UP_SIZE	new float[]{MAPCHIP_SIZE*CMap::mMapX*1.2f, MAPCHIP_SIZE*10, MAPCHIP_SIZE} 
#define OBB_WALL_DOWN_SIZE	new float[]{MAPCHIP_SIZE*CMap::mMapX*1.2f, MAPCHIP_SIZE*10, MAPCHIP_SIZE} 
/*向き*/
#define OBB_WALL_RIGHT_DIRECTION -1.0f,0.0f,0.0f
#define OBB_WALL_LEFT_DIRECTION 1.0f,0.0f,0.0f
#define OBB_WALL_UP_DIRECTION 0.0f,0.0f,-1.0f
#define OBB_WALL_DOWN_DIRECTION 0.0f,0.0f,1.0f


#define NET_POS_Z(z) 0		//網のポジション　
#define NET_POS_Y 6		//網のポジション　
#define NET_POS_X(x) 0		//網のポジション　
/*VBOレンダー*/
//領域解放をマクロ化
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
#define SAFE_DELETE(a) { if(a) delete a; a = 0;}
//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

/*スクロール速さ*/
#define SCROLL_SPEED 1.0f

/*静的初期化*/
CCollider *CMap::mpGoalPlayer = 0;
CCollider *CMap::mpGoalEnemy = 0;
int CMap::mGoalCount = 0;//ゴールのカウント
int CMap::mMapX = 0;
int CMap::mMapZ = 0;
CCsv CMap::mCsvMapData;


/*ポジションから配列会得*/
int CMap::ArrayX(float x){ //マップ配列を返す
	return round(x) / (MAPCHIP_SIZE * 2) + CMap::mMapX / 2;
}
/*ポジションから配列会得*/
int CMap::ArrayZ(float z){ //マップ配列を返す
	return round(z) / (MAPCHIP_SIZE * 2) + CMap::mMapZ / 2;
}






CVector3 CMap::PlayerFirstPos(){

	for (int z = 0; z < CMap::mMapZ; z++){
		for (int x = 0; x < CMap::mMapX; x++){
			if (mCsvMapData.mpData[(z*mMapX) + x] == CMap::E_PLAYER_4)
			return CVector3(POS_X(x), 0.0f, POS_Z(z));
		}
	}

}

CVector3 CMap::EnemyFirstPos(){
	for (int z = 0; z < CMap::mMapZ; z++){
		for (int x = 0; x < CMap::mMapX; x++){
			if (mCsvMapData.mpData[(z*mMapX) + x] == CMap::E_AI_5)
				return CVector3(POS_X(x), 0.0f, POS_Z(z));
		}
	}
}
/*ゴールプレイヤー*/
CVector3 CMap::GoalPlayerFirstPos(){
	for (int z = 0; z < CMap::mMapZ; z++){
		for (int x = 0; x < CMap::mMapX; x++){
			if (mCsvMapData.mpData[(z*mMapX) + x] == CMap::E_GOAL_PLAYER_6)
				return CVector3(POS_X(x), 0.0f, POS_Z(z));
		}
	}
}
/*ゴールエネミー*/
CVector3 CMap::GoalEnemyFirstPos(){
	for (int z = 0; z < CMap::mMapZ; z++){
		for (int x = 0; x < CMap::mMapX; x++){
			if (mCsvMapData.mpData[(z*mMapX) + x] == CMap::E_GOAL_ENEMY_7)
				return CVector3(POS_X(x), 0.0f, POS_Z(z));
		}
	}
}


void CMap::Init(){
	
	/*状態によりマップ変化*/
	switch (CQuest::eChoice)
	{
	case CQuest::E_QUEST00:
		/*マップデータロード*/
		mCsvMapData.Load(CSV_FILE_MAP0);
		break;
	case CQuest::E_QUEST01:
		/*マップデータロード*/
		mCsvMapData.Load(CSV_FILE_MAP1);
		break;
	case CQuest::E_QUEST02:
		/*マップデータロード*/
		mCsvMapData.Load(CSV_FILE_MAP2);
		break;
	case CQuest::E_QUEST03:
		/*マップデータロード*/
		mCsvMapData.Load(CSV_FILE_MAP3);
		break;
	};
	/*静的な格納*/
	CMap::mMapX = mCsvMapData.mRow;
	CMap::mMapZ = mCsvMapData.mLine;

	/*デバック用*/
#ifdef _DEBUG 
	printf("マップデータ確認\n");
	mCsvMapData.DataPrintf();
#endif

	/*ここで初期化*/
	MapInit(mCsvMapData);


}

/*マップ初期配置関数*/
void CMap::MapInit(CCsv &csv){

	/*タイル用意*/
	CTile *tile;
	/*高台用意*/
	CHighBox *highBox;
	/*加速床用意*/
	CFastFloor *fastFloor;
	/*減速床用意*/
	CSlowFloor *slowFloor;
	/*トランポリン用意*/
	CTrampoline *trampoline;
	/*坂用意*/
	CSlope *slope;
	/*坂の端用意*/
	CSlopeEnd *slopeEnd;
	/*ゴール用意*/
	CGoal *goal;

	for (int z = 0; z < CMap::mMapZ; z++){
		for (int x = 0; x < CMap::mMapX; x++){
			/*タイルを張る*/
			tile = new CTile(ARRAY_POS(x, 0, z), mTexTile);
			mMapTaskManager.Add(tile);//追加

			/*現在の状態から追加する要素を決める*/
			switch (mCsvMapData.mpData[(z*mMapX) + x])
			{
				/*トランポリン設定*/
			case CMap::E_Trampoline_1:
				trampoline = new CTrampoline(ARRAY_POS(x,0,z));
				mMapTaskManager.Add(trampoline);
				break;
				/*高速床*/
			case CMap::E_FAST_FLOOR_2:
				fastFloor = new CFastFloor(ARRAY_POS(x,0,z));
				mMapTaskManager.Add(fastFloor);
				break;
				/*減速床設定*/
			case CMap::E_SLOW_FLOOR_3:
				slowFloor = new CSlowFloor(ARRAY_POS(x, 0, z));
				mMapTaskManager.Add(slowFloor);
				break;
				/*プレイヤーゴール設定*/
			case CMap::E_GOAL_PLAYER_6:
				goal = new CGoal(ARRAY_POS(x, 0, z), CTask::E_TAG::E_TAG_GOAL_PLAYER);
				mMapTaskManager.Add(goal);
								break;
				/*エネミーゴール設定*/
			case CMap::E_GOAL_ENEMY_7:
				goal = new CGoal(ARRAY_POS(x, 0, z), CTask::E_TAG::E_TAG_GOAL_ENEMY);
				mMapTaskManager.Add(goal);
								break;
				/*坂の設定*/
			case CMap::E_SLOP_8:
				slope = new CSlope(ARRAY_POS(x, 0, z), x, z);
				mMapTaskManager.Add(slope);

				break;
			case CMap::E_SLOP_END_9:
				
				slopeEnd = new CSlopeEnd(ARRAY_POS(x, 0, z), x, z);
				mMapTaskManager.Add(slopeEnd);
				break;
				/*高い高台*/
			case CMap::E_HIGH_BOX_A:
				highBox = new CHighBox(ARRAY_POS(x, 0, z));
				mMapTaskManager.Add(highBox);
				break;
			};
			
		}
	}


	/*網用意*/
	CNet *net;
	net = new CNet(CVector4(NET_POS_X(x), NET_POS_Y, NET_POS_Z(z)));
	mMapTaskManager.Add(net);


	/*壁の設定*/
	mWallBox.SetVertex(WALL_SIZE_LEFT, -WALL_SIZE_RIGHT,WALL_SIZE_TOP, WALL_SIZE_BOTTOM,WALL_SIZE_FRONT, -WALL_SIZE_BACK);
	/*テクスチャの設定*/
	mWallBox.SetTex(CBox::E_WALL);
	mWallBox.SetColor(WHITE_COLOR);

	mWallBox.UpdateMatrix();
	ColInit();
}

/*座標に指定された属性を返す*/
CMap::E_MAP CMap::MapState(int x, int z){
	return (E_MAP)(mCsvMapData.mpData[z * CMap::mMapX + x]);
}

/*座標値が現在のマップから這い出していないか判断*/
bool CMap::FlagMapLimit(int x, int z){
	if (0 <= x && x <= mMapX){
		if (0 <= z && z <= mMapZ){
			return true;
		}
	}
	return false;
}

/*座標に指定したものがあった場合 trueを返す*/
bool CMap::FlagMapMacth(int x, int z, E_MAP state){
	if (FlagMapLimit(x, z)){//はみ出さない
		if (mCsvMapData.mpData[z * CMap::mMapX + x] == state){//一致しているか?
			return true;
		}
	}
	return false;
}
/*あたり判定の初期化*/
void CMap::ColInit(){
	for (int i = 0; i < E_WALL_ARRAY; i++)
	{
		mpColPlane[i] = new CCollider(CTask::E_COL_BOX);
	}

	CVector3 left, right, up, down;
	/*ポジション設定*/
	left = CVector3(mWallBox.mSizeX1 +MAPCHIP_SIZE/2,0.0f,0.0f);
	right = CVector3(mWallBox.mSizeX2 - MAPCHIP_SIZE / 2, 0.0f, 0.0f);
	up = CVector3(0, 0.0f, mWallBox.mSizeZ1 + MAPCHIP_SIZE );
	down = CVector3(0, 0.0f, mWallBox.mSizeZ2 - MAPCHIP_SIZE);


#define NORMAL(vec) mObb.mNormal = CVector3(vec); //法線の向き
	/*地面設定*/
	mpColPlane[E_GROUND]->SetBoxOBB(CVector3(0.0f, -MAPCHIP_SIZE*2, 0.0f), GROUND_SIZE, &mWallBox.mRect[CBox::E_y1].mMatrix);
	mpColPlane[E_GROUND]->NORMAL(VEC_TOP);//法線を左に(パックの跳ね返り方向)
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_GROUND, mpColPlane[E_GROUND]);

	/*右の壁設定*/
	mpColPlane[E_WALL_RIGHT]->SetBoxOBB(right, OBB_WALL_RIGHT_SIZE, &mWallBox.mRect[CBox::E_x2].mMatrix);
	mpColPlane[E_WALL_RIGHT]->NORMAL(VEC_LEFT);//法線を左に(パックの跳ね返り方向)
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_WALL, mpColPlane[E_WALL_RIGHT]);
	/*左の壁設定*/
	mpColPlane[E_WALL_LEFT]->SetBoxOBB(left, OBB_WALL_LEFT_SIZE, &mWallBox.mRect[CBox::E_x1].mMatrix);
	mpColPlane[E_WALL_LEFT]->NORMAL(VEC_RIGHT);//法線を右に(パックの跳ね返り方向)
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_WALL, mpColPlane[E_WALL_LEFT]);
	/*上の壁設定*/
	mpColPlane[E_WALL_UP]->SetBoxOBB(up, OBB_WALL_UP_SIZE, &mWallBox.mRect[CBox::E_z2].mMatrix);
	mpColPlane[E_WALL_UP]->NORMAL(VEC_BACK);//法線を後方に(パックの跳ね返り方向)
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_WALL, mpColPlane[E_WALL_UP]);
	/*下の壁設定*/
	mpColPlane[E_WALL_DOWN]->SetBoxOBB(down, OBB_WALL_DOWN_SIZE, &mWallBox.mRect[CBox::E_z1].mMatrix);
	mpColPlane[E_WALL_DOWN]->NORMAL(VEC_FRONT);//法線を前方に(パックの跳ね返り方向)
	CCollisionManager::GetInstance()->Add(CTask::E_TAG_WALL, mpColPlane[E_WALL_DOWN]);

}

CMap::CMap() : mArrayCount(0){
	/*テクスチャロード*/
	mTexTile.load(TGA_FILE"BG.tga");
}

CMap::~CMap(){

}


void CMap::Update(){
	for (int i = 0; i < CMap::E_WALL_ARRAY; i++)
	{
		mpColPlane[i]->Update();
	}
	mMapTaskManager.AllUpdate();
}

void CMap::Render(){

	mWallBox.Render2();
	mMapTaskManager.AllRender();
}

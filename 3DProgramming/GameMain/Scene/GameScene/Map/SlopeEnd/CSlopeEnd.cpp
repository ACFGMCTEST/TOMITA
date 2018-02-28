#include "CSlopeEnd.h"

#include "../../../../Collision/CCollisionManager.h"
#include "../CMap.h"
/*あたり判定:ボックス設定*/
#define OBB_POS CVector3(0.0f,0.0f,0.0f) 
#define OBB_SIZE new float[]{MAPCHIP_SIZE, MAPCHIP_SIZE/2, MAPCHIP_SIZE} 
#define SMALL_SIZE(num) num*0.999f//ボックスとかぶらない用
#define SET_OBB OBB_POS,OBB_SIZE,&mMatrix

/*当たり判定 跳ね返りよう*/
#define REF_SIZE_X mMaxX * 0.05f			//当たり判定のX
#define REF_SIZE_Y mMaxY 				//当たり判定のY
#define REF_SIZE_Z mMaxZ 				//当たり判定のZ
#define OBB_LEFT_POS CVector3(-MAPCHIP_SIZE - REF_SIZE_X ,0.0f,0.0f) //ポジション右
#define OBB_RIGHT_POS CVector3(MAPCHIP_SIZE + REF_SIZE_X ,0.0f,0.0f) //ポジション左
#define SET_REF_RIGHT_OBB OBB_RIGHT_POS,OBB_SIZE,&mSideMatrix//右
#define SET_REF_LEFT_OBB  OBB_LEFT_POS,OBB_SIZE, &mSideMatrix//左
/*左右の向き*/
#define FRONT_ROT	CVector3(ANGLE_315,ANGLE_180,0.0f)
#define BACK_ROT	CVector3(ANGLE_315,0.0f,0.0f)
#define LEFT_ROT	CVector3(0,0,0)
#define RIGHT_ROT	CVector3(0,0,0)

#include "../../../../Key/CKey.h"

/*更新*/
CSlopeEnd::CSlopeEnd(CVector3 pos, int x, int z) : CSlope(pos, x, z),
mpColRefLeft(nullptr),mpColRefRight(nullptr){
	
}

CVector3 SaveRot;
/*当たり判定初期化 右*/
void CSlopeEnd::ColInitRight(const CVector3 rot){
	/*インスタンス作成*/
	mpColRefRight = new CCollider(E_COL_BOX);
	/*親設定*/
	mpColRefRight->mpParent = this;
	/*当たり判定　跳ね返りよう　パラメータ設定*/
	mpColRefRight->SetBoxOBB(SET_REF_RIGHT_OBB);								
	//タグ決める
	mpColRefRight->eTag = CTask::E_TAG::E_TAG_SLOPE_REF;							
	//当たり判定追加
	CCollisionManager::GetInstance()->Add(mpColRefRight->eTag, mpColRefRight);	
	/*サイズきめ*/
	mpColRefRight->SetObbSize(new float[]{REF_SIZE_X, REF_SIZE_Y, mMaxZ});//当たり判定
	mSideMatrix = mSideMatrix.MatrixTransform(mPos,rot);
	SaveRot = rot;
}
/*当たり判定初期化 左*/
void CSlopeEnd::ColInitLeft(const CVector3 rot){
	/*インスタンス作成*/
	mpColRefLeft = new CCollider(E_COL_BOX);
	/*親設定*/
	mpColRefRight->mpParent = this;
	/*当たり判定　跳ね返りよう　パラメータ設定*/
	mpColRefLeft->SetBoxOBB(SET_REF_LEFT_OBB);
	//タグ決める
	mpColRefLeft->eTag = CTask::E_TAG::E_TAG_SLOPE_REF;
	//当たり判定追加
	CCollisionManager::GetInstance()->Add(mpColRefLeft->eTag, mpColRefLeft);
	/*サイズきめ*/
	mpColRefLeft->SetObbSize(new float[]{REF_SIZE_X, REF_SIZE_Y, mMaxZ});//当たり判定
	mSideMatrix = mSideMatrix.MatrixTransform(mPos,rot);
	SaveRot = rot;


}

/*当たり判定の初期化*/
void CSlopeEnd::ColInit(ESlpoeRot eState){
	/*坂の向きにより初期化*/
	switch (eState)
	{
		/*前*/
	case CSlope::E_FRONT:
		/*左右に障害物がなければ生成*/
		if (!CMap::FlagMapMacth(mMapChipX -1, mMapChipZ, CMap::E_SLOP_8)){
			ColInitRight(FRONT_ROT);
		}
		if (!CMap::FlagMapMacth(mMapChipX + 1, mMapChipZ, CMap::E_SLOP_8)){
			ColInitLeft(FRONT_ROT);
		}

		
		break;
		/*後ろ*/
	case CSlope::E_BACK:
		/*左右に障害物がなければ生成*/
		if (!CMap::FlagMapMacth(mMapChipX + 1, mMapChipZ, CMap::E_SLOP_8)){
			ColInitRight(BACK_ROT);
		}
		if (!CMap::FlagMapMacth(mMapChipX - 1, mMapChipZ, CMap::E_SLOP_8)){
			ColInitLeft(BACK_ROT);

		}

		break;
		/*右*/
	case CSlope::E_RIGHT:
		/*左右に障害物がなければ生成*/
		if (!CMap::FlagMapMacth(mMapChipX , mMapChipZ -1, CMap::E_SLOP_8)){
			ColInitRight(RIGHT_ROT);
		}
		if (!CMap::FlagMapMacth(mMapChipX , mMapChipZ + 1, CMap::E_SLOP_8)){
			ColInitLeft(RIGHT_ROT);

		}

		break;
		/*左*/
	case CSlope::E_LEFT:
		/*左右に障害物がなければ生成*/
		if (!CMap::FlagMapMacth(mMapChipX , mMapChipZ+1, CMap::E_SLOP_8)){
			ColInitRight(LEFT_ROT);
		}
		if (!CMap::FlagMapMacth(mMapChipX , mMapChipZ-1, CMap::E_SLOP_8)){
			ColInitLeft(LEFT_ROT);

		}

		break;
	}
}

//初期化
void CSlopeEnd::SlopeEndInit(){
	//マップによって坂の向きを変える 
	CSlope::MapRot();	
	/*当たり判定初期化 引数は現在の方向enum*/
	ColInit(eSlopeRot);

}
/*更新*/
void CSlopeEnd::Update(){

	/*壁が横にある場合ローテーション1回のみする*/
	if (!mFlagRot){
		SlopeEndInit();
		mFlagRot = true;
	}
	/*当たり判定更新*/
	mpColBox->Update();
	/*生成されているなら更新*/
	if (mpColRefLeft != 0){
		mpColRefLeft->Update(); 

		/*タス*/
		if (CKey::push('1') && SaveRot.x <= 360){
			SaveRot.x += 0.1;
			printf("回転値(%f,%f,%f)\n",SaveRot.x,SaveRot.y,SaveRot.z);
		}
		if (CKey::push('2') && SaveRot.y <= 360){
			SaveRot.y += 0.1;
			printf("回転値(%f,%f,%f)\n",SaveRot.x,SaveRot.y,SaveRot.z);
		}
		if (CKey::push('3') && SaveRot.z <= 360){
			SaveRot.z += 0.1;
			printf("回転値(%f,%f,%f)\n", SaveRot.x, SaveRot.y, SaveRot.z);
		}
		/*引く*/
		if (CKey::push('4') && SaveRot.x >= 0){
			SaveRot.x -= 0.1;
			printf("回転値(%f,%f,%f)\n", SaveRot.x, SaveRot.y, SaveRot.z);
		}
		if (CKey::push('5') && SaveRot.y >= 0){
			SaveRot.y -= 0.1;
			printf("回転値(%f,%f,%f)\n", SaveRot.x, SaveRot.y, SaveRot.z);
		}
		if (CKey::push('6') && SaveRot.z >= 0){
			SaveRot.z -= 0.1;
			printf("回転値(%f,%f,%f)\n", SaveRot.x, SaveRot.y, SaveRot.z);
		}
		mSideMatrix = mSideMatrix.MatrixTransform(mPos, SaveRot);

	}

	if (mpColRefRight != 0)mpColRefRight->Update();
}

/*描画*/
void CSlopeEnd::Render(){
	UpdateMatrix();
	CBox::Render();
#ifdef _DEBUG 
	//mpColBox->Render();
	/*生成されているなら更新*/
	if (mpColRefLeft != 0)mpColRefLeft->Render();
	if (mpColRefRight != 0)mpColRefRight->Render();
#endif
}
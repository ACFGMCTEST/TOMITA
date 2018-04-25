#include "CSlopeEnd.h"

#include "../../../../Collision/CCollisionManager.h"
#include "../CMap.h"

/*当たり判定 跳ね返りよう*/
#define REF_SIZE_X mMaxX * 0.05f			//当たり判定のX
#define REF_SIZE_Y mMaxY 				//当たり判定のY
#define REF_SIZE_Z mMaxZ 				//当たり判定のZ
#define OBB_LEFT_POS CVector3(-MAPCHIP_SIZE - REF_SIZE_X ,0.0f,0.0f) //ポジション右
#define OBB_RIGHT_POS CVector3(MAPCHIP_SIZE + REF_SIZE_X ,0.0f,0.0f) //ポジション左
#define SET_REF_RIGHT_OBB OBB_RIGHT_POS,OBB_SIZE,&mMatrix//右
#define SET_REF_LEFT_OBB  OBB_LEFT_POS,OBB_SIZE, &mMatrix//左


#include "../../../../Key/CKey.h"

/*更新*/
CSlopeEnd::CSlopeEnd(CVector3 pos, int x, int z) : CSlope(pos, x, z),
mpColRefLeft(nullptr),mpColRefRight(nullptr){
	
}


/*当たり判定初期化 右*/
void CSlopeEnd::ColInitRight(){
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
	mpColRefRight->SetObbSize(CVector3(REF_SIZE_X, REF_SIZE_Y, mMaxZ));//当たり判定
}
 
/*当たり判定初期化 左*/
void CSlopeEnd::ColInitLeft(){
	/*インスタンス作成*/
	mpColRefLeft = new CCollider(E_COL_BOX);
	/*親設定*/
	mpColRefLeft->mpParent = this;
	/*当たり判定　跳ね返りよう　パラメータ設定*/
	mpColRefLeft->SetBoxOBB(SET_REF_LEFT_OBB);
	//タグ決める
	mpColRefLeft->eTag = CTask::E_TAG::E_TAG_SLOPE_REF;
	//当たり判定追加
	CCollisionManager::GetInstance()->Add(mpColRefLeft->eTag, mpColRefLeft);
	/*サイズきめ*/
	mpColRefLeft->SetObbSize(CVector3( REF_SIZE_X, REF_SIZE_Y, mMaxZ));//当たり判定
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
			ColInitRight();
		}
		if (!CMap::FlagMapMacth(mMapChipX + 1, mMapChipZ, CMap::E_SLOP_8)){
			ColInitLeft();
		}

		
		break;
		/*後ろ*/
	case CSlope::E_BACK:
		/*左右に障害物がなければ生成*/
		if (!CMap::FlagMapMacth(mMapChipX + 1, mMapChipZ, CMap::E_SLOP_8)){
			ColInitRight();
		}
		if (!CMap::FlagMapMacth(mMapChipX - 1, mMapChipZ, CMap::E_SLOP_8)){
			ColInitLeft();

		}

		break;
		/*右*/
	case CSlope::E_RIGHT:
		/*左右に障害物がなければ生成*/
		if (!CMap::FlagMapMacth(mMapChipX , mMapChipZ +1, CMap::E_SLOP_8)){
			ColInitRight();
		}
		if (!CMap::FlagMapMacth(mMapChipX , mMapChipZ - 1, CMap::E_SLOP_8)){
			ColInitLeft();

		}

		break;
		/*左*/
	case CSlope::E_LEFT:
		/*左右に障害物がなければ生成*/
		if (!CMap::FlagMapMacth(mMapChipX , mMapChipZ-1, CMap::E_SLOP_8)){
			ColInitRight();
		}
		if (!CMap::FlagMapMacth(mMapChipX , mMapChipZ+1, CMap::E_SLOP_8)){
			ColInitLeft();

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

	/*反射壁を生成するかどうか判定*/
	if (!mFlagRot){
		SlopeEndInit();
		mFlagRot = true;
	}
	/*当たり判定更新*/
	mpColBox->Update();
	/*生成されているなら更新*/
	if (mpColRefLeft != 0)	mpColRefLeft->Update(); 
	if (mpColRefRight != 0)mpColRefRight->Update();
}

/*描画*/
void CSlopeEnd::Render(){
	UpdateMatrix();
	CBox::Render();

}
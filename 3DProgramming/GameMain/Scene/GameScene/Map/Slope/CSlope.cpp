#include "CSlope.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollisionManager.h"
#include "../CMap.h"




/*更新*/
CSlope::CSlope(CVector3 pos,int x, int z) {
	mFlagRot = false;
	mMapChipX = x;
	mMapChipZ = z;
	/*当たり判定インスタンス作成*/
	mpColBox = new CCollider(E_COL_BOX);
	//mpColRefLeft = new CCollider(E_COL_BOX);
	//mpColRefRight = new CCollider(E_COL_BOX);


	/*親設定*/
	mpColBox->mpParent = this;
	/*ポジション設定*/
	mPos.x = pos.x;
	mPos.y = -MAPCHIP_SIZE/2;
	mPos.z = pos.z;
	UpdateMatrix();

	/*サイズ設定*/
	mMinX = -MAPCHIP_SIZE;
	mMaxX =  MAPCHIP_SIZE;
	mMinY = -MAPCHIP_SIZE;
	mMaxY =  MAPCHIP_SIZE;
	mMinZ = -MAPCHIP_SIZE;
	mMaxZ =  MAPCHIP_SIZE;
	SetVertex(mMinX,mMaxX,mMinY,mMaxY,mMinZ,mMaxZ);

	/*色設定*/
	SetColor(WHITE_COLOR);
	/*レンダー順番決める*/
	ePriority = CTask::E_SLOPE;
	/*テクスチャ*/
	SetTex(CBox::E_BOX);

	/*当たり判定設定 坂本体*/
	mpColBox->SetBoxOBB(SET_OBB);									//設定
	mpColBox->SetColor(WHITE_COLOR);								//色設定		
	mpColBox->eTag = CTask::E_TAG::E_TAG_SLOPE;						//タグ決める
	CCollisionManager::GetInstance()->Add(mpColBox->eTag, mpColBox);//当たり判定追加

	///*当たり判定　跳ね返りよう*/
	//mpColRefLeft->SetBoxOBB(SET_REF_LEFT_OBB);									//設定
	//mpColRefRight->SetBoxOBB(SET_REF_RIGHT_OBB);									//設定
	//mpColRefLeft->SetColor(WHITE_COLOR);											//色設定		
	//mpColRefRight->SetColor(WHITE_COLOR);											//色設定		
	//mpColRefLeft->eTag = CTask::E_TAG::E_TAG_SLOPE_REF;							//タグ決める
	//mpColRefRight->eTag = CTask::E_TAG::E_TAG_SLOPE_REF;						    //タグ決める
	//CCollisionManager::GetInstance()->Add(mpColRefLeft->eTag, mpColRefLeft);	    //当たり判定追加
	//CCollisionManager::GetInstance()->Add(mpColRefRight->eTag, mpColRefRight);	//当たり判定追加
}

/*サイズすべて*/
void CSlope::SetSize(float size){
	/*サイズ設定*/
	mMinX = -size;
	mMaxX = size;
	mMinY = 0;
	mMaxY = size;
	mMinZ = -size;
	mMaxZ = size;
}


/*マップによって向きを変える デフォルトは，左下がり右上がり*/
void CSlope::MapRot(){
	/*マップチップの斜め*/
#define  CHIP_SLANTING sqrt(MAPCHIP_SIZE*MAPCHIP_SIZE +MAPCHIP_SIZE*MAPCHIP_SIZE )

	/*手前がボックスだった場合 && マップからはみ出してないか つまり坂は後ろにあります*/
	if (CMap::FlagMapMacth(mMapChipX, mMapChipZ - 1, CMap::E_HIGH_BOX_A)){
		eSlopeRot = E_FRONT;
		/*回転させ坂の向きを決める*/
		mRot.x = ANGLE_315;
		mRot.y = ANGLE_180;
		/*サイズ変更*/
		SetSize(CHIP_SLANTING);
		mMinX = -SMALL_SIZE(MAPCHIP_SIZE);
		mMaxX =  SMALL_SIZE(MAPCHIP_SIZE);

		///*ポジション設定*/
		mPos.z -= MAPCHIP_SIZE;
	}
	/*左がボックスだった場合&& マップからはみ出してないか つまり坂は右にあります*/
	if (CMap::FlagMapMacth(mMapChipX - 1, mMapChipZ, CMap::E_HIGH_BOX_A)){
		eSlopeRot = E_LEFT;
		/*回転させ坂の向きを決める*/
		mRot.y = ANGLE_90;
		mRot.x = ANGLE_45;
		//mRot.z = ANGLE_45;
		/*サイズ変更*/
		SetSize(CHIP_SLANTING);
		mMinX = -SMALL_SIZE(MAPCHIP_SIZE);
		mMaxX = SMALL_SIZE(MAPCHIP_SIZE);


		///*ポジション設定*/
		mPos.x -= MAPCHIP_SIZE;
	}

	/*右がボックスだった場合&& マップからはみ出してないか つまり坂は左にあります*/
	if (CMap::FlagMapMacth(mMapChipX + 1, mMapChipZ, CMap::E_HIGH_BOX_A)){
		eSlopeRot = E_RIGHT;
		/*回転させ坂の向きを決める*/
		mRot.y = ANGLE_270;
		mRot.x = 45;

		/*サイズ変更*/
		SetSize(CHIP_SLANTING);
		mMinX = -SMALL_SIZE(MAPCHIP_SIZE);
		mMaxX = SMALL_SIZE(MAPCHIP_SIZE);


		//*ポジション設定*/
		//mPos = ARRAY_POS(POS_X(mMapChipX+1), -MAPCHIP_SIZE / 2, POS_Z(mMapChipZ));
		mPos.x += MAPCHIP_SIZE;
	}
	/*後ろがボックスだった場合&& マップからはみ出してないか つまり坂は前にあります*/
	if (CMap::FlagMapMacth(mMapChipX, mMapChipZ + 1, CMap::E_HIGH_BOX_A)){
		eSlopeRot = E_BACK;
		/*回転させ坂の向きを決める*/
		mRot.x = ANGLE_315;
		/*サイズ変更*/
		SetSize(CHIP_SLANTING);
		mMinX = -SMALL_SIZE(MAPCHIP_SIZE);
		mMaxX = SMALL_SIZE(MAPCHIP_SIZE);


		///*ポジション設定*/
		mPos.z += MAPCHIP_SIZE;
	}


	/*サイズ設定*/
	SetVertex(mMinX, mMaxX, mMinY, mMaxY, mMinZ, mMaxZ);
	mpColBox->SetObbSize(new float[]{mMaxX, mMaxY, mMaxZ});//当たり判定

	//mpColRefLeft->SetObbSize(new float[]{REF_SIZE_X,REF_SIZE_Y, mMaxZ});//当たり判定
	//mpColRefRight->SetObbSize(new float[]{REF_SIZE_X, REF_SIZE_Y, mMaxZ});//当たり判定

	/*回転*/
	mpColBox->SetObbRot(CVector3(mRot.x, mRot.y, mRot.z));

	//mpColRefLeft->SetObbRot(CVector3(mRot.x, mRot.y, mRot.z));
	//mpColRefRight->SetObbRot(CVector3(mRot.x, mRot.y, mRot.z));


}

/*更新*/
void CSlope::Update(){
	
	/*壁が横にある場合ローテーション1回のみする*/
	if (!mFlagRot){
		MapRot();//マップによって坂の向きを変える 右向き
		mFlagRot = true;
	}
	mpColBox->Update();
	/*mpColRefLeft->Update();
	mpColRefRight->Update();*/

}

/*描画*/
void CSlope::Render(){
	UpdateMatrix();
	CBox::Render();
#ifdef _DEBUG 
	///mpColBox->Render();
	//mpColRefLeft->Render();
	//mpColRefRight->Render();
#endif

}

/*坂の中間値*/
CVector3 CSlope::MiddlePos(const CVector3 &pos) const {
	CVector3 returnPos;//値を返すよう
	returnPos = pos;
	float length;//坂の下からの距離

#define LENGTH(PLLen,SlopeLen,radius) ( abs( (PLLen - (SlopeLen - radius)) / (radius*2) ) )//坂の現在のポジション場所から割合を求める

	/*坂の状態遷移*/
	switch (eSlopeRot)
	{
		/*手前の時*/
	case CSlope::E_FRONT:
		length = LENGTH(pos.z, mPos.z, mMinZ);
		returnPos.y = mMaxY * length;//坂の間から長さを求める
		break;
		/*後ろの時*/
	case CSlope::E_BACK:
		length = LENGTH(pos.z, mPos.z, mMaxZ);//坂の現在のポジション場所から割合を求める
		returnPos.y = mMaxY * length;//坂の間から長さを求める
		break;
		/*右の時*/
	case CSlope::E_RIGHT:
		length = LENGTH(pos.x, mPos.x, mMaxX);
		returnPos.y = mMaxY * length;//坂の間から長さを求める
		break;
		/*左の時*/
	case CSlope::E_LEFT:
		length = LENGTH(pos.x, mPos.x, mMinX);
		returnPos.y = mMaxY * length;//坂の間から長さを求める
		break;
	};

	return returnPos;
}


/*
坂の傾きにする
*rot =  回転する値
*/
void CSlope::SlpoeRot(CVector3 *rot) const{


	/*坂の状態遷移*/
	switch (eSlopeRot)
	{

		/*手前の時*/
	case CSlope::E_FRONT:
		rot->x = ANGLE_45;
		rot->y = 0;
		rot->z = 0;
		break;

		/*後ろの時*/
	case CSlope::E_BACK:
		rot->x = ANGLE_125;
		rot->y = 0;
		rot->z = 0;
		break;
		/*右の時*/
	case CSlope::E_RIGHT:
		rot->x = 0;
		rot->y = 0;
		rot->z = ANGLE_125;
		break;
		/*左の時*/
	case CSlope::E_LEFT:
		rot->x = 0;
		rot->y = 0;
		rot->z = ANGLE_45;
		break;
	};


}

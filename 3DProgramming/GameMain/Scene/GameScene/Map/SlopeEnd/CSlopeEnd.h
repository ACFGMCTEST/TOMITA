
#ifndef SLOPE_END_HPP
#define SLOPE_END_HPP

#include "../Slope/CSlope.h"

/*坂クラス*/
class CSlopeEnd : public CSlope{
public:

	CCollider *mpColRefLeft;//左のあたりはんてい
	CCollider *mpColRefRight;//左のあたりはんてい

	/*デバック用*/
	CVector3 SaveRot;

	//端用マトリックス
	CMatrix44 mSideMatrix;

	/*当たり判定初期化 右 引数:回転値*/
	void ColInitRight();
	/*当たり判定初期化 左 引数:回転値*/
	void ColInitLeft();

	/*当たり判定の初期化 向きによって変える*/
	void ColInit(ESlpoeRot eState);
	/*コンストラクタ
	pos = 位置
	x , y = 自分のマップ上座標値*/
	CSlopeEnd(CVector3 pos, int x, int z);

	void SlopeEndInit();

	void Update();

	void Render();
};

#endif
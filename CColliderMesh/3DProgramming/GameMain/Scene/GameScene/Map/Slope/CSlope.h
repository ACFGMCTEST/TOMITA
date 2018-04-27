
#ifndef SLOPE_HPP
#define SLOPE_HPP

#include "../../../../../Base/CBase.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollider.h"

#include "../../../GameScene/Map/CMap.h"

/*坂クラス*/
class CSlope : public CBox{
private:
	int mMapChipX, mMapChipZ;//自分のマップチップ上の座標値
	bool mFlagRot;//回転したか判断
	/*坂の現在の向いている方向*/
	enum  ESlpoeRot{
		E_FRONT,// 前
		E_BACK,// 後ろ
		E_RIGHT,// 右
		E_LEFT,// 左
	};
	ESlpoeRot eSlopeRot = E_FRONT;//坂の向き
public:
	CCollider *mpColBox;		//あたり判定
	CCollider *mpColRefLeft;	//当たり判定跳ね返りよう左
	CCollider *mpColRefRight;	//当たり判定跳ね返りよう右

	float mMinX;//サイズ小さいほう
	float mMaxX;//サイズ大きいほう
	float mMinY;//サイズ小さいほう
	float mMaxY;//サイズ大きいほう
	float mMinZ;//サイズ小さいほう
	float mMaxZ;//サイズ大きいほう

	/*サイズすべて*/
	void SetSize(float size);

	/*コンストラクタ 
	pos = 位置
	x , y = 自分のマップ上座標値*/
	CSlope(CVector3 pos, int x, int z, char e);
	/*マップによって向きを変える デフォルトは，左下がり右上がり*/
	void MapRot();
	/*アップデート*/
	void Update();
	/*描画処理*/
	void Render();
	/*坂の中間値*/
	CVector3 MiddlePos(const CVector3 &pos) const;
	/*坂の傾きにする
	*rot =  回転する値
	*/
	void SlpoeRot(CVector3 *rot) const;
};

#endif
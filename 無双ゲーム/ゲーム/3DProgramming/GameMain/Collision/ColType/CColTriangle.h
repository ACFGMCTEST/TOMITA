#ifndef COL_TRIANGLE_H
#define COL_TRIANGLE_H

#include "CColBase.h"
#include "../CCollisionManager.h"


/*当たり判定クラス 三角面*/

//三角形コライダクラス
class CColTriangle : public CColBase {
private:

	//更新　頂点を合成行列で掛ける
	void Update();
public:
	int mNumber;//参加系ポリゴンの何番目に生成されたかカウント
	static int mAllCount;//三角ポリゴンの数をカウント

	CVector3 mV[3];
	CVector3 mPos;//三角形の中心

	/*トライアングル代入*/
	CColTriangle(bool addFlag);
	/*デストラクタ*/
	~CColTriangle();

	/*パラメータ設定*/
	CColTriangle(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2);
	//頂点を合成行列で掛けたコライダを取得する
	CColTriangle GetUpdate();
};


#endif
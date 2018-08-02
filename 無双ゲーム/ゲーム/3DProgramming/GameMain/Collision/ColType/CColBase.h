#ifndef COL_BASE_H
#define COL_BASE_H

#include "../../Vector/CVector3.h"
#include "../../Matrix/CMatrix44.h"
#include "../../Task/CTask.h"

/*当たり判定クラスベース*/
class CColBase : public CTask
{
protected:
	float r, g, b, a;//色情報
public:
	CTask * mpParent;	//親のタスク
	CMatrix44 *mpCombinedMatrix;	//フレームの合成行列
	CVector3 mPos;		//中心座標
	CVector3 mAdjust;	//衝突応答　調整値

	/*当たり判定属性用*/
	enum E_STATE {
		NO,//設定なし
		PL_ATTACK,//プレイヤーのアタック
		PL_ATTACK_EFFECT3D,//3Dエフェクトの当たり判定
		PL_BODY,//プレイヤーのボディ
		ENE_BODY,//エネミーのアタック
	};
	E_STATE eState;

	CColBase() : mpParent(0), mpCombinedMatrix(0){}

	/*色設定*/
	void SetColor(float cr, float cg, float cb, float ca){
		r = cr;
		g = cg;
		b = cb;
		a = ca;
	}
	/*描画処理*/
	virtual void Render() {};

};

#endif
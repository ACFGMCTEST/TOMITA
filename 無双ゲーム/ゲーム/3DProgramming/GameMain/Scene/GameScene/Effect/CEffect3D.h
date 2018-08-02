//冨田健斗
#ifndef CEffect3D_HPP
#define CEffect3D_HPP
#include "../../../Graphic/CModelX.h"
#include "CEffect2D.h"
#include "../../../Collision/ColType/CColSphere.h"

class CEffect3D : public CModelXS ,public CTask {
private :
	CColSphere * mpCol;//当たり判定
	CEffect2D * mpEffect;//エフェクト
	//計算で使うもの
	CVector3 mPos;
	CVector3 mRot;
	//元の位置
	CVector3 *mpPos;
	CVector3 *mpRot;
public:
	~CEffect3D();
	CEffect3D();
	/*初期化*/
	void Init(CTask *parent, CModelX *mod,CVector3 *ppos,CVector3 *pRot);
	/*描画*/
	void Render();
	/*更新*/
	void Update();
	//ポジションを元に戻す
	void PosInit();
	/*移動関数*/
	void Move();
	//ポジション更新
	void PosUpdate();
};
#endif

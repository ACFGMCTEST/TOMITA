
#ifndef HIGH_BOX_HPP
#define HIGH_BOX_HPP

#include "../../../../../Base/CBase.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollider.h"

class CHighBox : public CBox{
public:
	CCollider *mpColBox;		//あたり判定

	/*コンストラクタ 
	pos = 位置*/
	CHighBox(CVector3 pos);
	/*アップデート*/
	void Update();
	/*描画処理*/
	void Render();

};

#endif

#ifndef SLOW_FLOOR_HPP
#define SLOW_FLOOR_HPP

#include "../../../../../Base/CBase.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollider.h"
/*坂クラス*/
class CSlowFloor : public CBox{
public:
	CCollider *mpColBox;		//あたり判定

	/*コンストラクタ 
	pos = 位置*/
	CSlowFloor(CVector3 pos);
	/*アップデート*/
	void Update();
	/*描画処理*/
	void Render();

};

#endif

#ifndef FAST_FLOOR_HPP
#define FAST_FLOOR_HPP

#include "../../../../../Base/CBase.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollider.h"

/*坂クラス*/
class CFastFloor : public CBox{
public:
	CCollider *mpColBox;		//あたり判定

	/*コンストラクタ 
	pos = 位置*/
	CFastFloor(CVector4 pos);
	/*アップデート*/
	void Update();
	/*描画処理*/
	void Render();

};

#endif
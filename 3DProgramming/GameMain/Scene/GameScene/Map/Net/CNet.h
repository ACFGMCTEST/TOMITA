
#ifndef NET_HPP
#define NET_HPP

#include "../../../../../Base/CBase.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollider.h"
/*網クラス*/
class CNet : public CBox{
public:
	CCollider *mpColBox;		//あたり判定

	/*コンストラクタ 
	pos = 位置*/
	CNet(CVector4 pos);
	/*アップデート*/
	void Update();
	/*描画処理*/
	void Render();

};

#endif
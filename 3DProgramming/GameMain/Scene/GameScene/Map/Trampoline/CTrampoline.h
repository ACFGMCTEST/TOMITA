
#ifndef TRAMPOLINE_HPP
#define TRAMPOLINE_HPP

#include "../../../../../Base/CBase.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollider.h"

/*坂クラス*/
class CTrampoline : public CBox{
public:
	CCollider*mpColBox;		//あたり判定

	/*コンストラクタ 
	pos = 位置*/
	CTrampoline(CVector3 pos);
	/*アップデート*/
	void Update();
	/*描画処理*/
	void Render();

};

#endif
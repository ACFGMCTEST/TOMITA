#ifndef MAP_HPP
#define MAP_HPP

#include "../../../Collision/CCollisionManager.h"

/*マップ*/
class CMap{

private:
	CMatrix44 m44;//仮のもの
public:
	/*当たり判定*/
	CCollider *mpGround;//仮のもの

	CMap(){};
	~CMap(){};
	/*初期化*/
	void Init();
	/*更新*/
	void Update();
	/*描画*/
	void Render();


};

#endif
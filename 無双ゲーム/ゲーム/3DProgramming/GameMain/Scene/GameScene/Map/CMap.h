#ifndef MAP_HPP
#define MAP_HPP
#include "../../../Graphic/CModelX.h"
#include "../../../Graphic/CBox.h"
#include "../../../Collision/CCollisionManager.h"
#include "../../../Graphic/CModelObj.h"

/*マップ*/
class CMap{

private:
	static CMap *mMap;
	CMatrix44 m44;//仮のもの
	CModelX mGroundX;//Xファイル描画用
	CModelObj mGround;//Objファイル
	CModelObj mSky;//背景
	
public:
	CMatrix44 mRespawn;//リスポーンする行列
	static CMap *GetInstance();
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
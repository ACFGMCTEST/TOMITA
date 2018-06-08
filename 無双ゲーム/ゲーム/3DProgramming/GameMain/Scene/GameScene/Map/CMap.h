#ifndef MAP_HPP
#define MAP_HPP
#include "../../../Graphic/CModelX.h"
#include "../../../Graphic/CBox.h"
#include "../../../Collision/CCollisionManager.h"
#include "../../../Graphic/CModelObj.h"

/*マップ*/
class CMap{

private:
	CMatrix44 m44;//仮のもの
	CModelX mGroundX;//Xファイル描画用
	CModelObj mGround;//Objファイル
	CBox mSkyBox;//背景
	
public:
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
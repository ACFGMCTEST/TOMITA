#ifndef MAP_HPP
#define MAP_HPP
#include "../../../Graphic/CModelX.h"
#include "../../../Graphic/CBox.h"
#include "../../../Collision/CCollisionManager.h"
#include "../../../Graphic/CModelObj.h"
#include "../../../Graphic/CBillBoard.h"

/*マップのボーンの名前*/
#define ENEMY_RESP_0 "EnemyResp0"
#define ENEMY_RESP_1 "EnemyResp1"
#define ENEMY_RESP_2 "EnemyResp2"
#define ENEMY_KING_RESP "Armature"

/*マップ*/
class CMap{

private:
	static CMap *mMap;
	CMatrix44 m44;//仮のもの

	CModelX mGroundX;//Xファイル描画用
	CModelObj mGround;//Objファイル
	CModelObj mSky;//背景

	CBillBoard *mpMiniRect;//ミニマップ用
	CVector3 mPos;//ポジション
public:
	static CMap *GetInstance();
	CMap() : mPos(0.0f, 0.0f, 0.0f){};
	~CMap(){};
	/*初期化*/
	void Init();
	/*更新*/
	void Update();
	/*描画*/
	void Render();
	/*ミニマップ用描画*/
	void MiniMapRender();
	/*ミニマップ設定*/
	void SetMiniMap();
	/*引数の名前のマトリックを返す*/
	CMatrix44 Matrix(char *name) {
	return mGroundX.FindFrame(name)->mCombinedMatrix;
	}

};

#endif
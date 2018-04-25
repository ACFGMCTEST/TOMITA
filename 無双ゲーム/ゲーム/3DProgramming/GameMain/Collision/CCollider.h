#ifndef CCOLLIDERBOX_H
#define CCOLLIDERBOX_H
#include "../Task/CTask.h"
#include "CCollision.h"

/*当たり判定クラス
eColTagを指定し形を決めている
*/
class CCollider :public CTask
{
private:
	/*当たり判定*/
	CVector3 *mpPos;//ポジション同期用

	/*当たり判定(ボックス用)*/
	CVector3 mParentNextPos;//ボックスの親からの位置
public:
	/*当たり判定　ボックス*/
	COBB mObb;
	/*当たり判定 球*/
	CColSphere mColSphere;



	//フレームの合成行列
	CMatrix44 *mpCombinedMatrix;
	CCollider(CTask::E_COL_TAG tag) : mpCombinedMatrix(0){
		eColTag = tag;
	}


	//OBBのボックスパラメータ設定
	void SetBoxOBB(CVector3 &center, CVector3 size, CMatrix44 *m);

	/*球のパラメータ設定*/
	void SetShere(float radius, CVector3 pos, CMatrix44 *m);

	/*壁のパラメーター設定 壁の向きとポジション*/
	void SetWall(CVector3 normal, CVector3 *pos);

	/*サイズアップ*/
	void SizeUP(float f);

	/*Obbを回転させる*/
	void SetObbRot(const CVector3 rot);
	/*Obbを大きくさせる*/
	void SetObbSize(float length[]);

	/*色設定*/
	void SetColor(float cr, float cg, float cb, float ca);
	void Update();
	void Render();
	void Render(COBB *obb);


};

#endif

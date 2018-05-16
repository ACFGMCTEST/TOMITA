#include "CColSphere.h"
#include "../CCollisionManager.h"
#include "glut.h"
/*球体の分割数*/
#define DIVISION_NUM 20,20

/*コンストラクタ*/
CColSphere::CColSphere(){
	mType = COL_SPHEPE;//球体にする
	CCollisionManager::GetInstance()->Add(this);//あたり判定追加
}

/*球のパラメータ設定*/
CColSphere::CColSphere(CTask *parent, float radius, CVector3 pos, CMatrix44 *m){
	mParentNextPos = pos;
	mRadius = radius;
	mpCombinedMatrix = m;
	mpParent = parent;
}

/*更新処理*/
void CColSphere::Update(){
	/*ポジションを調整する*/
	mPos = mParentNextPos;
	//移動回転させる
	Transform(*mpCombinedMatrix);
}

/*更新処理呼び出し*/
CColSphere CColSphere::GetUpdate(){
	CColSphere c = *this;
	c.Update();
	return c;
}

//OBBに行列を反映
void CColSphere::Transform(CMatrix44 &mat) {
	CVector4 c = CVector4(mPos.x, mPos.y, mPos.z, 1);
	c = c*mat;
	mPos = CVector3(c.x, c.y, c.z);
}
/*描画*/
void CColSphere::Render(){
	glPushMatrix();
	glColor3d(r,g,b); //色の設定
	glTranslated(mPos.x, mPos.y, mPos.z);//平行移動値の設定
	glutSolidSphere(mRadius, DIVISION_NUM);//引数：(半径, Z軸まわりの分割数, Z軸に沿った分割数)
}
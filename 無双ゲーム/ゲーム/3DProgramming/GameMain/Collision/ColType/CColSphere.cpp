#include "CColSphere.h"
#include "../CCollisionManager.h"
#include "glut.h"
/*球体の分割数*/
#define DIVISION_NUM 20,20

/*当たり判定追加するとき*/
CColSphere::CColSphere(){
	mType = COL_SPHEPE;//球体にする
}

CColSphere::CColSphere(bool flag) {
	mType = COL_SPHEPE;//球体にする
	if (flag)	CCollisionManager::GetInstance()->Add(this);

};


/*球のパラメータ設定*/
CColSphere::CColSphere(CTask *parent, CVector3 pos, float radius, CMatrix44 *m,CColBase::E_STATE state)
:CColSphere(true){
	mPos = pos;
	mRadius = radius;
	mpCombinedMatrix = m;
	mMatrixRotation = *m;
	mpParent = parent;
	CColBase::eState = state;
}

/*球のパラメータ設定 マネージャーで管理しない場合*/
CColSphere::CColSphere(float radius, CVector3 pos, CMatrix44 *m){
	mPos = pos;
	mRadius = radius;
	mpCombinedMatrix = m;
	mMatrixRotation = *m;

}

/*更新処理*/
void CColSphere::Update(){
	/*CMatrix44 pos;
	pos.translate(mPos);
	*mpCombinedMatrix = *mpCombinedMatrix * pos;
    */
	Transform(*mpCombinedMatrix);
	//mPos = mPos * *mpCombinedMatrix;
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

	//glPushMatrix();
	//glColor3d(r,g,b); //色の設定
	//glTranslated(mPos.x, mPos.y, mPos.z);//平行移動値の設定
	//glutSolidSphere(mRadius, DIVISION_NUM);//引数：(半径, Z軸まわりの分割数, Z軸に沿った分割数)

	glPopMatrix();
	glPushMatrix();

	glMultMatrixf(mpCombinedMatrix->f);
	glutSolidSphere(mRadius, DIVISION_NUM);
	glPopMatrix();
}
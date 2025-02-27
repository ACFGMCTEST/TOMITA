#include "glut.h"
#include "CColCapsule.h"

/*コンストラクタ　引数:当たり判定追加しないか判断*/
CColCapsule::CColCapsule() : mRadius(0.0f) {
	mType = COL_CAPSULE;
}
/*更新処理*/
void CColCapsule::Update() {
	if (mpCombinedMatrix) {
		mV[0] = mV[0] * *mpCombinedMatrix;
		mV[1] = mV[1] * *mpCombinedMatrix;
	}
}
/*更新処理呼び出し*/
CColCapsule CColCapsule::GetUpdate() {
	CColCapsule cc = *this;
	cc.Update();
	return cc;
}
/*
カプセルコライダの初期化
parent:親へのポインタ
v0:頂点１
v1:頂点２
radius:半径
pcombinedMatrix:連結させるフレームの合成行列
*/
CColCapsule::CColCapsule(CTask *parent, CVector3 v0, CVector3 v1, float radius, CMatrix44 *pcombinedMatrix)
: CColCapsule()
{
	CCollisionManager::GetInstance()->Add(this);//あたり判定追加
	mpCombinedMatrix = pcombinedMatrix;
	mV[0] = v0;
	mV[1] = v1;
	mRadius = radius;
	mpParent = parent;
}

/*描画処理*/
void CColCapsule::Render() {
	float color[] = { 1.0f, 1.0f, 0.0f, 0.5f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	CMatrix44 mat;
	CVector3 vec;
	glPushMatrix();
	if (mpCombinedMatrix) glMultMatrixf(mpCombinedMatrix->f);
	glPushMatrix();
	vec = mV[0] - mV[1];
	vec = vec.normalize();
	vec = vec * mRadius;
	vec = mV[1] + vec;
	mat.translate(vec);
	glMultMatrixf(mat.f);
	glutSolidSphere(mRadius, 20, 20);


	glPopMatrix();
	glPushMatrix();
	vec = mV[1] - mV[0];
	vec = vec.normalize();
	vec = vec * mRadius;
	vec = mV[0] + vec;
	mat.translate(vec);
	glMultMatrixf(mat.f);
	glutSolidSphere(mRadius, 20, 20);
	glPopMatrix();

	glPopMatrix();
}

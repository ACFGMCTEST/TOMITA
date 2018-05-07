#include "glut.h"
#include "CColCapsule.h"



void CColCapsule::Update() {
	if (mpCombinedMatrix) {
		mV[0] = mV[0] * *mpCombinedMatrix;
		mV[1] = mV[1] * *mpCombinedMatrix;
	}
}

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
	eColTag = E_COL_CAPSULE;
	mpCombinedMatrix = pcombinedMatrix;
	mV[0] = v0;
	mV[1] = v1;
	mRadius = radius;
	mpParent = parent;
}

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

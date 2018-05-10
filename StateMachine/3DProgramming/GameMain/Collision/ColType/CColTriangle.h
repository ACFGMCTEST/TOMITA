#ifndef COL_TRIANGLE_H
#define COL_TRIANGLE_H

#include "CColBase.h"
#include "glut.h"

/*当たり判定クラス 三角面*/
class CColTriangle : CCollBase{
public:
	CVector3 v0, v1, v2;//三角形の頂点

};

#include "../CCollider.h"

class CColTriangle2 : public CCollider2 {
public:
	CColTriangle2() {
		eColTag = E_COL_TRIANGLE;
	}

	void Init(CTask *parent, CVector3 v0, CVector3 v1, CVector3 v2, CVector3& positionFromParent, CMatrix44 *pcombinedMatrix) {
		eColTag = E_COL_TRIANGLE;
		mPositionFromParent = positionFromParent;
		mMatrixFromParent.translate(positionFromParent);
		mpCombinedMatrix = pcombinedMatrix;
		if (mpCombinedMatrix)
			mMatrix = mMatrixFromParent * *mpCombinedMatrix;
		else
			mMatrix = mMatrixFromParent;

		mV[0][0] = v0;
		mV[0][1] = v1;
		mV[0][2] = v2;
		mpParent = parent;
		mV[1][0] = mV[0][0] * mMatrix;
		mV[1][1] = mV[0][1] * mMatrix;
		mV[1][2] = mV[0][2] * mMatrix;
	}

	void Render() {
		float color[] = { 1.0f, 1.0f, 0.0f, 0.5f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
		glPushMatrix();
//			glMultMatrixf(mMatrix.f);
			glNormal3f(0.0f, 1.0f, 0.0f);
			//三角形の描画
			glBegin(GL_TRIANGLES);	//三角形の頂点指定開始
			glVertex3f(mV[1][0].x, mV[1][0].y, mV[1][0].z);	//頂点の指定
			glVertex3f(mV[1][1].x, mV[1][1].y, mV[1][1].z);	//頂点の指定
			glVertex3f(mV[1][2].x, mV[1][2].y, mV[1][2].z);	//頂点の指定
			glEnd();	//頂点指定終了
		glPopMatrix();
	}

	void Update() {
		if (mpCombinedMatrix) {
			mMatrix = mMatrixFromParent * *mpCombinedMatrix;
			mV[1][0] = mV[0][0] * mMatrix;
			mV[1][1] = mV[0][1] * mMatrix;
			mV[1][2] = mV[0][2] * mMatrix;
		}
	}
};

#endif
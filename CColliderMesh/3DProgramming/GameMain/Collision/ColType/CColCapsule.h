#ifndef CCOLCAPSULE_H
#define CCOLCAPSULE_H

#include "glut.h"
#include "../CCollider.h"

class CColCapsule : public CCollider2 {
public:
	CColCapsule() {
		eColTag = E_COL_CAPSULE;
	}

	void Init(CTask *parent, CVector3 v0, CVector3 v1, float radius, CVector3& positionFromParent, CMatrix44 *pcombinedMatrix) {
		eColTag = E_COL_CAPSULE;
		mPositionFromParent = positionFromParent;
		mMatrixFromParent.translate(positionFromParent);
		mMatrix = mMatrixFromParent;
		mpCombinedMatrix = pcombinedMatrix;
		mV[0][0] = v0;
		mV[0][1] = v1;
		mF[0] = radius;
		mpParent = parent;
	}

	void Render() {
		float color[] = { 1.0f, 1.0f, 0.0f, 0.5f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
		CMatrix44 mat;
		CVector3 vec;
		glPushMatrix();
//			glMultMatrixf(mMatrix.f);
			glPushMatrix();
				vec = mV[1][0] - mV[1][1];
				vec = vec.normalize();
				vec = vec * mF[0];
				vec = mV[1][1] + vec;
				//
//				vec = mV[1][1];
				mat.translate(vec);
				glMultMatrixf(mat.f);
				glutSolidSphere(mF[0], 20, 20);
			glPopMatrix();
			glPushMatrix();
				vec = mV[1][1] - mV[1][0];
				vec = vec.normalize();
				vec = vec * mF[0];
				vec = mV[1][0] + vec;
				//
//				vec = mV[1][0];
				mat.translate(vec);
				glMultMatrixf(mat.f);
				glutSolidSphere(mF[0], 20, 20);
			glPopMatrix();

		glPopMatrix();
	}
	void Update() {
		if (mpCombinedMatrix) {
			mMatrix = mMatrixFromParent * *mpCombinedMatrix;
			mV[1][0] = mV[0][0] * mMatrix;
			mV[1][1] = mV[0][1] * mMatrix;
		}
	}

};

#endif


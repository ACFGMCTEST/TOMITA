#ifndef COL_TRIANGLE_H
#define COL_TRIANGLE_H

#include "CColBase.h"
#include "glut.h"

/*�����蔻��N���X �O�p��*/
class CColTriangle : CCollBase{
public:
	CVector3 v0, v1, v2;//�O�p�`�̒��_

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
			//�O�p�`�̕`��
			glBegin(GL_TRIANGLES);	//�O�p�`�̒��_�w��J�n
			glVertex3f(mV[1][0].x, mV[1][0].y, mV[1][0].z);	//���_�̎w��
			glVertex3f(mV[1][1].x, mV[1][1].y, mV[1][1].z);	//���_�̎w��
			glVertex3f(mV[1][2].x, mV[1][2].y, mV[1][2].z);	//���_�̎w��
			glEnd();	//���_�w��I��
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
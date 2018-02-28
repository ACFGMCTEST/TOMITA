#include "CBillBoard.h"
#include "glut.h"

void CBillBoard::SetVertex(float left, float right, float bottom, float top) {
	mVertex[0].x = left;
	mVertex[0].y = top;
	mVertex[0].z = 0.0f;
	mVertex[1].x = left;
	mVertex[1].y = bottom;
	mVertex[1].z = 0.0f;
	mVertex[2].x = right;
	mVertex[2].y = bottom;
	mVertex[2].z = 0.0f;
	mVertex[3].x = right;
	mVertex[3].y = top;
	mVertex[3].z = 0.0f;
}

void CBillBoard::Update() {
	mMatrix.identity();
	mMatrix.translate(mPosition);
	mMatrix = mMatrix * mpCamera->mCameraInverse;
}

void CBillBoard::Render() {

	glPushMatrix();
	glMultMatrixf(mMatrix.f);
	glBegin(GL_QUADS);
	glVertex3f(mVertex[0].x, mVertex[0].y, mVertex[0].z);
	glVertex3f(mVertex[1].x, mVertex[1].y, mVertex[1].z);
	glVertex3f(mVertex[2].x, mVertex[2].y, mVertex[2].z);
	glVertex3f(mVertex[3].x, mVertex[3].y, mVertex[3].z);
	glEnd();
	glPopMatrix();

}


#include "CBillBoard.h"
#include "glut.h"
#include "../Camera/CCamera.h"
//�J�����̃|�C���^
CCamera *CBillBoard::mpCamera = 0;
/*�R���X�g���N�^*/
CBillBoard::CBillBoard():mpTexture(0){}

/*�T�C�Y�ݒ�*/
void CBillBoard::SetVertex(float left, float right, float bottom, float top,CVector3 *pos) {
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
	mpPosition = pos;
}
/*�e�N�X�`���ݒ�*/
void CBillBoard::SetUv(CTexture *t, int left, int top, int right, int bottom) {
	mpTexture = t;
	mUv[0][0] = (float)left / mpTexture->header.width;
	mUv[0][1] = (float)(mpTexture->header.height - top) / mpTexture->header.height;
	mUv[1][0] = (float)left / mpTexture->header.width;
	mUv[1][1] = (float)(mpTexture->header.height - bottom) / mpTexture->header.height;
	mUv[2][0] = (float)right / mpTexture->header.width;
	mUv[2][1] = (float)(mpTexture->header.height - bottom) / mpTexture->header.height;
	mUv[3][0] = (float)right / mpTexture->header.width;
	mUv[3][1] = (float)(mpTexture->header.height - top) / mpTexture->header.height;
}
/*�X�V����*/
void CBillBoard::Update() {
	mMatrix.identity();
	mMatrix.translate(*mpPosition);
	mMatrix = mMatrix * mpCamera->mCameraInverse;
}
/*�`��*/
void CBillBoard::Render() {
	if (mpTexture){
		//�e�N�X�`����L���ɂ���
		glEnable(GL_TEXTURE_2D);
		//�A���t�@�u�����h��L���ɂ���
		glEnable(GL_BLEND);
		//�u�����h���@���w��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//�e�N�X�`�����w��
		glBindTexture(GL_TEXTURE_2D, mpTexture->id);
		float dif[4] = { 1.0f, 1.0f, 1.0f, 1.0f };//�J���[�ݒ�
		glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
		glPushMatrix();
		glMultMatrixf(mMatrix.f);
		glBegin(GL_QUADS);

		glTexCoord2fv(mUv[0]); glVertex3f(mVertex[0].x, mVertex[0].y, mVertex[0].z);
		glTexCoord2fv(mUv[1]); glVertex3f(mVertex[1].x, mVertex[1].y, mVertex[1].z);
		glTexCoord2fv(mUv[2]); glVertex3f(mVertex[2].x, mVertex[2].y, mVertex[2].z);
		glTexCoord2fv(mUv[3]); glVertex3f(mVertex[3].x, mVertex[3].y, mVertex[3].z);
		glEnd();
		glPopMatrix();

		//�e�N�X�`�������
		glBindTexture(GL_TEXTURE_2D, 0);
		//�A���t�@�u�����h�𖳌�
		glDisable(GL_BLEND);
		//�e�N�X�`���𖳌�
		glDisable(GL_TEXTURE_2D);
	}
	else{
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

}


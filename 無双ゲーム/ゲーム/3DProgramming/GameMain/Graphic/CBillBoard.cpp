#include "CBillBoard.h"
#include "glut.h"
#include "../Camera/CCamera.h"

///*�R���X�g���N�^*/
//CBillBoard::CBillBoard():mpTexture(0), mpCamera(0) {}

CBillBoard::CBillBoard() : mpTexture(0),mpRotation(0){
	CTask::eName = CTask::E_BILLBOARD;
	SetColor(WHITE_COLOR);
	mNormal.x = 0.0f;
	mNormal.y = 1.0f;
	mNormal.z = 0.0f;
}

/*�T�C�Y�ݒ�*/
void CBillBoard::SetVertex(CCamera *pCamera, SVer ver,
	CVector3 *pos,CVector3 *rot,CVector3 Ajust) {
	
	mVertex[0].x = ver.left;
	mVertex[0].y = ver.top;
	mVertex[0].z = 0.0f;
	mVertex[1].x = ver.left;
	mVertex[1].y = ver.bottom;
	mVertex[1].z = 0.0f;
	mVertex[2].x = ver.right;
	mVertex[2].y = ver.bottom;
	mVertex[2].z = 0.0f;
	mVertex[3].x = ver.right;
	mVertex[3].y = ver.top;
	mVertex[3].z = 0.0f;
	mpPosition = pos;
	mpRotation = rot;
	mAjustPos = Ajust;
	mpCamera = pCamera;
}
void CBillBoard::SetVertex(SVer ver) {

	mVertex[0].x = ver.left;
	mVertex[0].y = ver.top;
	mVertex[0].z = 0.0f;
	mVertex[1].x = ver.left;
	mVertex[1].y = ver.bottom;
	mVertex[1].z = 0.0f;
	mVertex[2].x = ver.right;
	mVertex[2].y = ver.bottom;
	mVertex[2].z = 0.0f;
	mVertex[3].x = ver.right;
	mVertex[3].y = ver.top;
	mVertex[3].z = 0.0f;
}

/*�T�C�Y�ݒ�*/
void CBillBoard::SetVertex(CCamera *pCamera, SVer ver,CVector3 *pos, CVector3 Ajust) {

	mVertex[0].x = ver.left;
	mVertex[0].y = ver.top;
	mVertex[0].z = 0.0f;
	mVertex[1].x = ver.left;
	mVertex[1].y = ver.bottom;
	mVertex[1].z = 0.0f;
	mVertex[2].x = ver.right;
	mVertex[2].y = ver.bottom;
	mVertex[2].z = 0.0f;
	mVertex[3].x = ver.right;
	mVertex[3].y = ver.top;
	mVertex[3].z = 0.0f;
	mpPosition = pos;
	mAjustPos = Ajust;
	mpCamera = pCamera;
}

/*�T�C�Y�ݒ�*/
void CBillBoard::SetVertex(CCamera *pCamera, float left, float right, float bottom, float top) {
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
	mpCamera = pCamera;
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
	CVector3 pos = *mpPosition + mAjustPos;
	mMatrix.identity();
	mMatrix.translate(pos);
	CMatrix44 rot_y;
	if (mpRotation) {
		rot_y.rotationY(mpRotation->y);
		mMatrix = mMatrix * rot_y *mpCamera->mCameraInverse;
	}
	else {
		mMatrix = mMatrix *mpCamera->mCameraInverse;
	}
}

/*�X�V����*/
void CBillBoard::BeforePosUpdate() {
	CMatrix44 rot_y,matrix;
	CVector3 forward = CVector3(0, 0, -1.0f);
	CVector3 pos = *mpPosition + mAjustPos;
	CVector3 rot = forward.getRotationTowards(mpCamera->mPos + pos * -1.0f);
	rot_y.rotationY(rot.y);
	//�i�s�������v�Z
	forward = forward * rot_y;
	//�ړ�������
	pos += forward * 0.1f;

	mMatrix.identity();
	mMatrix.translate(pos);
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
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mDif);
		glPushMatrix();
		glMultMatrixf(mMatrix.f);
		glNormal3f(mNormal.x, mNormal.y, mNormal.z);
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
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mDif);
		glMultMatrixf(mMatrix.f);
		glNormal3f(mNormal.x, mNormal.y, mNormal.z);
		glBegin(GL_QUADS);
		glVertex3f(mVertex[0].x, mVertex[0].y, mVertex[0].z);
		glVertex3f(mVertex[1].x, mVertex[1].y, mVertex[1].z);
		glVertex3f(mVertex[2].x, mVertex[2].y, mVertex[2].z);
		glVertex3f(mVertex[3].x, mVertex[3].y, mVertex[3].z);
		glEnd();
		glPopMatrix();
	}

}

void CBillBoard::MiniMapRender() {
	Render();
}

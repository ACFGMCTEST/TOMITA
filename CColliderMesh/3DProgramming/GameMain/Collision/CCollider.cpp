#include "CCollider.h"
#include "glut.h"
#include "CCollision.h"

/*�����T�C�Y*/
#define INIT_SIZE 1.0f
/*���̂̕�����*/
#define DIVISION_NUM 20,20

/*Obb��傫��������*/
void CCollider::SetObbSize(CVector3 &v){
	float a[] = { v.x, v.y, v.z };
	SetObbSize(a);
}
void CCollider::SetObbSize(float length[]){
		/*�{�b�N�X�ł��邩����*/
	if (eColTag == CTask::E_COL_BOX){
		for (int i = 0; i < 3; i++){
			mObb.mLength[i] = length[i];
		}
	}
	else if (eColTag == CTask::E_COL_NO){
		printf("�����蔻��̌`��ݒ肵�Ă�������\n");
		assert(false);
	}
	else
	{
		printf("�ݒ肵�Ă���`���Ⴂ�܂�\n");
		assert(false);
	}
}
/*
OBB�̃p�����[�^�ݒ�
center:���S�̍��W
lenght:xyz�̒���
matrix:�t���[���̍����s��
*/
void CCollider::SetBoxOBB(CVector3 &center, CVector3 &v, CMatrix44 *matrix){
	float a[] = { v.x, v.y, v.z };
	SetBoxOBB(center, a,matrix);
}

void CCollider::SetBoxOBB(CVector3 &center, float length[], CMatrix44 *matrix){


	/*�{�b�N�X�ł��邩����*/
	if (eColTag == CTask::E_COL_BOX){
		mParentNextPos = center;
		mObb.mAxis[0] = CVector3(1.0f, 0.0f, 0.0f);
		mObb.mAxis[1] = CVector3(0.0f, 1.0f, 0.0f);
		mObb.mAxis[2] = CVector3(0.0f, 0.0f, 1.0f);
		for (int i = 0; i < 3; i++){
			mObb.mLength[i] = length[i];
		}
		mpCombinedMatrix = matrix;
		mObb.mMatrixRotation = *matrix;
	}
	else if(eColTag == CTask::E_COL_NO){
		printf("�����蔻��̌`��ݒ肵�Ă�������\n");
		assert(false);
	}
	else
	{
		printf("�ݒ肵�Ă���`���Ⴂ�܂�\n");
		assert(false);
	}
}

/*Obb����]������*/
void CCollider::SetObbRot(const CVector3 rot){
	mObb.mRotation = rot;//��]�l����
	/*�{�b�N�X�ł��邩����*/
	if (eColTag == CTask::E_COL_BOX){


		CMatrix44 mx, mz;
		//��]������

		mx.rotationX(mObb.mRotation.x);
		mz.rotationZ(mObb.mRotation.z);
		
		*mpCombinedMatrix = *mpCombinedMatrix * mx * mz;
		mObb.mMatrixRotation = *mpCombinedMatrix;
	}
	else if (eColTag == CTask::E_COL_NO){
		printf("�����蔻��̌`��ݒ肵�Ă�������\n");
		assert(false);
	}
	else
	{
		printf("�ݒ肵�Ă���`���Ⴂ�܂�\n");
		assert(false);
	}
}

/*���̓����蔻��*/
void CCollider::SetShere(float radius,CVector3 pos,CMatrix44 *matrix){
	/*���̂ł��邩�ݒ�*/
	if (eColTag == CTask::E_COL_SPHEPE){
		mParentNextPos = pos;
		mColSphere.mRadius = radius;
		//mpPos = pos;
		mpCombinedMatrix = matrix;
	}
	else if (eColTag == CTask::E_COL_NO){
		printf("�����蔻��̌`��ݒ肵�Ă�������\n");
		assert(false);
	}
	else
	{
		printf("�ݒ肵�Ă���`���Ⴂ�܂�\n");
		assert(false);
	}
}

/*
Update
mOBB��ϊ��s��ňړ���]������
*/
void CCollider::Update(){
	
	switch (eColTag)
	{
	case CTask::E_COL_NO:
		break;
	case CTask::E_COL_BOX:
		mObb.mAxis[0] = CVector3(1.0f, 0.0f, 0.0f);
		mObb.mAxis[1] = CVector3(0.0f, 1.0f, 0.0f);
		mObb.mAxis[2] = CVector3(0.0f, 0.0f, 1.0f);


		//��]�s��̐ݒ�
		mObb.mPos = mParentNextPos;

		
		//�ړ���]������
		mObb.Transeform(*mpCombinedMatrix);
		break;
	case CTask::E_COL_SPHEPE:
		mColSphere.mPos = mParentNextPos;
		//�ړ���]������
		mColSphere.Transeform(*mpCombinedMatrix);
		break;
	default:
		break;
	}

}

void CCollider::Render(){

	switch (eColTag)
	{
	case CTask::E_COL_NO:
		printf("�����蔻��̌`��ݒ肵�܂��傤");
		assert(false);
		break;
	case CTask::E_COL_BOX:
		Render(&mObb);
		break;
	case CTask::E_COL_SPHEPE:
		glPushMatrix();
		glColor3d(mColSphere.r, mColSphere.g, mColSphere.b); //�F�̐ݒ�
		glTranslated(mColSphere.mPos.x, mColSphere.mPos.y, mColSphere.mPos.z);//���s�ړ��l�̐ݒ�
		glutSolidSphere(mColSphere.mRadius, DIVISION_NUM);//�����F(���a, Z���܂��̕�����, Z���ɉ�����������)
		glPopMatrix();
		break;
	default:
		break;
	}



}

//OBB�`��

void CCollider::Render(COBB *obb){
	CVector3 pos[8];
	for (int i = 0; i < 8; i++)
	{
		pos[i] = obb->mPos;

	}

	pos[0] += obb->mAxis[0] * obb->mLength[0];
	pos[0] += obb->mAxis[1] * obb->mLength[1];
	pos[0] += obb->mAxis[2] * obb->mLength[2];

	pos[1] -= obb->mAxis[0] * obb->mLength[0];
	pos[1] += obb->mAxis[1] * obb->mLength[1];
	pos[1] += obb->mAxis[2] * obb->mLength[2];

	pos[2] -= obb->mAxis[0] * obb->mLength[0];
	pos[2] -= obb->mAxis[1] * obb->mLength[1];
	pos[2] += obb->mAxis[2] * obb->mLength[2];

	pos[3] += obb->mAxis[0] * obb->mLength[0];
	pos[3] -= obb->mAxis[1] * obb->mLength[1];
	pos[3] += obb->mAxis[2] * obb->mLength[2];

	pos[4] += obb->mAxis[0] * obb->mLength[0];
	pos[4] += obb->mAxis[1] * obb->mLength[1];
	pos[4] -= obb->mAxis[2] * obb->mLength[2];

	pos[5] -= obb->mAxis[0] * obb->mLength[0];
	pos[5] += obb->mAxis[1] * obb->mLength[1];
	pos[5] -= obb->mAxis[2] * obb->mLength[2];

	pos[6] -= obb->mAxis[0] * obb->mLength[0];
	pos[6] -= obb->mAxis[1] * obb->mLength[1];
	pos[6] -= obb->mAxis[2] * obb->mLength[2];


	pos[7] += obb->mAxis[0] * obb->mLength[0];
	pos[7] -= obb->mAxis[1] * obb->mLength[1];
	pos[7] -= obb->mAxis[2] * obb->mLength[2];

	//�F�̐ݒ�ݒ�
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, CVector3(r, g, b, a});
	//�u�����h���@���w��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
#define GLVERPOS(i)  glVertex3f(pos[i].x, pos[i].y, pos[i].z)
	GLVERPOS(0);
	GLVERPOS(1);
	GLVERPOS(2);
	GLVERPOS(3);

	GLVERPOS(0);
	GLVERPOS(3);
	GLVERPOS(7);
	GLVERPOS(4);

	GLVERPOS(4);
	GLVERPOS(7);
	GLVERPOS(6);
	GLVERPOS(5);

	GLVERPOS(5);
	GLVERPOS(6);
	GLVERPOS(2);
	GLVERPOS(1);

	GLVERPOS(1);
	GLVERPOS(0);
	GLVERPOS(4);
	GLVERPOS(5);

	GLVERPOS(6);
	GLVERPOS(7);
	GLVERPOS(3);
	GLVERPOS(2);
	glEnd();

	//���u�����h����
	glDisable(GL_BLEND);

}
/*�F�ݒ�*/
void CCollider::SetColor(float cr, float cg, float cb, float ca){
	switch (eColTag)
	{
	case CTask::E_COL_NO:
		break;
	case CTask::E_COL_WALL:
		//mColWall.SetColor(cr, cg, cb, ca);
		break;
	case CTask::E_COL_BOX:
		mObb.SetColor(cr, cg, cb, ca);

		break;
	case CTask::E_COL_SPHEPE:
		mColSphere.SetColor(cr, cg, cb, ca);

		break;
	default:
		break;
	}
}

/*�T�C�Y�A�b�v*/
void CCollider::SizeUP(float f){
	for (int i = 0; i < 3; i++){
		mObb.mLength[i] += f;
	}
}
/*
bool CCollider3::Collision(CCollider3 *col) {
	switch (mType) {
	case COL_CAPSULE:
		CCollider3Capsule *pcc = dynamic_cast<CCollider3Capsule*>(this);
		switch (col->mType) {
		case COL_TRIANGLE:
			CCollider3Triangle *pct = dynamic_cast<CCollider3Triangle*>(col);
			return CCollision::IntersectTriangleCapsule3(pct->mV[0], pct->mV[0], pct->mV[0], pcc->mV[0], pcc->mV[1], pcc->mRadius, &mAdjust);
		}
	}
	return false;
}
*/
void CCollider3Triangle::Update() {
	if (mpCombinedMatrix) {
		mV[0] = mV[0] * *mpCombinedMatrix;
		mV[1] = mV[1] * *mpCombinedMatrix;
		mV[2] = mV[2] * *mpCombinedMatrix;
	}
}
void CCollider3Capsule::Update() {
	if (mpCombinedMatrix) {
		mV[0] = mV[0] * *mpCombinedMatrix;
		mV[1] = mV[1] * *mpCombinedMatrix;
	}
}

CCollider3Capsule CCollider3Capsule::GetUpdate() {
	CCollider3Capsule cc = *this;
	cc.Update();
	return cc;
}

void CCollider3Capsule::Init(CTask *parent, CVector3 v0, CVector3 v1, float radius, CMatrix44 *pcombinedMatrix) {
	eColTag = E_COL_CAPSULE;
	mpCombinedMatrix = pcombinedMatrix;
	mV[0] = v0;
	mV[1] = v1;
	mRadius = radius;
	mpParent = parent;
}

void CCollider3Capsule::Render() {
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

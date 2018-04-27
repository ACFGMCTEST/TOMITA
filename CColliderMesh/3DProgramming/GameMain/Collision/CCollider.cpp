#include "CCollider.h"
#include "glut.h"

/*�����T�C�Y*/
#define INIT_SIZE 1.0f
/*���̂̕�����*/
#define DIVISION_NUM 20,20

/*Obb��傫��������*/
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
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, new float[]{r, g, b, a});
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
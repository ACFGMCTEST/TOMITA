#include "CColSphere.h"
#include "../CCollisionManager.h"
#include "glut.h"
/*���̂̕�����*/
#define DIVISION_NUM 20,20

/*�����蔻��ǉ�����Ƃ�*/
void CColSphere::ColAdd(){
	mType = COL_SPHEPE;//���̂ɂ���
	CCollisionManager::GetInstance()->Add(this);//�����蔻��ǉ�
}



/*���̃p�����[�^�ݒ�*/
CColSphere::CColSphere(CTask *parent, CVector3 pos, float radius, CMatrix44 *m,CColBase::E_STATE state)
{
	ColAdd();
	mPos = pos;
	mRadius = radius;
	mpCombinedMatrix = m;
	mMatrixRotation = *m;
	mpParent = parent;
	CColBase::eState = state;
}

/*���̃p�����[�^�ݒ� �}�l�[�W���[�ŊǗ����Ȃ��ꍇ*/
CColSphere::CColSphere(float radius, CVector3 pos, CMatrix44 *m){
	mPos = pos;
	mRadius = radius;
	mpCombinedMatrix = m;
	mMatrixRotation = *m;

}

/*�X�V����*/
void CColSphere::Update(){
	/*CMatrix44 pos;
	pos.translate(mPos);
	*mpCombinedMatrix = *mpCombinedMatrix * pos;
    */
	Transform(*mpCombinedMatrix);
	//mPos = mPos * *mpCombinedMatrix;
}

/*�X�V�����Ăяo��*/
CColSphere CColSphere::GetUpdate(){
	CColSphere c = *this;
	c.Update();
	return c;
}

//OBB�ɍs��𔽉f
void CColSphere::Transform(CMatrix44 &mat) {
	CVector4 c = CVector4(mPos.x, mPos.y, mPos.z, 1);
	c = c*mat;
	mPos = CVector3(c.x, c.y, c.z);
}
/*�`��*/
void CColSphere::Render(){

	//glPushMatrix();
	//glColor3d(r,g,b); //�F�̐ݒ�
	//glTranslated(mPos.x, mPos.y, mPos.z);//���s�ړ��l�̐ݒ�
	//glutSolidSphere(mRadius, DIVISION_NUM);//�����F(���a, Z���܂��̕�����, Z���ɉ�����������)

	glPopMatrix();
	glPushMatrix();

	glMultMatrixf(mpCombinedMatrix->f);
	glutSolidSphere(mRadius, DIVISION_NUM);
	glPopMatrix();
}
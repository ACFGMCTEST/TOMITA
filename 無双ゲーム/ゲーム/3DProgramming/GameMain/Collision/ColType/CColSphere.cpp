#include "CColSphere.h"
#include "../CCollisionManager.h"
#include "glut.h"
/*���̂̕�����*/
#define DIVISION_NUM 20,20

/*�R���X�g���N�^*/
CColSphere::CColSphere(){
	mType = COL_SPHEPE;//���̂ɂ���
	CCollisionManager::GetInstance()->Add(this);//�����蔻��ǉ�
}

/*���̃p�����[�^�ݒ�*/
CColSphere::CColSphere(CTask *parent, float radius, CVector3 pos, CMatrix44 *m){
	mParentNextPos = pos;
	mRadius = radius;
	mpCombinedMatrix = m;
	mpParent = parent;
}

/*�X�V����*/
void CColSphere::Update(){
	/*�|�W�V�����𒲐�����*/
	mPos = mParentNextPos;
	//�ړ���]������
	Transform(*mpCombinedMatrix);
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
	glPushMatrix();
	glColor3d(r,g,b); //�F�̐ݒ�
	glTranslated(mPos.x, mPos.y, mPos.z);//���s�ړ��l�̐ݒ�
	glutSolidSphere(mRadius, DIVISION_NUM);//�����F(���a, Z���܂��̕�����, Z���ɉ�����������)
}
#include "COBB.h"
#include "../CCollisionManager.h"
#include "glut.h"

/*�R���X�g���N�^�@����:�����蔻���ǉ����邩���Ȃ������f*/
COBB::COBB(bool addCol){
	mType = COL_BOX;//���̂ɂ���
	/*�����Ŕ��f*/
	if (addCol)CCollisionManager::GetInstance()->Add(this);//�����蔻��ǉ�
};
/*�p�����[�^�ݒ�*/
COBB::COBB(CVector3 &center, CVector3 &v, CMatrix44 *matrix){
	/*�{�b�N�X�ł��邩����*/
	mPos = center;
	/*�x�N�g�������߂�*/
	mAxis[0] = CVector3(1.0f, 0.0f, 0.0f);
	mAxis[1] = CVector3(0.0f, 1.0f, 0.0f);
	mAxis[2] = CVector3(0.0f, 0.0f, 1.0f);
	/*���������߂�*/
	mLength[0] = v.x;
	mLength[1] = v.y;
	mLength[2] = v.z;

	mpCombinedMatrix = matrix;
	mMatrixRotation = *matrix;
}
/*�X�V����*/
void COBB::Update(){
	/*�x�N�g���̏�����*/
	mAxis[0] = CVector3(1.0f, 0.0f, 0.0f);
	mAxis[1] = CVector3(0.0f, 1.0f, 0.0f);
	mAxis[2] = CVector3(0.0f, 0.0f, 1.0f);
	//�ړ���]������
	Transform(*mpCombinedMatrix);
}

/*�X�V�����Ăяo��*/
COBB COBB::GetUpdate(){
	COBB c = *this;
	c.Update();
	return c;
}
//OBB�ɍs��𔽉f
void COBB::Transform(CMatrix44 &mat){
	for (int i = 0; i < COBB::E_ARRAY; i++) mAxis[i] = mat * mAxis[i] - mat * CVector3();
	CVector4 c = CVector4(mPos.x, mPos.y, mPos.z, 1);
	c = c*mat;
	mPos = CVector3(c.x, c.y, c.z);
}
/*�`��*/
void COBB::Render(){
	CVector3 pos[8];
	for (int i = 0; i < 8; i++)
	{
		pos[i] = mPos;

	}

	pos[0] += mAxis[0] * mLength[0];
	pos[0] += mAxis[1] * mLength[1];
	pos[0] += mAxis[2] * mLength[2];

	pos[1] -= mAxis[0] * mLength[0];
	pos[1] += mAxis[1] * mLength[1];
	pos[1] += mAxis[2] * mLength[2];

	pos[2] -= mAxis[0] * mLength[0];
	pos[2] -= mAxis[1] * mLength[1];
	pos[2] += mAxis[2] * mLength[2];

	pos[3] += mAxis[0] * mLength[0];
	pos[3] -= mAxis[1] * mLength[1];
	pos[3] += mAxis[2] * mLength[2];

	pos[4] += mAxis[0] * mLength[0];
	pos[4] += mAxis[1] * mLength[1];
	pos[4] -= mAxis[2] * mLength[2];

	pos[5] -= mAxis[0] * mLength[0];
	pos[5] += mAxis[1] * mLength[1];
	pos[5] -= mAxis[2] * mLength[2];

	pos[6] -= mAxis[0] * mLength[0];
	pos[6] -= mAxis[1] * mLength[1];
	pos[6] -= mAxis[2] * mLength[2];


	pos[7] += mAxis[0] * mLength[0];
	pos[7] -= mAxis[1] * mLength[1];
	pos[7] -= mAxis[2] * mLength[2];

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
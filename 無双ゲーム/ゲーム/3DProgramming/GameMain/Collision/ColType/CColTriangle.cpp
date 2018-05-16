#include "CColTriangle.h"
#include "../CCollisionManager.h"

int CColTriangle::mAllCount = 0;

/*�R���X�g���N�^ new����*/
CColTriangle::CColTriangle() {
	mType = COL_TRIANGLE;
	CCollisionManager::GetInstance()->Add(this);//�����蔻��ǉ�
}
/*�f�X�g���N�^*/
CColTriangle::~CColTriangle(){
	mAllCount--;
}

/*�R���X�g���N�^�@���_�����*/
CColTriangle::CColTriangle(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2) : CColTriangle()
{
	mAllCount++;//�J�E���g����
	mNumber = mAllCount;//�����̐����ԍ����߂�
	mPos = CVector3::TriangleCenter(v0, v1, v2);
	printf("�O�p�`�̒��S(%f, %f, %f)\n", mPos.x, mPos.y, mPos.z);
	/*�����̃|�W�V�������瓖���蔻�肷��*/

	mV[0] = v0;
	mV[1] = v1;
	mV[2] = v2;
}

/*�X�V*/
void CColTriangle::Update() {
	if (mpCombinedMatrix) {
		mV[0] = mV[0] * *mpCombinedMatrix;
		mV[1] = mV[1] * *mpCombinedMatrix;
		mV[2] = mV[2] * *mpCombinedMatrix;
	}
}

/*�����蔻����Ƃ�Ƃ��̂ݍX�V����*/
CColTriangle CColTriangle::GetUpdate() {
	CColTriangle ct = *this;
	ct.Update();
	return ct;
}


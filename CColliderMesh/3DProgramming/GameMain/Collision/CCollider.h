#ifndef CCOLLIDERBOX_H
#define CCOLLIDERBOX_H
#include "../Task/CTask.h"
//#include "CCollision.h"
#include "ColType/COBB.h"
#include "ColType/CColSphere.h"

/*�����蔻��N���X
eColTag���w�肵�`�����߂Ă���
*/
class CCollider :public CTask
{
private:
	/*�����蔻��*/
	CVector3 *mpPos;//�|�W�V���������p

	/*�����蔻��(�{�b�N�X�p)*/
	CVector3 mParentNextPos;//�{�b�N�X�̐e����̈ʒu
public:
	/*�����蔻��@�{�b�N�X*/
	COBB mObb;
	/*�����蔻�� ��*/
	CColSphere mColSphere;

	//�t���[���̍����s��
	CMatrix44 *mpCombinedMatrix;

	CCollider() : mpCombinedMatrix(0) {}

	CCollider(CTask::E_COL_TAG tag) : mpCombinedMatrix(0) {
			eColTag = tag;
	}

	//OBB�̃{�b�N�X�p�����[�^�ݒ�
	void SetBoxOBB(CVector3 &center, float length[], CMatrix44 *m);
	void SetBoxOBB(CVector3 &center, CVector3 &v, CMatrix44 *matrix);

	/*���̃p�����[�^�ݒ�*/
	void SetShere(float radius, CVector3 pos, CMatrix44 *m);

	/*�ǂ̃p�����[�^�[�ݒ� �ǂ̌����ƃ|�W�V����*/
	void SetWall(CVector3 normal, CVector3 *pos);

	/*�T�C�Y�A�b�v*/
	void SizeUP(float f);

	/*Obb����]������*/
	void SetObbRot(const CVector3 rot);
	/*Obb��傫��������*/
	void SetObbSize(float length[]);
	void SetObbSize(CVector3 &v);
	/*�F�ݒ�*/
	void SetColor(float cr, float cg, float cb, float ca);
	void Update();
	void Render();
	void Render(COBB *obb);
};

class CCollider2 : public CCollider
{
private:

protected:
	/*�����蔻��(�{�b�N�X�p)*/
	CVector3 mPositionFromParent;//�{�b�N�X�̐e����̈ʒu
	//�e����̈ʒu�̍s��
	CMatrix44 mMatrixFromParent;
	//���[���h���W�ϊ��s��
	CMatrix44 mMatrix;
public:
	//����01�A�O�p�`012�AOBB012 �J�v�Z��01
	CVector3 mV[2][3];
	//���a0�A���̒���012
	float mF[3];

	//�t���[���̍����s��
	CMatrix44 *mpCombinedMatrix;


	CCollider2() {}
	CCollider2(CTask::E_COL_TAG tag) : mpCombinedMatrix(0) {
		eColTag = tag;
	}

	void Update() {
		if (mpCombinedMatrix) {
			mMatrix = mMatrixFromParent * *mpCombinedMatrix;
		}
	}

	virtual void Render() {};

};

#endif
#ifndef CCOLLIDERBOX_H
#define CCOLLIDERBOX_H
#include "../Task/CTask.h"
#include "CCollision.h"

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
	CCollider(CTask::E_COL_TAG tag) : mpCombinedMatrix(0){
		eColTag = tag;
	}


	//OBB�̃{�b�N�X�p�����[�^�ݒ�
	void SetBoxOBB(CVector3 &center, CVector3 size, CMatrix44 *m);

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

	/*�F�ݒ�*/
	void SetColor(float cr, float cg, float cb, float ca);
	void Update();
	void Render();
	void Render(COBB *obb);


};

#endif

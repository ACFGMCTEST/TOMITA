#ifndef COL_BASE_H
#define COL_BASE_H

#include "../../Vector/CVector3.h"
#include "../../Matrix/CMatrix44.h"
#include "../../Task/CTask.h"

/*�����蔻��N���X�x�[�X*/
class CColBase : public CTask
{
public:
	CVector3 mParentNextPos;//�e���璲����������
	CVector3 mPos;		//���S���W
	float r, g, b, a;//�F���
	CVector3 mAdjust;	//�Փˉ����@�����l
	CTask *mpParent;	//�e�̃^�X�N
	CMatrix44 *mpCombinedMatrix;	//�t���[���̍����s��
	CColBase() : mpParent(0), mpCombinedMatrix(0) {}

	/*�F�ݒ�*/
	void SetColor(float cr, float cg, float cb, float ca){
		r = cr;
		g = cg;
		b = cb;
		a = ca;
	}
	/*�`�揈��*/
	virtual void Render() {};

};

#endif
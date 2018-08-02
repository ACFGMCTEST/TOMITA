#ifndef COL_BASE_H
#define COL_BASE_H

#include "../../Vector/CVector3.h"
#include "../../Matrix/CMatrix44.h"
#include "../../Task/CTask.h"

/*�����蔻��N���X�x�[�X*/
class CColBase : public CTask
{
protected:
	float r, g, b, a;//�F���
public:
	CTask * mpParent;	//�e�̃^�X�N
	CMatrix44 *mpCombinedMatrix;	//�t���[���̍����s��
	CVector3 mPos;		//���S���W
	CVector3 mAdjust;	//�Փˉ����@�����l

	/*�����蔻�葮���p*/
	enum E_STATE {
		NO,//�ݒ�Ȃ�
		PL_ATTACK,//�v���C���[�̃A�^�b�N
		PL_ATTACK_EFFECT3D,//3D�G�t�F�N�g�̓����蔻��
		PL_BODY,//�v���C���[�̃{�f�B
		ENE_BODY,//�G�l�~�[�̃A�^�b�N
	};
	E_STATE eState;

	CColBase() : mpParent(0), mpCombinedMatrix(0){}

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
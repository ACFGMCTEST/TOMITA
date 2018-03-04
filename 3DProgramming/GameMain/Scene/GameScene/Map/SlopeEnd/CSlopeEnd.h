
#ifndef SLOPE_END_HPP
#define SLOPE_END_HPP

#include "../Slope/CSlope.h"

/*��N���X*/
class CSlopeEnd : public CSlope{
public:

	CCollider *mpColRefLeft;//���̂�����͂�Ă�
	CCollider *mpColRefRight;//���̂�����͂�Ă�

	/*�f�o�b�N�p*/
	CVector3 SaveRot;

	//�[�p�}�g���b�N�X
	CMatrix44 mSideMatrix;

	/*�����蔻�菉���� �E ����:��]�l*/
	void ColInitRight();
	/*�����蔻�菉���� �� ����:��]�l*/
	void ColInitLeft();

	/*�����蔻��̏����� �����ɂ���ĕς���*/
	void ColInit(ESlpoeRot eState);
	/*�R���X�g���N�^
	pos = �ʒu
	x , y = �����̃}�b�v����W�l*/
	CSlopeEnd(CVector3 pos, int x, int z);

	void SlopeEndInit();

	void Update();

	void Render();
};

#endif
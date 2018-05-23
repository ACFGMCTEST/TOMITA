/*
*�^�X�N�̃v���O����
*�S���� �y�c���l
*/
#ifndef TASK_HPP
#define TASK_HPP
#include <stdio.h>
#include <assert.h>

class CColBase;

class  CTask
{
public:

	int mNumber;//�����̐����ԍ�
	CTask *mpNext;
	CTask *mpPrev;

	bool mKillFlag;  //�t���O�������Ă�����̂�����
	bool mCharaFlag; //�L�����N�^�[�̃t���O�������Ă�����̂ɂ�Col����

	CTask *mpParent;//�e ��������^�X�N��̂��̂ɃA�N�Z�X���Ă���
	float mValue; //���݂g�o


	//�v���C���[�̏�Ԓl
	enum ESTATE {
		E_IDLING,		//����
		E_RUN,		//����
		E_ATTACK,	//�U��
		E_RUN_ATTACK,//�ړ��U��
		E_JUMP,	    //�W�����v
		E_DMGM,		//�_���[�W
		E_STATE_ARRAY//�X�e�[�^�X�̏��
	};
	ESTATE mState;	//�v���C���[�̏��

	//���҂����f
	enum E_NAME{
		E_PLAYER,
		E_SLIME,
	};
	E_NAME eName;//�l�[��

	/*�����蔻��̑���*/
	enum EType {
		COL_TRIANGLE,	//�O�p�`�R���C�_
		COL_BOX,//�{�b�N�X
		COL_SPHEPE,//��
		COL_CAPSULE		//�J�v�Z���R���C�_
	};
	EType mType;


	CTask();
	virtual ~CTask();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void BillboardRender();//billboard������́@�����菇�Ō����Ȃ��Ȃ���̂�����̂ŕ�����
	virtual bool Collision(CColBase* p1, CColBase* p2) { return false; };

};


#endif

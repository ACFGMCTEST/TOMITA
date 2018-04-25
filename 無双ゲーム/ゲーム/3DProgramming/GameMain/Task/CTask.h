/*
*�^�X�N�̃v���O����
*�S���� �y�c���l
*/
#ifndef TASK_HPP
#define TASK_HPP
#include <stdio.h>
#include <assert.h>

class  CTask
{
public:

	CTask *mpNext;
	CTask *mpPrev;

	bool mKillFlag;  //�t���O�������Ă�����̂�����
	bool mCharaFlag; //�L�����N�^�[�̃t���O�������Ă�����̂ɂ�Col����

	CTask *mpParent;//�e ��������^�X�N��̂��̂ɃA�N�Z�X���Ă���
	float mValue; //���݂g�o

	int mCount; //�����ԍ�

	//�v���C���[�̏�Ԓl
	enum ESTATE {
		E_IDLING,		//����
		E_RUN,		//����
		E_ATTACK_RUN,		//�U�����߂Ȃ��瑖��
		E_ATTACK_INIT,	//�U�����߂ɓ���
		E_ATTACK,	//�U��
		E_ATTACK_IDLING,	//�U������
		E_JUMP,	    //�W�����v
		E_ATTACK_JUMP,//�A�^�b�N�W�����v
		E_DMGM,		//�_���[�W
		E_STATE_ARRAY//�X�e�[�^�X�̏��
	};
	ESTATE mState;	//�v���C���[�̏��


	/*����*/
	enum E_TAG{
		E_TAG_NO,				//�����l
		E_TAG_CAMERA,			//�J����
		E_TAG_PLAYER,			//�v���C���[
		E_TAG_WEAPON,			//�U���͈�
		E_TAG_ATTACK_INIT_RANGE,//�U�������͈� �G�l�~�[�p
		E_TAG_ATTACK_RANGE,		//�U���͈� �G�l�~�[�p
		E_TAG_ENEMY,			//�G�l�~�[
		E_TAG_GROUND,			//�n��

		E_TAG_WALL,				//�E�H�[
	};
	E_TAG eTag = E_TAG_NO;//�����蔻��̏���
	/*����*/
	enum E_PRIORITY{
		E_NO,				//�����l
		E_PLAYER,			//�v���C���[
		E_WEAPON,			//�U���͈�
		E_ATTACK_INIT_RANGE,//�U�������͈� �G�l�~�[�p
		E_ATTACK_RANGE,		//�U���͈� �G�l�~�[�p
		E_GROUND,			//�n��
		E_ENEMY,			//�G�l�~�[
	};
	E_PRIORITY ePriority;//�����_�[�̏���

	/*�����蔻��̌`*/
	enum  E_COL_TAG
	{
		E_COL_NO,
		E_COL_WALL,//��
		E_COL_BOX,//�{�b�N�X
		E_COL_SPHEPE,//��
	};
	E_COL_TAG eColTag;

	bool mUiFlag; //UI�����邩���f

	CTask();
	virtual ~CTask();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void BillboardRender();//billboard������́@�����菇�Ō����Ȃ��Ȃ���̂�����̂ŕ�����

};
static CTask::ESTATE ReferenceState;	//�A�j���[�V�����Q�Ɨp swich���Ŋy���邽�߂Ɏg��


#endif

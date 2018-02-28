#ifndef CXPuck_H
#define CXPuck_H

#include "../../../Vector/CVector3.h"
#include "../../../Collision/CCollider.h"
#include "../Map/Slope/CSlope.h"

//#include "CBillBoard.h"
#include "../../../Graphic/CModelX.h"

/*�L�����X�e�[�^�X*/

/*�������*/
#define KNOCK_BACK  0.2f/*������т̓x����*/

/*�i�ޕ��p*/
#define FORWARD 0.0f,0.0f,1.0f
#define FORWARD_SLOPE 0.0f,0.5f,0.5f//��ɏ��Ƃ�


/*�S�[���|�W�V����*/
#define GOAL_POS_Z 20.0f//�^�񒆂��ƃ��X�L������������̂ŏ������炷
#define GOAL_POS_PUCK_PLAYER CVector3(0.0f,30.0f,-GOAL_POS_Z)
#define GOAL_POS_PUCK_ENEMY  CVector3(0.0f,30.0f,GOAL_POS_Z)
/*
CXPuck
�p�b�N�N���X
*/
class CXPuck : public CModelXS {
private:
	float mGravitTime;//�d�͂̎���
	bool mFlagJump;//�W�����v�������f�p
	CVector3 mRefrectVec;//���˕Ԃ����
public:
	bool mFlagSlope;//��
	bool mGoalStandUpFlag;//�S�[���������̃t���O
	float mSaveSpeed; //�����@�ۑ��p
	float mVelocity; //���� �g������
	CVector3 mForward;//�i�ތ���
	CVector4 fortank; //�����������Ă������
	CVector3 mPosition;	//�ʒu
	CVector3 mRotation;	//��]

	CCollider *mpCBSphere;//�����蔻��(����)
	CCollider *mpCBRefBox;//�����蔻��(box)���˕Ԃ蔻�f�p

	bool mRefFlag;//���˂����邩��flag

	CXPuck();

	/*�����蔻�菉����*/
	void ColInit();
	//����������
	void Init(CModelX *model);
	//�X�V����
	void Update();
	//�`�揈��
	void Render();

	void PosUpdate();//�|�W�V�����̕ύX�֐��@
	/*�ړ�����*/
	void Move();


	/*���˕Ԃ� obb����*/
	void ColReflect(const COBB &col);

	/*���˕Ԃ�����w��
	rot ��]�n
	*/
	void ColReflect(CVector3 &rot,float &power);
	/*���������Ƃ��������~�߂�*/
	void ColStop(const COBB &obb1, const COBB &obb2);//����̂����蔻��
	/*��������*/
	void ColSlow();
	/*��������*/
	void ColFast();
	
	/*�W�����v����*/
	void Jump();
	/*�W�����v���� Jump�̃t���O�𗧂Ă�*/
	void EnabledJump();
	/*��ɂ����������̃t���O���ď���*/
	void  EnabledSlope();

	/*�S�[���G�l�~�[*/
	void GoalEnemy();
	/*�S�[���v���C���[*/
	void GoalPlayer();
	/*�|�W�V�������グ�鏈��*/
	void StandUp();

	/*�n�ʂɓ����������̔���*/
	void ColGround();

	/*�d��*/
	void Gravity();
	/*���삷��ꍇ*/
	void MyMove();
	/*�ȈՈړ��t���O�֐�*/
	bool FlagMove();

	/*�����蔻��Ăяo��
	���̏ꏊ�ɖ߂����߂̊֐�
	*/
	void Collision(const COBB &box, const CColSphere &sphere);


	/*��]�l���Z�b�g*/
	void RotReset();
};

#endif

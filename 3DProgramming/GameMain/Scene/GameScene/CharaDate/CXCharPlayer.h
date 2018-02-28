#ifndef CXCHARPLAYER_H
#define CXCHARPLAYER_H

#include "CXCharacter.h"
#include "../../../Vector/CVector3.h"
#include "../../../Collision/CCollider.h"
#include "../Effect/CEffect2D.h"
#include "../../../Key/CKey.h"
#include "../../../Graphic/CModelX.h"
#include "../Map/Slope/CSlope.h"
//�v���C���[�̐�
#define CHARA_ARRAY 3
/*�L�����X�e�[�^�X*/
/*�i�ރX�s�[�h*/
#define SPEED_RUN 0.35f //����
#define SPEED_RUN_SKILL 0.6f //�X�L�����̑��s�X�s�[�h

#define SPEED_ATTACK_RUN SPEED_RUN*0.8f //���ߑ���
#define SPEED_JUMP_DOWN 0.05f //�W�����v����velocty���}�C�i�X����
#define SPEED_ATTACK_RUN_SKILL 0.4 //�X�L���������̈ړ����x

#define SKILL_TIME_LIMIT 1200.0f

/*������΂���*/
#define ATTACK_POWER 0.02f
#define ATTACK_POWER_MAX 0.5f		//�f�t�H���g

#define ATTACK_W0_POWER_MAX	0.65f	//���펖�̍U����
#define ATTACK_WS0_POWER_MAX 1.3f	//���펖�̍U����
#define ATTACK_W1_POWER_MAX 0.6f
#define ATTACK_W2_POWER_MAX 1.11f
#define ATTACK_W3_POWER_MAX 0.55f

#define POWER_UP 0.001f//�U���̂����蕝
#define W_0_POWER_UP 0.0013f
#define W_1_POWER_UP 0.0012f
#define WS_1_POWER_UP 0.01f
#define W_2_POWER_UP 0.00222f
#define W_3_POWER_UP 0.0011f

/*�������*/
#define KNOCK_BACK  0.2f/*������т̓x����*/
/*�J�E���g�*/
#define KNOCK_BACK_SMALL (int)1 * 5 
#define KNOCK_BACK_MIDDLE (int)4 * 5
#define KNOCK_BACK_BIG (int)6 * 5
/*POINT�̊��Z�*/
#define POINT_MAX 50 //�T�O�܂�
#define POINT_UP 0.1f //���ߎ�^�ȊO
#define POINT_UP_BIG 0.1f * 1.5f  //���ߎ�^�p
/*�i�ޕ��p*/
#define FORWARD 0.0f,0.0f,1.0f
/*
 CXCharPlayer
 �v���C���[�N���X
*/
//class CXCharPlayer : public CXCharacter {
class CXCharPlayer : public CModelXS {
private:
	int mRotCount;//��]�n�J�E���g�@�ړ�����Ƃ��Ɏg��
	CKey AttackInitKey;//Init���Ɏg��
public:
	float mGravitTime;//�d�͂̎���
	float mVelocity; //���� �g������
	float mPower;//�U����
	bool mFlagKnockback;//�m�b�N�o�b�N�������f
	bool mFlagJump;//�W�����v�t���O
	bool mFlagSlpoe;//����ɓ������Ă��邩���f


	const float mGageDecrease = 0.17f;//�X�L���Q�[�W�̂P�t���[�����̌������x
	const float mGageLimit=200.0f;	//�X�L���Q�[�W�̃��~�b�g�s���������̂Ŏ��Ԑ�������˂�

	float mSkillTime;//�X�L���̔�������

	CVector3 mForward;//�i�ތ���
	CVector4 fortank; //�����������Ă������

	CVector3 mPosition;	//�ʒu
	CVector3 mPrevPos; //�O�̈ʒu�ۑ��ꏊ 

	CVector3 mRotation;	//��]
	/*����*/
	enum E_DIRECTION{
	E_RIGHT,
	E_LEFT,
	E_TOP,
	E_BOTTOM
	};
	E_DIRECTION eDirection;//���݂̕���
	bool DirectionAnima();//�����̐��� �A�j���[�V�������I���܂ňړ����Ȃ�
	//25
	//�Փ˔���i�́j
	//CCollider *mCBBody;
	CCollider *mpCBBody;//������
	CCollider *mpCBLeg;//��
	//�Փ˔���i����j
	CCollider *mpCBWeapon;
	/*�n���}�[��EFFECT*/
	CEffect2D mHammerEffect;

	CXCharPlayer();
	//����������
	void Init(CModelX *model);
	/*�����蔻�菉����*/
	void ColInit();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//billboard�̕`�揈��
	void BillboardRender();
	/*���E�܂�*/
	bool FlagRight();
	/*��]�֐�
	rot = ��]�l*/
	void PlusRot(float rot);
	void PosUpdate();//�|�W�V�����̕ύX�֐��@
	int mCountKnockBack; //�m�b�N�o�b�N�����

	/*���������Ƃ��ɌĂяo��
	count:�ړ���
	Forward:�i�ޕ��p
	*/
	void ColMove(int count, CVector3 Foward);

	/*���삷��ꍇ*/
	void MyMove();
	/*�ȈՈړ��t���O�֐�*/
	bool FlagMove();
	bool FlagLeft();
	/*��]����܂ňړ����Ȃ�*/
	bool FlagRotMove(int angle);
	/*�ȈՃA�j���[�V�����؂�ւ�*/
	void AnimaState(ESTATE state);

	/*�o�H�T���@�|�W�V�������Ƃ�悤*/
	CVector4 *mGoPos; //�������|�W�V���� new���ĕۑ�
	int mGoPosSize; //�Ō�܂ł̔z��ۑ�
	int mGoCount;//�ǂ��ɍs���J�E���g �Ō�̔z�񂩂�0�Ɍ������Ă���
	/*POS�����̃}�g���b�N�X�A�b�v�f�[�g*/
	void MatrixUpdate();


	/*�A�^�b�N�̃X�e�[�^�X �U�������f*/
	bool FlagAttackState();
	/*��������֐�*/
	void MoveSpeed();
	/*�������Ƃ��̏���
	forward = �����ݒ�
	velocity = ��
	*/
	void Move(const CVector3 &forward,float velocity);


	/*�o�H�T���@���ؗp
	x,z =�@���̍��W�l
	count = ���߂Ɏg���Ƃ�0������
	CostMap = cost���i�[����}�b�v������
	FastFlag = ���߂Ɏg���Ƃ���true������
	*/
	void CostMapping(int x, int z, int count,int *CostMap, bool FastFlag);

	/*
	�o�H�T���@�S�[�����玩���̏ꏊ��
	x,z = ���W�l
	count = ���߂Ɏg���Ƃ�0������
	Arraysize = �z�񐔂��i�[����
	CostMap  = cost���i�[���ꂽ�}�b�v�f�[�^������
	pos = �i�[����|�W�V�����@new�@����
	FastFlag = ���߂Ɏg���Ƃ�true�ɂ���
	*/
	void SearchGoPos(int x, int z, int count, int *Arrysize,const int CostMap[], CVector4 **Pos, bool FastFlag);

	/*�T�������̏�����*/
	void SearchGoPosInit();


	/*�����蔻��Ăяo��
	���̏ꏊ�ɖ߂����߂̊֐�
	*/
	void Collision(const COBB &box, const CColSphere &sphere);

	/*�n���}�[�̗��߂鏈��*/
	void HammerUp();
	/*Hammer�̏���������*/
	void HammerInit();
	/*�d��
	�����̑������Ă���Ƃ����d�͂��~�߂�ꏊ�ɂ���
	*/
	void Gravity();

	/*�W�����v�֐�
	�����蔻��̎d�l
	�����̓����蔻��ɓ����Ă���
	�n�ʂɈ�ԋ߂�

	�����������瓖���蔻�肪���܂����Ɠ����Ă��ꂢ�Ɏ~�܂��Ă��邩��
	�K�N�u�����ۂ��Ȃ���΂��Ȃ��Ă����񂾂���
	*/
	void Jump();
	/*�O���E���h�̐ݒ�*/
	void ColGround();

	/*��ɓ����������̔���*/
	void ColSlope();
};

#endif

#ifndef CXCHARPLAYER_H
#define CXCHARPLAYER_H

#include "../../../../Graphic/CModelX.h"
#include "../../../../Vector/CVector3.h"
#include "../../Effect/CEffect2D.h"
#include "../../../../Key/CKey.h"
#include"../../../../../StateMachine/CStateMachine.h"
#include "../../../../../StateMachine/CStateBase.h"
#include "../../../../Collision/ColType/CColBase.h"
#include "../../../../Collision/ColType/CColCapsule.h"
//�v���C���[�̐�
#define CHARA_ARRAY 3
/*�L�����X�e�[�^�X*/
/*�i�ރX�s�[�h*/
#define SPEED_RUN 0.2f //MAX����
#define SPEED_RUN_ACC(v) if (SPEED_RUN > v){v += SPEED_RUN* 0.1f; }else{v = SPEED_RUN;}//�����x�v�Z����ɗ����ꍇ

#define SPEED_ATTACK_RUN SPEED_RUN*0.8f //���ߑ���
#define SPEED_JUMP_DOWN 0.05f			//�W�����v����velocty���}�C�i�X����
#define SPEED_ATTACK_RUN_SKILL 0.4		//�X�L���������̈ړ����x

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
protected:
	/*�X�e�[�^�X�Ǘ��}�l�[�W���[*/
	std::unique_ptr<CStateMachine> mStateMachine;//�X�e�[�^�X�Ǘ�
private:

	int mRotCount;//��]�n�J�E���g�@�ړ�����Ƃ��Ɏg��
	CKey AttackInitKey;//Init���Ɏg��
	
public:
	CMatrix44 *mpMatrix;//�����蔻��̌��_
	float mGravitTime;//�d�͂̎���
	float mVelocity; //���� �g������
	float mPower;//�U����
	bool mFlagKnockback;//�m�b�N�o�b�N�������f
	bool mFlagJump;//�W�����v�t���O

	CVector3 mForward;//�i�ތ���
	CVector4 fortank; //�����������Ă������

	CVector3 mPosition;	//�ʒu
	CVector3 mPrevPos; //�O�̈ʒu�ۑ��ꏊ 

	CVector3 mRotation;	//��]
	CXCharPlayer();
	//����������
	void Init(CModelX *model);
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//billboard�̕`�揈��
	void BillboardRender();

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

	/*��]����܂ňړ����Ȃ�*/
	//bool FlagRotMove(int angle);

	/*POS�����̃}�g���b�N�X�A�b�v�f�[�g*/
	void MatrixUpdate();

	/*�ړ�������*/
	void Move();

	/*�����蔻�蒲���p*/
	void SetAdjust(CVector3 *s, const CVector3 &t);
	/*�����蔻��*/
	bool Collision(CColBase* me, CColBase* you);
	/*�J�v�Z���������蔻��*/
	void CapsuleCol(CColCapsule *caps, CColBase* y);


	/*�d��
	�����̑������Ă���Ƃ����d�͂��~�߂�ꏊ�ɂ���
	*/
	void Gravity();
	/*�O���E���h�̐ݒ�*/
	void ColGround();

	/*�L�����N�^�[�������̉�]
	float = ������������
	*/
	int MoveRotation(int  angle);

	CVector3 mAdjust;


	/*���삷���]�l�v�Z*/
	void PlayerMoveRot();
};

#endif

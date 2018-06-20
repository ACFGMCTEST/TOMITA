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
#include "../../../../Collision/ColType/CColSphere.h"
#include "../../../../Graphic/CHpBar2D.h"
//�v���C���[�̐�
#define CHARA_ARRAY 3
/*�L�����X�e�[�^�X*/
/*�i�ރX�s�[�h*/
#define SPEED_RUN 0.4f //MAX����
#define SPEED_RUN_ACC(v) if (SPEED_RUN > v){v += SPEED_RUN* 0.1f; }else{v = SPEED_RUN;}//�����x�v�Z����ɗ����ꍇ

/*�U����*/
#define ATTACK_POWER 4.0f

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
CPlayer
�v���C���[�N���X
*/
class CPlayer : public CModelXS {
protected:
	/*�X�e�[�^�X�Ǘ��}�l�[�W���[*/
	std::unique_ptr<CStateMachine> mStateMachine;//�X�e�[�^�X�Ǘ�
	CVector3 mDamageRot;//�_���[�W���󂯂���]�l
	float mDamagePower;//������Ԓl
private:
	CEffect2D *mpHitEffect;//�U�����̃G�t�F�N�g
	CHpBar2D *mpHp;//hp
	CKey AttackInitKey;//Init���Ɏg��
	int mRotCount;//��]�n�J�E���g�@�ړ�����Ƃ��Ɏg��
public:
	bool mFlagDamage;//�_���[�W���̃t��
	bool mFlagAttack;//�U������t���O
	std::string mStr;//���݂̏��
	//�v���C���[�̏�Ԓl
	enum E_STATE {
		E_IDLING,		//����
		E_RUN,		//����
		E_ATTACK,	//�U��
		E_RUN_ATTACK,//�ړ��U��
		E_JUMP,	    //�W�����v
		E_DAMAGE,		//�_���[�W
		E_AVOID,		//���
		E_STATE_ARRAY//�X�e�[�^�X�̏��
	};

	CMatrix44 *mpMatrix;//�����蔻��̌��_

	CVector3 mForward;//�i�ތ���
	CVector3 mPosition;	//�ʒu
	CVector3 mRotation;	//��]


	float mGravitTime;//�d�͂̎���
	float mVelocity; //���� �g������
	float mPower;//�U����

	bool mFlagJump;//�W�����v�t���O

	CPlayer();
	~CPlayer();
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
	/*�ʃo�[�W����*/
	void Collision(CColSphere *youSphere,CColSphere *sphere);
	/*���̓��̓����蔻��*/
	void SphereCol(CColSphere *sphere, CColBase *y);

	/*�J�v�Z���̈ړ�*/
	//void ColCapsAdjus(CColCapsule *youCaps, CColCapsule *caps);

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

	/*���݂�str�����*/
	void State(std::string s);

	/*������Ԕ���:*/
	void BlowOff();
	/*�_���[�W���󂯂����̏���*/
	void Damage(float power, CVector3 rot);
};

#endif

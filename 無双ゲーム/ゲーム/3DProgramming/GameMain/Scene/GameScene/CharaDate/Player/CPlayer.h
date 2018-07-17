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
#include "../../../../Graphic/CBillBoard.h"
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

/*�X�e�[�^�X*/
#include "Attack\CPlayerAttack.h"
#include "Idling\CPlayeridling.h"
#include "Jump\CPlayerJump.h"
#include "Run\CPlayerRun.h"
#include "RunAttack\CPlayerRunAttack.h"
#include "Damage\CPlayerDamage.h"
#include "Died\CPlayerDied.h"
#include "Avoid\CPlayerAvoid.h"


/*�����蔻��̐ݒ�l*/
#define COL_RADIUS 1.0f
#define COL_POS CVector3(0.0f, 1.0f, 0.0f), CVector3(0.0f, 0.0f, 0.0f)
#define COL_SPHE_POS CVector3(0.0f, 0.0f, 0.0f)
#define COL_BONE(string) &mpCombinedMatrix[model->FindFrame(string)->mIndex]

/*�v���C���[*/
#define MODEL_FILE_UNITY		MODEL_FILE"SDUnity\\SDUnityBoxing.x"
/*�A�j���[�V�����̃t�@�C���ꏊ*/
#define F_PL_IDLING				MODEL_FILE"SDUnity\\Anima\\Idling.x"
#define F_PL_RUN				MODEL_FILE"SDUnity\\Anima\\Run.x"
#define F_PL_RUN_ATTACK			MODEL_FILE"SDUnity\\Anima\\powerRunAttack.x"
#define F_PL_ATTACK				MODEL_FILE"SDUnity\\Anima\\Attack2.x"
#define F_PL_JUMP				MODEL_FILE"SDUnity\\Anima\\Jump.x"
#define F_PL_DAMAGE				MODEL_FILE"SDUnity\\Anima\\Damage.x"
#define F_PL_DIED			    MODEL_FILE"SDUnity\\Anima\\Died.x"
#define F_PL_AVOID				MODEL_FILE"SDUnity\\Anima\\Avoid.x"
/*
CPlayer
�v���C���[�N���X
*/
class CPlayer : public CModelXS {
protected:
	CStateMachine mStateMachine;//�X�e�[�^�X�Ǘ�
	CVector3 mDamageRot;//�_���[�W���󂯂���]�l
	float mDamagePower;//������Ԓl
	CBillBoard *mpMiniRect;//�~�j�}�b�v�p
	/*�~�j�}�b�v�ݒ�p*/
	void SetMiniMap();
private:
	CEffect2D *mpHitEffect;//�U�����̃G�t�F�N�g
	CHpBar2D *mpHp;//hp


	CKey AttackInitKey;//Init���Ɏg��
	int mRotCount;//��]�n�J�E���g�@�ړ�����Ƃ��Ɏg��
public:
	


	bool mFlagDamage;//�_���[�W���̃t��
	bool mFlagAttack;//�U������t���O
	std::string mStr;//���݂̏��

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


	/*������ԗ� ������ԗ͂ƌ��݂̈ړ��ʂŌv�Z����*/
	void BlowSpeed();
	/*������Ԕ���:*/
	void BlowOff();
	/*�_���[�W���󂯂����̏���*/
	void Damage(float power, CVector3 rot);


	/*�̗̓Q�[�W��Hp�擾*/
	float HP() { return mpHp->mValue;}

};

#endif

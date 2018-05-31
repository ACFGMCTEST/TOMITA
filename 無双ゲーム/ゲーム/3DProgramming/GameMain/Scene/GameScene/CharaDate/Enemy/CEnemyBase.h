#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "../Player/CXCharPlayer.h"
#include"../../../../Graphic/CHpBar.h"

/*�G�l�~�[�̃N���X*/
class CEnemyBase : public CXCharPlayer{
protected:
	CHpBar * mpHp;//HP�o�[
	CTexture mTexmFrame;//Hp�̃e�N�X�`��
	CTexture mTexGauge; //Hp�̃e�N�X�`��
	CVector3 mDamageRot;//�_���[�W���󂯂���]�l
	float mDamagePower;//������Ԓl
public:
	bool mFlagDamage;//�_���[�W���̃t���O
	CEnemyBase();
	
	/*����������*/
	void Init(CModelX *model);
	/*�X�V*/
	void Update();
	/*�`��*/
	void  Render();
	/*�U������ �����蔻�蕔���ŌĂ�*/
	void AttackInit();
	/*�����蔻��*/
	bool Collision(CColBase* me, CColBase* you);
	/*�J�v�Z���������蔻��*/
	void CapsuleCol(CColCapsule *caps, CColBase* y);
	/*AI�̓����֐�*/
	void AIMove();
	/*�_���[�W���󂯂����̏���*/
	void Damage(float power, CVector3 rot);
	/*������Ԕ���:�����@��ԕ����w��*/
	void BlowOff();

};
#endif

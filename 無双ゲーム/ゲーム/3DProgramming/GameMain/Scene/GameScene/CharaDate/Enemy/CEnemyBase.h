#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "../Player/CPlayer.h"
#include"../../../../Graphic/CHpBar.h"
#include "../../Effect/CExplosion.h"

/*�G�l�~�[�̃N���X*/
class CEnemyBase : public CPlayer{
protected:
	CHpBar     *mpHp;//HP�o�[
	/*hp�ݒ�@ajust*/
	void SetHpBar(float hp,CVector3 ajust);
	/*�����ݒ�*/
	void SetExp();

public:
	bool mFlagBlowDamage;//�������ł���Ƃ��A�����ă_���[�W��^���邩���f
	CExplosion * mpExplosion;//�����G�t�F�N�g(���S���̉��o)
	bool mFlagUpdate;//�A�b�v�f�[�g���邩���Ȃ���
	CEnemyBase();
	~CEnemyBase();


	/*����������*/
	void Init();
	/*�X�V*/
	void Update();
	/*�`��*/
	void Render();
	

	/*�U������ �����蔻�蕔���ŌĂ�*/
	void AttackInit();

	/*���̓������蔻�� ������*/
	void SphereCol(CColSphere *m, CColBase* y);
	/*AI�̓����֐�*/
	void AIMove();
	/*�_���[�W���󂯂����̏���*/
	float Damage(float power, CVector3 rot);
	/*�̗̓Q�[�W��Hp�擾*/
	float HP() { return mpHp->mValue; }	
};
#endif

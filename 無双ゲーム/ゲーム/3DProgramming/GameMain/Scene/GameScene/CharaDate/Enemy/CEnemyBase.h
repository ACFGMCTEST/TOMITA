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
	void SetHpBar(CVector3 ajust);
	/*�����ݒ�*/
	void SetExp();
public:
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
	/*�����蔻��*/
	bool Collision(CColBase* me, CColBase* you);
	/*�J�v�Z���������蔻��*/
	void CapsuleCol(CColCapsule *caps, CColBase* y);
	/*���̓������蔻�� ������*/
	void SphereCol(CColSphere *m, CColBase* y);
	/*AI�̓����֐�*/
	void AIMove();
	/*�_���[�W���󂯂����̏���*/
	void Damage(float power, CVector3 rot);

	/*�̗̓Q�[�W��Hp�擾*/
	float HP() { return mpHp->mValue; }
};
#endif

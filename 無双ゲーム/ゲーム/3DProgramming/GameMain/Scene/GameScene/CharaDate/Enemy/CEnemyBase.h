#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "../Player/CXCharPlayer.h"
#include"../../../../Graphic/CHpBar.h"

/*�G�l�~�[�̃N���X*/
class CEnemyBase : public CXCharPlayer{
public:
	CTexture mTexmFrame; //Hp�̃e�N�X�`��
	CTexture mTexGauge; //Hp�̃e�N�X�`��
	CHpBar mHp;//HP�o�[


	CEnemyBase();
	/*����������*/
	void Init(CModelX *model);
	/*AI�̓����֐�*/
	void AIMove();
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
	/*�_���[�W���󂯂����̏���*/
	void Damage(float power);

};
#endif

#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "../Player/CXCharPlayer.h"

/*�G�l�~�[�̃N���X*/
class CEnemyBase : public CXCharPlayer{
public:
	
	CEnemyBase();

	/*����������*/
	void Init(CModelX *model);
	/*AI�̓����֐�*/
	void AIMove();
	/*�X�V*/
	void Update();
	/*�U������ �����蔻�蕔���ŌĂ�*/
	void AttackInit();

};
#endif

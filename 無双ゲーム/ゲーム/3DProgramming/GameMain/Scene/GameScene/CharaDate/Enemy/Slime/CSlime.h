#ifndef SLIME_H
#define SLIME_H
#include "../CEnemyBase.h"

/*�G�l�~�[�̃N���X*/
class CSlime : public CEnemyBase{
private:
public:
	CSlime();
	/*����������*/
	void Init(CModelX *model);
	/*�X�V*/
	void Update();
	/*�`��*/
	void Render();
};
#endif

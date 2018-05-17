#ifndef SLIME_H
#define SLIME_H
#include "../CEnemyBase.h"

/*�G�l�~�[�̃N���X*/
class CSlime : public CEnemyBase{
private:
	static int mAllCount;//�G�l�~�[�̐�
public:
	int mNumber;//�����̐����ԍ�
	CSlime();
	~CSlime();
	/*����������*/
	void Init(CModelX *model);
	

	/*�X�V*/
	void Update();
	/*�`��*/
	void Render();
	/*���G�֐�*/
	bool Search();
};
#endif

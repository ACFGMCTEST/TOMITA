#ifndef SLIME_H
#define SLIME_H
#include "../CEnemyBase.h"
/*�����蔻��*/
#include "../../../../../Collision/ColType/CColSphere.h"
#include "../../../../../Collision/ColType/CColCapsule.h"

/*�G�l�~�[�̃N���X*/
class CSlime : public CEnemyBase{
private:
	static int mAllCount;//�G�l�~�[�̐�
	/*�����蔻��*/
	CColCapsule *mpCaps;//�J�v�Z������
	CColSphere  *mpSphere;//���̓���
	
public:
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
	/*���̔���*/
	void SphereCol(CColSphere *sphere, CColBase *y);
};
#endif

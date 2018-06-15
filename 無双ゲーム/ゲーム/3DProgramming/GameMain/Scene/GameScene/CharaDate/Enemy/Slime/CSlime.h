#ifndef SLIME_H
#define SLIME_H
#include "../CEnemyBase.h"
/*�����蔻��*/
#include "../../../../../Collision/ColType/CColSphere.h"
#include "../../../../../Collision/ColType/CColCapsule.h"

/*�G�l�~�[�̃N���X*/
class CSlime : public CEnemyBase{
protected:
	/*�����蔻��*/
	CColCapsule * mpCaps;//�J�v�Z������
	CColSphere  *mpSphere;//���̓���
private:
	static int mAllCount;//�G�l�~�[�̐�
public:
	enum E_STATE {
		E_IDLING,		//����
		E_RUN,			//����
		E_DAMAGE,		//�_���[�W
		E_ATTACK,		//�A�^�b�N
		E_STATE_ARRAY//�X�e�[�^�X�̏��
	};

	CSlime();
	~CSlime();
	/*�폜*/
	void Delete();
	/*����������*/
	void Init(CModelX *model);

	/*�X�V*/
	void Update();
	/*�`��*/
	void Render();
	/*���G�֐�*/
	bool Search();
	/*�U���͈�*/
	bool AttackRange();
	/*���̔���*/
	void SphereCol(CColSphere *sphere, CColBase *y);
};
#endif

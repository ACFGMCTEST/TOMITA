#ifndef SLIME_H
#define SLIME_H
#include "../CEnemyBase.h"
/*�����蔻��*/
#include "../../../../../Collision/ColType/CColSphere.h"
#include "../../../../../Collision/ColType/CColCapsule.h"

/*�G�l�~�[*/
/*�X���C��*/
#define MODEL_FILE_SLIME		MODEL_FILE"Slime\\Slime.x"//�X���C��	
#define SLIME_MAX 5//�X���C���̐�
#define SLIME_POS(i) CVector3(i * SLIME_MAX + 10,POS_Y,i * SLIME_MAX + 10)//�X���C���̐�
/*�A�j���[�V�����̃t�@�C���ꏊ*/
#define F_SLI_IDLING			MODEL_FILE"Slime\\Anima\\Idling.x"
#define F_SLI_RUN				MODEL_FILE"Slime\\Anima\\Run.x"
#define F_SLI_DAMAGE			MODEL_FILE"Slime\\Anima\\Damage.x"
#define F_SLI_ATTACK			MODEL_FILE"Slime\\Anima\\Attack.x"


/*�L���O�X���C��*/
#define KING_MODEL_FILE_SLIME		MODEL_FILE"Slime\\King\\KingSlime.x"//�X���C��	
/*�A�j���[�V�����̃t�@�C���ꏊ*/
#define F_SLI_KING_IDLING			MODEL_FILE"Slime\\King\\Anima\\Idling.x"
#define F_SLI_KING_RUN				MODEL_FILE"Slime\\King\\Anima\\Run.x"
#define F_SLI_KING_DAMAGE			MODEL_FILE"Slime\\King\\Anima\\Damage.x"
#define F_SLI_KING_ATTACK			MODEL_FILE"Slime\\King\\Anima\\Attack.x"

/*�G�l�~�[�̃N���X*/
class CSlime : public CEnemyBase{
protected:
	/*�����蔻��*/
	CColCapsule * mpCaps;//�J�v�Z������
	CColSphere  *mpSphere;//���̓���
private:
	static int mAllCount;//�G�l�~�[�̐�
public:

	CSlime();
	~CSlime();
	/*�폜*/
	void Delete();
	/*�X�e�[�^�X������ King�X���C�����������̂��悤*/
	void StateInit();
	/*�X���C���̏�����*/
	void SlimeInit(CModelX *model);
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

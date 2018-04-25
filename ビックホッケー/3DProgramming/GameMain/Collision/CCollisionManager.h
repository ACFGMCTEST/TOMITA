#ifndef CCOLLISIONMANAGER_HPP
#define CCOLLISIONMANAGER_HPP
#include "CCollider.h"
#include "../Task/CTaskManager.h"
#include "CCollider.h"
#include "../Sound/CSound.h"

/*���ׂĂ̓����蔻��Ǘ�*/
class CCollisionManager : public CTaskManager{
private:

	CSound mSEAttack;//�U�����̉�
	CSound mSEReflect;//���˕Ԃ�̉�
	CSound mSEGoal;//�S�[���̉�
	CSound mSEDamage;//�_���[�W�̉�



	bool ColIf(CTask *Task_You, CTask *Task_I);

	void Update(CTask *t);//�X�V����

	void PlayerCollision(CTask *TaskYou, CTask *Player); //�v���C���[�̂�����͂�Ă�����
	void EnemyCollision(CTask *TaskYou, CTask *Enemy); //�G�l�~�[�̂�����͂�Ă�����A
	void PuckCollision(CTask *TaskYou, CTask *Puck); //�p�b�N�̓����蔻��
	void CameraCollision(CTask *TaskYou, CTask *Camera);//�J�����̓����蔻��
	void OnCollision(CTask *TaskYou, CTask *Task_I);    //�����蔻��Ăяo������


	static CCollisionManager *mCollisionManager;
	CCollisionManager();

public:

	static CCollisionManager *GetInstance(); //GetInstance
	~CCollisionManager();

	void Add(CTask::E_TAG tag, CCollider *col);//�����蔻��ǉ�����

	void Update();
};

#endif
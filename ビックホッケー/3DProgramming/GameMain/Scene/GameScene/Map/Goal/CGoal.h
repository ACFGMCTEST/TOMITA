#ifndef CXGoal_H
#define CXGoal_H

#include "../../../../Vector/CVector3.h"
#include "../../../../Collision/CCollider.h"

//#include "CBillBoard.h"
#include "../../../../Graphic/CModelX.h"
#include "../../Effect/CExplosion.h"
#include"../../../../Graphic/CBox.h"
/*�L�����X�e�[�^�X*/

/*�������*/
#define KNOCK_BACK  0.2f/*������т̓x����*/

/*�i�ޕ��p*/
#define FORWARD 0.0f,0.0f,1.0f


/*�S�[���|�W�V����*/
#define GOAL_POS_Goal_PLAYER CVector3(CMap::PlayerFirstPos().x,CMap::PlayerFirstPos().y - 2.0f,CMap::PlayerFirstPos().z + 10.0f)
#define GOAL_POS_Goal_ENEMY  CVector3(CMap::EnemyFirstPos().x, CMap::EnemyFirstPos().y - 2.0f, CMap::EnemyFirstPos().z - 10.0f)
/*
CXGoal
�S�[���N���X
*/
class CGoal :public CBox{
public:
	CVector3 mForward;//�i�ތ���
	CVector4 fortank; //�����������Ă������
	CVector3 mPosition;	//�ʒu
	CVector3 mRotation;	//��]

	CCollider *mCBBox;//�����蔻��

	CExplosion mEffect;//�S�[���������̃G�t�F�N�g

	CGoal(CVector3 pos,CTask::E_TAG tag);

	/*�����蔻�菉����*/
	void ColInit();
	//����������
	void Init(CVector3 pos);
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//billboard�̕`�揈��
	void BillboardRender();
	//�|�W�V�����̕ύX�֐��@
	void PosUpdate();
	/*�S�[���������̉��o*/
	void GoalPerformance();

};

#endif

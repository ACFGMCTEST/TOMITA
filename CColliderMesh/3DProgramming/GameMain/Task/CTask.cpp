#include "CTask.h"


CTask::CTask() :mpNext(0), mpPrev(0), mKillFlag(false), mUiFlag(false), mCharaFlag(false){};


CTask::~CTask(){};
void CTask::Init(){};
void CTask::Update(){};
void CTask::Render(){};
void CTask::BillboardRender(){}


///*�^�O���f(�����蔻��p)*/
//void CTask::PrintColTag(){
//
//	printf("�����蔻��̃^�O��");
//	switch (eTag)
//	{
//		/*�Ȃ�*/
//	case CTask::E_TAG_NO:
//		printf("�^�O�Ȃ�");
//		break;
//		/*�p�b�N*/
//	case CTask::E_TAG_PUCK:
//		printf("Puck");
//		break;
//		/*�v���C���[*/
//	case CTask::E_TAG_PLAYER:
//		printf("Player");
//		break;
//		/*�E�G�|��*/
//	case CTask::E_TAG_WEAPON:
//		printf("Weapon");
//
//		break;
//	case CTask::E_TAG_ATTACK_INIT_RANGE:
//		printf("AttackInitRange");
//
//		break;
//	case CTask::E_TAG_ATTACK_RANGE:
//		printf("AttackRange");
//
//		break;
//	case CTask::E_TAG_ENEMY:
//		printf("Enemy");
//
//		break;
//	case CTask::E_TAG_TRAMPOLINE:
//		printf("�^�O = �p�b�N\n");
//
//		break;
//	case CTask::E_TAG_GOAL_PLAYER:
//		printf("GoalPlayer");
//
//		break;
//	case CTask::E_TAG_GOAL_ENEMY:
//		printf("GoalEnemy");
//
//		break;
//	case CTask::E_TAG_NET:
//		printf("Net");
//
//		break;
//	case CTask::E_TAG_SLOPE:
//		printf("Slope");
//
//		break;
//	case CTask::E_TAG_BOX:
//		printf("Box");
//
//		break;
//	case CTask::E_TAG_HIGH_BOX:
//		printf("HightBox");
//
//		break;
//	case CTask::E_TAG_FAST_FLOOR:
//		printf("FastFloor");
//
//		break;
//	case CTask::E_TAG_SLOW_FLOOR:
//		printf("SlowFloor");
//		break;
//	}
//	printf("�ł�\n");
//}
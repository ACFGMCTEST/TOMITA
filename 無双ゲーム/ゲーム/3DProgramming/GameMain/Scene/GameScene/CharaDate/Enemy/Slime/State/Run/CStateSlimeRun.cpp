#include "CStateSlimeRun.h"
#include "../../CSlime.h"

//�ύX����֐�
void CStateSlimeRun::ChangeState(){
}
/*���߂ɌĂяo��*/
void CStateSlimeRun::Start()
{

}

/*�X�V����*/
void CStateSlimeRun::Update(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*�A�C�h�����O�̏���*/
	sli->ChangeAnimation(CTask::E_RUN, true, ANIMA_SPEED_RUN);

	/*����*/
	SPEED_RUN_ACC(sli->mVelocity);//�ړ����x�v�Z
	sli->Move();

}

CStateSlimeRun::CStateSlimeRun()
{
}

CStateSlimeRun::~CStateSlimeRun()
{
}
#include "CStateSlimeRun.h"
#include "../../CSlime.h"
/*�i�ރX�s�[�h*/
#define SPEED_RUN 0.01f //MAX����
#define SPEED_RUN_ACC(v) if (SPEED_RUN > v){v += SPEED_RUN* 0.1f; }else{v = SPEED_RUN;}//�����x�v�Z����ɗ����ꍇ

//�ύX����֐�
void CStateSlimeRun::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*�t���O�������Ă��Ȃ����*/
	if (!sli->Search()){
		mNextRegisterName = SLI_STATE_IDLING;//����
	}
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
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
	sli->AIMove();
}

CStateSlimeRun::CStateSlimeRun()
{
}

CStateSlimeRun::~CStateSlimeRun()
{
}
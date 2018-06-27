#include "CSlimeRun.h"
#include "../CSlime.h"
/*�i�ރX�s�[�h*/
#define SPEED_RUN 0.05f //MAX����
#define SPEED_RUN_ACC(v) if (SPEED_RUN > v){v += SPEED_RUN* 0.1f; }else{v = SPEED_RUN;}//�����x�v�Z����ɗ����ꍇ
/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED 60 * 3

//�ύX����֐�
void CSlimeRun::ChangeState(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*�t���O�������Ă��Ȃ����*/
	if (!sli->Search()){
		mNextRegisterName = F_SLI_IDLING;//�ҋ@
	}
	/*�U���̃t���O������*/
	if (sli->AttackRange()) {
		mNextRegisterName = F_SLI_ATTACK;//�U��
	}
	/*�_���[�W���󂯂Ă���Ȃ�*/
	if (sli->mFlagDamage) {
		mNextRegisterName = F_SLI_DAMAGE;//�_���[�W
	}
	
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}
/*���߂ɌĂяo��*/
void CSlimeRun::Start()
{

}

/*�X�V����*/
void CSlimeRun::Update(){
	CSlime *sli = dynamic_cast<CSlime*>(mpParent);
	/*�A�C�h�����O�̏���*/
	sli->ChangeAnimation(F_SLI_RUN,F_SLI_KING_RUN, true, ANIMA_SPEED);

	/*����*/
	SPEED_RUN_ACC(sli->mVelocity);//�ړ����x�v�Z
	sli->AIMove();
}

CSlimeRun::CSlimeRun()
{
}

CSlimeRun::~CSlimeRun()
{
}
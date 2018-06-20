#include "CPlayerJump.h"
#include "../CPlayer.h"
/*�W�����v�̃X�s�[�h*/
#define JUMP_SPEED 0.6f//�W�����v����X�s�[�h
/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED_JUMP 50
#define ANIMA_SPEED_JUMP_LAND 30 //���n����

#define ANIMAKEY_ADJUST 10 //�A�j���[�V���������p
//�A�j���[�V���� KEY ����
#define ANIMA_KEY_DEPRE 25 //�A�j���[�V�����̓��ݍ��ݏ��(�Ō�)
#define ANIMA_KEY_JUMP_UP  30 //�A�j���[�V�����̃W�����v�����(�Ō�)
#define ANIMA_KEY_JUMP_DOWN  40 //�A�j���[�V�����̃W�����v�����Ă�����(�Ō�)
#define ANIMA_KEY_LAND  60 //�A�j���[�V�������n��(�Ō�)

//�ύX����֐�
void CPlayerJump::ChangeState(){
	/*�A�C�h�����O����ꍇ*�@�n�ʂɂ����Ƃ�*/
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	if (pl->mAnimationTime >
		pl->mpModel->mAnimationSet[pl->mAnimationIndex]->mMaxTime) {
		mNextRegisterName = PL_STATE_IDLING;//�A�C�h�����O����
	}
	/*�U������ꍇ*/
	if (CKey::once(KEY_ATTACK)){
		mNextRegisterName = PL_STATE_ATTACK;//�U��
	}
	//���O������΃t���O�𗧂Ă�
	if (!mNextRegisterName.empty()) mFlagNext = true;//�����������
}
/*���߂ɌĂяo��*/
void CPlayerJump::Start()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	mVelocity = pl->mVelocity;//�ړ��ʂ�������
	pl->mFlagJump = true;//�v���C���[���W�����v������
	mFlagFall = false;
}


/*�A�j���[�V����*/
bool CPlayerJump::JumpAnima()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);
	bool flag = false;//�W�����v�̃A�j���[�V����
	float speed = ANIMA_SPEED_JUMP;
	/*�A�j���[�V�����̒���*/
	/*���ݍ��ݒ�*/
	if (0 <= pl->mAnimationTime && pl->mAnimationTime < ANIMA_KEY_DEPRE) {
		flag = false;
	}
	/*�W�����v��*/
	else if (ANIMA_KEY_DEPRE <= pl->mAnimationTime && pl->mAnimationTime < ANIMA_KEY_JUMP_UP) 
	{	
		flag =  true;
	}
	/*�W�����v�����Ă���*/
	else if (ANIMA_KEY_JUMP_UP <= pl->mAnimationTime && pl->mAnimationTime < ANIMA_KEY_JUMP_DOWN) 
	{
		if (pl->mFlagJump) return true;

		flag = false;
	}
	/*���n��*/
	else if (ANIMA_KEY_JUMP_DOWN <= pl->mAnimationTime && pl->mAnimationTime <= ANIMA_KEY_LAND)
	{
		speed = ANIMA_SPEED_JUMP_LAND;
		if (pl->mFlagJump) return true;
		flag = false;
	}
	pl->ChangeAnimation(CPlayer::E_JUMP, false, speed);//�A�j���[�V����������

	return flag;


}

/*�X�V����*/
void CPlayerJump::Update()
{
	CPlayer *pl = dynamic_cast<CPlayer*>(mpParent);

	
	/*�A�j���[�V�����Ŕ��f*/
	if (JumpAnima()) {
		/*�W�����v*/
		pl->mVelocity = mVelocity;
		pl->Move();//�ړ��֐�.��(x,z)�̈ړ�
		mPrevPosY = pl->mPosition.y;//���݂̃|�W�V�����L��
		float jumpVilocity = JUMP_SPEED - GRAVITY(pl->mGravitTime);//��������
		/*�W�����v��0���傫���ꍇ*/
		pl->mPosition.y += jumpVilocity;
	}
	/*�������łȂ��ꍇ*/
	if (!mFlagFall) {
		pl->mFlagJump = true;//�n�ʂ����ԂƂ��̔��蒲���p
		/*�������̏ꍇ*/
		float graSpeed = GRAVITY(pl->mGravitTime);
		if (JUMP_SPEED <= graSpeed * 2) {
			mFlagFall = true;
		}
	}
	pl->State(PL_STATE_JUMP);
}
//�J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CPlayerJump::OnChangeEvent()
{

}

CPlayerJump::CPlayerJump() {
}

CPlayerJump::~CPlayerJump()
{
}
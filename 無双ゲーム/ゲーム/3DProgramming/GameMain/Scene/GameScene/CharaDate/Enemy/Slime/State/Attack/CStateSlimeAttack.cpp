#include "CStateSlimeAttack.h"
#include "../../CSlime.h"
/*�X�s�[�h�̃t���[������velocity��ύX����*/
/*�t���[��*/
#define FRAME_VEL_ATTACK1 0
#define FRAME_VEL_ATTACK2 30
#define FRAME_VEL_ATTACK3 40
/*�X�s�[�h*/
#define BASE_SPEED 0.2f
#define VEL_ATTACK1 BASE_SPEED * 0.5f
#define VEL_ATTACK2 0
#define VEL_ATTACK3 BASE_SPEED * 0.7f
//�ύX����֐�
void CStateSlimeAttack::ChangeState(){
	
}
/*���߂ɌĂяo��*/
void CStateSlimeAttack::Start(){
	mAnimaSpeed = 0;//������
}
/*�U���̈ړ���������*/
void CStateSlimeAttack::AttackSpeed(){
	
}
/*�X�V����*/
void CStateSlimeAttack::Update()
{
	/*�U��*/
	AttackSpeed();//�U���ŏ����O�Ɉړ�������
}
//�J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CStateSlimeAttack::OnChangeEvent()
{

}

CStateSlimeAttack::CStateSlimeAttack()
{
}

CStateSlimeAttack::~CStateSlimeAttack()
{
}
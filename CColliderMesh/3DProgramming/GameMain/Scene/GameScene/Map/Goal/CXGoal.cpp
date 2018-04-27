#include "CXGoal.h"
#include "windows.h"
#include "../../../../Key/CKey.h"
#include "../../../../../Define/Define.h"
#include "../CMap.h"
#include "../../../../Key/CMouse.h"
#include "../../CharaDate/CXCharPlayer.h"
#include <math.h>

/*�����蔻��̐ݒ�l*/
#define OBB_POS CVector3(0.0f, 0.0f, 0.0f) 
#define OBB_SIZE new float[]{MAPCHIP_SIZE, 0.8f, 0.4f} 
/*HP�o�[�̐ݒ�l*/
#define HP_BAR_POS CVector3(mPosition.x,mPosition.y + 1.8f,mPosition.z)
#define HP_BAR_SIZE -0.4f, 0.4f, -0.1f, 0.0f
/*�X�s�[�h*/
#define SPEED_DOWN_ALWAYS 0.0001f//��ɉ����錸���x
#define SPEED_Goal 0.1f//�ʏ푬�x
#define SPEED_MAX ATTACK_POWER_MAX + 0.1f//�ō�����
//#define SPEED_MAX 10.0f//�ő�����x
#define SPEED_UP 0.01f//�������ɏ�������̏㏸�l
#define SPEED_DOWN 0.01f//�������ɏ�������̌����l
/*�p�x*/
#define ANGLE_90 90 //�p�x
#define ANGLE_45 45 //�p�x
#define ANGLE_1 1//�p�x\


/*�|�W�V�������グ�鏈��*/
#define STAND_UP 0.1f

CXGoal::CXGoal(){
	mForward = CVector3(FORWARD);
	mpParent = this;
	mState = E_IDLE;
	

};
/*�����蔻�菉����*/
void CXGoal::ColInit() {

	/*�����蔻��C���X�^���X�쐬*/
	mCBBox = new CCollider(CTask::E_COL_BOX);
	mCBBox->mpParent = this;
}
/*
Init
���f���ƏՓ˔���̐ݒ���s��
*/
void CXGoal::Init(CModelX *model,CVector3 pos) {
	ColInit();
	mPosition = pos;
	CModelXS::Init(model);
	mCBBox->SetBoxOBB(OBB_POS, OBB_SIZE
		, &mpCombinedMatrix[model->FindFrame("Armature_Bone")->mIndex]);
	
	PosUpdate();
	/*�G�t�F�N�g*/
	mEffect.Init(pos, mRotation);
	//�͂��߂̓A�j���[�V���������Ȃ��悤�ɂ��Ă���
	mEffect.DisableAnima();
}

/*�|�W�V�����̃A�b�v�f�[�g�֐�*/
void CXGoal::PosUpdate(){
	CMatrix44 rot_y, pos, matrix;
	//��]�s��̍쐬
	rot_y.rotationY(mRotation.y);

	/////�i�s�������v�Z
	//mForward = mForward * rot_y;
	////�ړ�������
	//mPosition += mForward * mVelocity;

	//�ړ��s����v�Z����
	pos.translate(mPosition);
	//��]�ړ��s������߂�
	matrix = pos * rot_y;

	//���_�f�[�^�̍X�V
	CModelXS::Update(matrix);

	mCBBox->Update();

}

/*�X�V����*/
void CXGoal::Update(){

	/*�|�W�V�����̍X�V����*/
	PosUpdate();

	mCBBox->Update();
}

/*Render*/
void CXGoal::Render() {
	CModelXS::Render();
#ifdef _DEBUG
	mCBBox->Render();
#endif
}

//billboard�̕`�揈��
void CXGoal::BillboardRender(){

	mEffect.Update();
	mEffect.Render();
}

/*�S�[���������̉��o*/
void CXGoal::GoalPerformance(){
	mEffect.EnabledAnima();
}
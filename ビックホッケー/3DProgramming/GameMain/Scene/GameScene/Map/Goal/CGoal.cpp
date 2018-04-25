#include "CGoal.h"
#include "windows.h"
#include "../../../../Key/CKey.h"
#include "../../../../../Define/Define.h"
#include "../CMap.h"
#include "../../../../Key/CMouse.h"
#include "../../CharaDate/CXCharPlayer.h"
#include "../../../../Collision/CCollisionManager.h"
#include <math.h>
/*�傫��*/
#define BOX_SIZE -MAPCHIP_SIZE, MAPCHIP_SIZE, -MAPCHIP_SIZE, MAPCHIP_SIZE, -MAPCHIP_SIZE*0.1f, MAPCHIP_SIZE*0.1f
/*�����蔻��̐ݒ�l*/
#define OBB_POS CVector3(0.0f, 0.0f, 0.0f) 
#define OBB_SIZE new float[]{MAPCHIP_SIZE, MAPCHIP_SIZE*1.1f, MAPCHIP_SIZE} 
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
#define ANGLE_1 1//�p�x
#define SET_OBB OBB_POS,OBB_SIZE,&mMatrix

/*�|�W�V�������グ�鏈��*/
#define STAND_UP 0.1f

CGoal::CGoal(CVector3 pos,CTask::E_TAG tag){

	mPosition = pos;

	/*�����蔻��C���X�^���X�쐬*/
	mCBBox = new CCollider(E_COL_BOX);
	/*�e�ݒ�*/
	mCBBox->mpParent = this;
	/*�|�W�V�����ݒ�*/
	mPos.x = pos.x;
	mPos.y = 0;
	mPos.z = pos.z - MAPCHIP_SIZE;
	for (int i = 0; i < BOX_FACE_NUM; i++)
	{
		mRect[i].mMatrix = mMatrix;

	}
	UpdateMatrix();

	/*�T�C�Y�ݒ�*/
	SetVertex(BOX_SIZE);
	/*�F�ݒ�*/
	SetColor(BLACK_COLOR);


	/*�����蔻��ݒ�*/
	mCBBox->SetBoxOBB(SET_OBB);//�ݒ�
	mCBBox->eTag = tag;
	/*�����_�[���Ԍ��߂�*/
	ePriority = CTask::E_GOAL_PLAYER;
	/*�����蔻��ǉ�*/
	CCollisionManager::GetInstance()->Add(mCBBox->eTag, mCBBox);

	
	/*�X�V*/
	PosUpdate();
	/*�G�t�F�N�g*/
	mEffect.Init(pos, mRotation);
	//�͂��߂̓A�j���[�V���������Ȃ��悤�ɂ��Ă���
	mEffect.DisableAnima();
};
/*�����蔻�菉����*/
void CGoal::ColInit() {}
/*
Init
���f���ƏՓ˔���̐ݒ���s��
*/
void CGoal::Init(CVector3 pos) {
	ColInit();
	mPosition = pos;
	
	/*�����蔻��ݒ�*/
	mCBBox->SetBoxOBB(SET_OBB);//�ݒ�
	PosUpdate();
	/*�G�t�F�N�g*/
	mEffect.Init(pos, mRotation);
	//�͂��߂̓A�j���[�V���������Ȃ��悤�ɂ��Ă���
	mEffect.DisableAnima();
}


/*�|�W�V�����̃A�b�v�f�[�g�֐�*/
void CGoal::PosUpdate(){
	CMatrix44 rot_y, pos, matrix;
	//��]�s��̍쐬
	rot_y.rotationY(mRotation.y);

	//�ړ��s����v�Z����
	pos.translate(mPosition);
	//��]�ړ��s������߂�
	matrix = pos * rot_y;

	//���_�f�[�^�̍X�V
	//CModelXS::Update(matrix);

	mCBBox->Update();

}

/*�X�V����*/
void CGoal::Update(){

	/*�|�W�V�����̍X�V����*/
	PosUpdate();

	mCBBox->Update();
}

/*Render*/
void CGoal::Render() {
	BillboardRender();
	CBox::UpdateMatrix();

	CBox::Render();
}

//billboard�̕`�揈��
void CGoal::BillboardRender(){
	//printf("���o���܂�\n");
	mEffect.Update();
	mEffect.Render();
}

/*�S�[���������̉��o*/
void CGoal::GoalPerformance(){
	mEffect.EnabledAnima();
}
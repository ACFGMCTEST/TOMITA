#include "CEffect3D.h"
#include "../../../Collision/ColType/CColSphere.h"
#include "../../../Collision/CCollisionManager.h"

/*�R���X�g���N�^*/
CEffect3D::CEffect3D(){
	CTask::eName = CTask::E_3D_EFFECT;
}
/*�f�X�g���N�^*/
CEffect3D::~CEffect3D() {}
/*������*/
void CEffect3D::Init(CTask *parent,CModelX *mod,CVector3 *ppos,CVector3 *pRot) {
	mpPos = ppos;
	mpRot = pRot;

	PosInit();

	CModelXS::Init(mod);
	/*�����蔻��ݒ�*/
#define COL_RADIUS 2.5f//���a
#define COL_POS CVector3(0.0f,0.0f,0.0f)
#define COL_MATRIX(string) &mpCombinedMatrix[mpModel->FindFrame(string)->mIndex]//�}�g���b�N�X
	new CColSphere(parent, COL_POS, COL_RADIUS, COL_MATRIX("Armature"), CColBase::PL_ATTACK_EFFECT3D);
}

/*�`��*/
void CEffect3D::Render() {
	CModelXS::Render();
}

//�|�W�V���������ɖ߂�
void CEffect3D::PosInit() {
	mPos = *mpPos;
	mRot = *mpRot;
}

/*�ړ��֐�*/
void CEffect3D::Move() {

	CMatrix44 rot_y, pos, matrix;
	//�O�����w��
	CVector3 Forward = CVector3(0.0f,0.0f,1.0f);
	//��]�s��̍쐬
	rot_y.rotationY(mRot.y);
	//�i�s�������v�Z
	Forward = Forward * rot_y;
#define SPEED 0.5f
	//�ړ�������
	mPos += Forward * SPEED;
}

//�|�W�V�����X�V
void CEffect3D::PosUpdate() {
	CMatrix44 pos, rot, matrix;
	//�ړ��s����v�Z����
	pos.translate(mPos);
	//��]�s��̍쐬
	rot.rotationY(mRot.y);
	//��]�ړ��s������߂�
	matrix = pos * rot;
	CModelXS::Update(matrix);
}

/*�X�V*/
void CEffect3D::Update() {
#define SPEED 40
	CModelXS::ChangeAnimation(MODEL_FILE"Effect\\EffectAnima.x", true, SPEED);
	//�ړ�������
	Move();
	//�|�W�V�������X�V
	PosUpdate();
	//�A�j���[�V�������I��������G�t�F�N�g������
	if (mAnimationTime >
		mpModel->mAnimationSet[mAnimationIndex]->mMaxTime) {
		CTask::mKillFlag = true;;
	}
}
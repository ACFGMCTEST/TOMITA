#include "glut.h"
#include "CCollider3.h"

/*
�R���W�����}�l�[�W���@��3����
*/

CCollisionManager3::CCollisionManager3(){}

CCollisionManager3* CCollisionManager3::mCollisionManager = 0;

//GetInstance
CCollisionManager3* CCollisionManager3::GetInstance() {
	if (mCollisionManager == 0) {
		mCollisionManager = new CCollisionManager3();
	}
	return mCollisionManager;
}

void CCollisionManager3::Add(CCollider3 *col){
	CTaskManager::Add(col);
}

/*�X�V����*/
void CCollisionManager3::Update(){

	CCollider3 *task;
	task = (CCollider3*)mpRoot;

	/*�T������*/
	while (task != 0)
	{
		//���g�̃R���C�_�^�C�v������
		switch (task->mType) {
		case CCollider3::COL_CAPSULE:
			//�ω����Ȃ��R���C�_�͏Փ˔��肵�Ȃ�
			if (task->mpCombinedMatrix) {
				//�R���C�_���R�s�[���čX�V
				CCollider3Capsule cc = (*(CCollider3Capsule*)task).GetUpdate();
				//�R���C�_��擪����Փ˔��肵�Ă���
				CCollider3 *n = (CCollider3*)mpRoot;
				while (n != NULL) {
					//�e�̃^�X�N�ŏՓ˔��肳����
					if (task->mpParent && task != n) {
						task->mpParent->Collision(&cc, n);
					}
					n = (CCollider3*)n->mpNext;
				}
			}
			break;
		}
		task = (CCollider3*)task->mpNext;
	}

#ifdef _DEBUG 
		AllRender();
#endif
}

CCollisionManager3::~CCollisionManager3(){
	AllKill();
}

void CCollider3Triangle::Update() {
	if (mpCombinedMatrix) {
		mV[0] = mV[0] * *mpCombinedMatrix;
		mV[1] = mV[1] * *mpCombinedMatrix;
		mV[2] = mV[2] * *mpCombinedMatrix;
	}
}

CCollider3Triangle CCollider3Triangle::GetUpdate() {
	CCollider3Triangle ct = *this;
	ct.Update();
	return ct;
}

void CCollider3Capsule::Update() {
	if (mpCombinedMatrix) {
		mV[0] = mV[0] * *mpCombinedMatrix;
		mV[1] = mV[1] * *mpCombinedMatrix;
	}
}

CCollider3Capsule CCollider3Capsule::GetUpdate() {
	CCollider3Capsule cc = *this;
	cc.Update();
	return cc;
}
/*
�J�v�Z���R���C�_�̏�����
parent:�e�ւ̃|�C���^
v0:���_�P 
v1:���_�Q
radius:���a
pcombinedMatrix:�A��������t���[���̍����s��
*/
CCollider3Capsule::CCollider3Capsule(CTask *parent, CVector3 topV0, CVector3 bottomV1, float radius, CMatrix44 *pcombinedMatrix)
: CCollider3Capsule()
{
	eColTag = E_COL_CAPSULE;
	mpCombinedMatrix = pcombinedMatrix;
	mV[0] = topV0;
	mV[1] = bottomV1;
	mRadius = radius;
	mpParent = parent;
}

void CCollider3Capsule::Render() {
	float color[] = { 1.0f, 1.0f, 0.0f, 0.5f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	CMatrix44 mat;
	CVector3 vec;
	glPushMatrix();
	if (mpCombinedMatrix) glMultMatrixf(mpCombinedMatrix->f);
	glPushMatrix();
	vec = mV[0] - mV[1];
	vec = vec.normalize();
	vec = vec * mRadius;
	vec = mV[1] + vec;
	mat.translate(vec);
	glMultMatrixf(mat.f);
	glutSolidSphere(mRadius, 20, 20);
	glPopMatrix();
	glPushMatrix();
	vec = mV[1] - mV[0];
	vec = vec.normalize();
	vec = vec * mRadius;
	vec = mV[0] + vec;
	mat.translate(vec);
	glMultMatrixf(mat.f);
	glutSolidSphere(mRadius, 20, 20);
	glPopMatrix();

	glPopMatrix();
}

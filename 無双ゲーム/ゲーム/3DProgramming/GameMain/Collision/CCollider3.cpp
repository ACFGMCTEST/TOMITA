#include "glut.h"
#include "CCollider3.h"

/*
コリジョンマネージャ　第3世代
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

/*更新処理*/
void CCollisionManager3::Update(){

	CCollider3 *task;
	task = (CCollider3*)mpRoot;

	/*探索処理*/
	while (task != 0)
	{
		//自身のコライダタイプを識別
		switch (task->mType) {
		case CCollider3::COL_CAPSULE:
			//変化しないコライダは衝突判定しない
			if (task->mpCombinedMatrix) {
				//コライダをコピーして更新
				CCollider3Capsule cc = (*(CCollider3Capsule*)task).GetUpdate();
				//コライダを先頭から衝突判定していく
				CCollider3 *n = (CCollider3*)mpRoot;
				while (n != NULL) {
					//親のタスクで衝突判定させる
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
カプセルコライダの初期化
parent:親へのポインタ
v0:頂点１ 
v1:頂点２
radius:半径
pcombinedMatrix:連結させるフレームの合成行列
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

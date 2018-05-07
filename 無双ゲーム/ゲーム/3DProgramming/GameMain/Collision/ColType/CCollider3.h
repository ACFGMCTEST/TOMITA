#ifndef CCOLLIDER3_H
#define CCOLLIDER3_H

#include "../Task/CTaskManager.h"
#include "../Vector/CVector3.h"
#include "../Matrix/CMatrix44.h"

/*
�R���C�_�@��3����
*/

class CCollider3 : public CTask {
public:
	enum EType {
		COL_TRIANGLE,	//�O�p�`�R���C�_
		COL_CAPSULE		//�J�v�Z���R���C�_
	};
	EType mType;
	CVector3 mAdjust;	//�Փˉ����@�����l
	CTask *mpParent;	//�e�̃^�X�N
	CMatrix44 *mpCombinedMatrix;	//�t���[���̍����s��
	CCollider3() : mpParent(0), mpCombinedMatrix(0) {}
};

class CCollisionManager3 : public CTaskManager {
private:

	static CCollisionManager3 *mCollisionManager;
	CCollisionManager3();

public:

	static CCollisionManager3 *GetInstance(); //GetInstance
	~CCollisionManager3();

	void Add(CCollider3 *col);//�����蔻��ǉ�����

	void Update();
};

//�O�p�`�R���C�_�N���X
class CCollider3Triangle : public CCollider3 {
	//�X�V�@���_�������s��Ŋ|����
	void Update();
public:
	CVector3 mV[3];

	CCollider3Triangle() {
		mType = COL_TRIANGLE;
		CCollisionManager3::GetInstance()->Add(this);//�����蔻��ǉ�
	}

	CCollider3Triangle(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2)
		: CCollider3Triangle()
	{
		mV[0] = v0;
		mV[1] = v1;
		mV[2] = v2;
	}
	//���_�������s��Ŋ|�����R���C�_���擾����
	CCollider3Triangle GetUpdate();
};

class CCollider3Capsule : public CCollider3 {
	void Update();
public:
	CVector3 mV[2];
	float mRadius;

	CCollider3Capsule() : mRadius(0.0f) {
		mType = COL_CAPSULE;
		CCollisionManager3::GetInstance()->Add(this);//�����蔻��ǉ�
	}

	CCollider3Capsule(CTask *parent, CVector3 v0, CVector3 v1, float radius, CMatrix44 *pcombinedMatrix);

	CCollider3Capsule GetUpdate();

	void Render();

};


#endif

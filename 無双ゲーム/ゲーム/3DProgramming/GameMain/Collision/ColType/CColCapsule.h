#ifndef COL_CAPSULE_H
#define COL_CAPSULE_H
#include "CColBase.h"
#include "../CCollisionManager.h"
#include "../../Vector/CVector3.h"

class CColCapsule : public CColBase {
private:
	/*�X�V*/
	void Update();
public:
	CVector3 mV[2];
	float mRadius;
	/*�R���X�g���N�^*/
	CColCapsule(){};
	/*�R���X�g���N�^�@����:�����蔻��ǉ����Ȃ������f*/
	CColCapsule(bool addFlag);
	/*�p�����[�^�ݒ�*/
	CColCapsule(CTask *parent, CVector3 v0, CVector3 v1, float radius, CMatrix44 *pcombinedMatrix);
	/*�X�V�����Ăяo��*/
	CColCapsule GetUpdate();
	/*�`�揈��*/
	void Render();

};


#endif

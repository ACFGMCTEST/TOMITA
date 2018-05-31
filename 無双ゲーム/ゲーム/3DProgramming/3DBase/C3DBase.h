#ifndef BASE_H
#define BASE_H
#include "../GameMain/Vector/CVector4.h"
#include "../GameMain/Matrix/CMatrix44.h"
#include <cassert>
#include "../GameMain/Task/CTask.h"

/*�RD�̃x�[�X�ɂȂ�N���X*/
class C3DBase : public CTask{
public:

	C3DBase * mpParent;//�e
	CMatrix44 mMatrix;//�s��
	CVector3 mPos;//�ʒu
	CVector3 mRot;//��]�l
	CVector3 mNormal;//�@��
	CVector3 mForward;//����

	C3DBase();
	/*�s��̍X�V*/
	void UpdateMatrix();


};

#endif
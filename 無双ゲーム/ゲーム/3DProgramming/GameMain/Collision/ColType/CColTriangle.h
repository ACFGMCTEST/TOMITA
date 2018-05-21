#ifndef COL_TRIANGLE_H
#define COL_TRIANGLE_H

#include "CColBase.h"
#include "../CCollisionManager.h"


/*�����蔻��N���X �O�p��*/

//�O�p�`�R���C�_�N���X
class CColTriangle : public CColBase {
private:

	//�X�V�@���_�������s��Ŋ|����
	void Update();
public:
	int mNumber;//�Q���n�|���S���̉��Ԗڂɐ������ꂽ���J�E���g
	static int mAllCount;//�O�p�|���S���̐����J�E���g

	CVector3 mV[3];
	CVector3 mPos;//�O�p�`�̒��S

	/*�g���C�A���O�����*/
	CColTriangle(bool addFlag);
	/*�f�X�g���N�^*/
	~CColTriangle();

	/*�p�����[�^�ݒ�*/
	CColTriangle(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2);
	//���_�������s��Ŋ|�����R���C�_���擾����
	CColTriangle GetUpdate();
};


#endif
#ifndef COL_SPHERE_H
#define COL_SPHERE_H

#include "CColBase.h"

/*�����蔻��N���X�@��*/
class CColSphere :public CColBase
{
private:
	CVector3 mInitPos;//���߂�pos�l
	/*�X�V����*/
	void Update();
public:
	float mRadius;//���a
	////��]�s�� 
	CMatrix44 mMatrixRotation;
	CColSphere(){};
	/*�����蔻��ǉ�*/
	void ColAdd();
	/*���̃p�����[�^�ݒ�*/
	CColSphere(CTask *parent, CVector3 pos, float radius, CMatrix44 *m);
	/*���̃p�����[�^�ݒ� �}�l�[�W���[�ŊǗ����Ȃ��ꍇ*/
	CColSphere(float radius, CVector3 pos, CMatrix44 *m);

	//OBB�ɍs��𔽉f
	void Transform(CMatrix44 &mat);
	/*�X�V�����Ăяo��*/
	CColSphere GetUpdate();
	/*�`��*/
	void Render();

};
#endif
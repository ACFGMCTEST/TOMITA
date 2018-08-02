//�y�c���l
#ifndef CEffect3D_HPP
#define CEffect3D_HPP
#include "../../../Graphic/CModelX.h"
#include "CEffect2D.h"
#include "../../../Collision/ColType/CColSphere.h"

class CEffect3D : public CModelXS ,public CTask {
private :
	CColSphere * mpCol;//�����蔻��
	CEffect2D * mpEffect;//�G�t�F�N�g
	//�v�Z�Ŏg������
	CVector3 mPos;
	CVector3 mRot;
	//���̈ʒu
	CVector3 *mpPos;
	CVector3 *mpRot;
public:
	~CEffect3D();
	CEffect3D();
	/*������*/
	void Init(CTask *parent, CModelX *mod,CVector3 *ppos,CVector3 *pRot);
	/*�`��*/
	void Render();
	/*�X�V*/
	void Update();
	//�|�W�V���������ɖ߂�
	void PosInit();
	/*�ړ��֐�*/
	void Move();
	//�|�W�V�����X�V
	void PosUpdate();
};
#endif

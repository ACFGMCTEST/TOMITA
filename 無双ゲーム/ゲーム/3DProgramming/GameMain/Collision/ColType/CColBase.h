#ifndef COL_BASE_H
#define COL_BASE_H

#include "../../Vector/CVector3.h"
#include "../../Matrix/CMatrix44.h"
#include "../../Task/CTask.h"

/*�����蔻��N���X�x�[�X*/
class CCollBase
{
public:
	CVector3 mPos;		//���S���W
	float r, g, b, a;//�F���
	/*�F�ݒ�*/
	void SetColor(float cr, float cg, float cb, float ca){
		r = cr;
		g = cg;
		b = cb;
		a = ca;
	}
};

#endif
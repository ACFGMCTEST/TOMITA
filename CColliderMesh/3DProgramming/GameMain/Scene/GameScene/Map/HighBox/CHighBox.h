
#ifndef HIGH_BOX_HPP
#define HIGH_BOX_HPP

#include "../../../../../Base/CBase.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollider.h"

class CHighBox : public CBox{
public:
	CCollider *mpColBox;		//�����蔻��

	/*�R���X�g���N�^ 
	pos = �ʒu*/
	CHighBox(CVector3 pos);
	/*�A�b�v�f�[�g*/
	void Update();
	/*�`�揈��*/
	void Render();

};

#endif

#ifndef SLOW_FLOOR_HPP
#define SLOW_FLOOR_HPP

#include "../../../../../Base/CBase.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollider.h"
/*��N���X*/
class CSlowFloor : public CBox{
public:
	CCollider *mpColBox;		//�����蔻��

	/*�R���X�g���N�^ 
	pos = �ʒu*/
	CSlowFloor(CVector3 pos);
	/*�A�b�v�f�[�g*/
	void Update();
	/*�`�揈��*/
	void Render();

};

#endif
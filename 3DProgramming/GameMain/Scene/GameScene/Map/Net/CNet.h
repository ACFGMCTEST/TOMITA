
#ifndef NET_HPP
#define NET_HPP

#include "../../../../../Base/CBase.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollider.h"
/*�ԃN���X*/
class CNet : public CBox{
public:
	CCollider *mpColBox;		//�����蔻��

	/*�R���X�g���N�^ 
	pos = �ʒu*/
	CNet(CVector4 pos);
	/*�A�b�v�f�[�g*/
	void Update();
	/*�`�揈��*/
	void Render();

};

#endif
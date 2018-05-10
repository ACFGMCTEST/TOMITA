
#ifndef SLOPE_HPP
#define SLOPE_HPP

#include "../../../../../Base/CBase.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollider.h"

#include "../../../GameScene/Map/CMap.h"

/*��N���X*/
class CSlope : public CBox{
private:
	int mMapChipX, mMapChipZ;//�����̃}�b�v�`�b�v��̍��W�l
	bool mFlagRot;//��]���������f
	/*��̌��݂̌����Ă������*/
	enum  ESlpoeRot{
		E_FRONT,// �O
		E_BACK,// ���
		E_RIGHT,// �E
		E_LEFT,// ��
	};
	ESlpoeRot eSlopeRot = E_FRONT;//��̌���
public:
	CCollider *mpColBox;		//�����蔻��
	CCollider *mpColRefLeft;	//�����蔻�蒵�˕Ԃ�悤��
	CCollider *mpColRefRight;	//�����蔻�蒵�˕Ԃ�悤�E

	float mMinX;//�T�C�Y�������ق�
	float mMaxX;//�T�C�Y�傫���ق�
	float mMinY;//�T�C�Y�������ق�
	float mMaxY;//�T�C�Y�傫���ق�
	float mMinZ;//�T�C�Y�������ق�
	float mMaxZ;//�T�C�Y�傫���ق�

	/*�T�C�Y���ׂ�*/
	void SetSize(float size);

	/*�R���X�g���N�^ 
	pos = �ʒu
	x , y = �����̃}�b�v����W�l*/
	CSlope(CVector3 pos, int x, int z, char e);
	/*�}�b�v�ɂ���Č�����ς��� �f�t�H���g�́C��������E�オ��*/
	void MapRot();
	/*�A�b�v�f�[�g*/
	void Update();
	/*�`�揈��*/
	void Render();
	/*��̒��Ԓl*/
	CVector3 MiddlePos(const CVector3 &pos) const;
	/*��̌X���ɂ���
	*rot =  ��]����l
	*/
	void SlpoeRot(CVector3 *rot) const;
};

#endif
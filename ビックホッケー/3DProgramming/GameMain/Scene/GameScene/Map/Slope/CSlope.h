
#ifndef SLOPE_HPP
#define SLOPE_HPP

#include "../../../../../Base/CBase.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../Graphic/CBox.h"
#include "../../../../../Define/Define.h"
#include "../../../../Collision/CCollider.h"

/*�����蔻��:�{�b�N�X�ݒ�*/
#define OBB_POS CVector3(0.0f,0.0f,0.0f) 
#define OBB_SIZE CVector3(MAPCHIP_SIZE, MAPCHIP_SIZE, MAPCHIP_SIZE)
#define SMALL_SIZE(num) num*0.999f//�{�b�N�X�Ƃ��Ԃ�Ȃ��p
#define SET_OBB OBB_POS,OBB_SIZE,&mMatrix

/*��N���X*/
class CSlope : public CBox{


public:
	

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


	CCollider *mpColBox;		//�����蔻��


	float mMinX;//�T�C�Y�������ق�
	float mMaxX;//�T�C�Y�傫���ق�
	float mMinY;//�T�C�Y�������ق�
	float mMaxY;//�T�C�Y�傫���ق�
	float mMinZ;//�T�C�Y�������ق�
	float mMaxZ;//�T�C�Y�傫���ق�

	/*�T�C�Y���ׂ�*/
	void SetSize(float size);

	CSlope(){}

	/*�R���X�g���N�^ 
	pos = �ʒu
	x , y = �����̃}�b�v����W�l*/
	CSlope(CVector3 pos,int x,int z);
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
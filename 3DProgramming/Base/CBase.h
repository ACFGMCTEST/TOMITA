#ifndef BASE_H
#define BASE_H
#include "../GameMain/Vector/CVector4.h"
#include "../GameMain/Matrix/CMatrix44.h"
#include <cassert>
#include "../GameMain/Task/CTask.h"
/*�^���N��HP*/
#define HP_TANK 2.5f
/*�ו���HP*/
#define HP_BAGGAGE 2.0f


class CBase : public CTask{
public:

	CVector4 mPos;
	CVector4 mRot;
	CMatrix44 mMatrix;
	CVector4 mNormal;
	CVector4 mForward;

	float mRadius; ///���a
	CBase *mpParent;

	float mHp; //�̗�
	float mColRot; //���������Ƃ��̉�](�Ă���AI�Ɏg��)
	static bool mFlagEnemyFight; //�N���퓬���Ă��邩���f
	static int mSumNum; //�S���̃i���o�[���v
	int mNum; //�����ԍ�
	bool mFlagSandwiching;//����ł���?���f�p

	CVector4 mGoRot; //�s����w��

	enum ESTATE
	{
		NORMAL, FIGHT, EXPLOSIONINIT, EXPLOSION, DOWN,FALLINIT,FALL
	};
	const ESTATE mState;

	enum COLLINDERTYPE{
		NOCOLLIDER,
		COL_PLANE,
		COL_SPHERE,
		COL_RECT
	};
	COLLINDERTYPE mColType;

	enum TAG{
		NOTAG,
		TAG_CANNOBALL,
		TAG_BAGGAGE,
		TAG_TARGAT,
		TAG_GROUND,
		TAG_WALL,
		TAG_TANK,
		TAG_TANKENEMY,
		TAG_EXPLOSION,
		TAG_ATTACKCANNON,
		TAG_RECT,
		TAG_GOAL_PLAYER,
		TAG_GOAL_ENEMY,
		TAG_HOLE_SMALL,//�����^���N�p
		TAG_HOLE_BIG//�ו�,�G�^���N�p
	};
	TAG mTag;

	bool mEnabled;

	CBase();

	void UpdateMatrix();

	void BaseInit();

	virtual void Update(){};
	virtual void Render(){};
	
};

#endif
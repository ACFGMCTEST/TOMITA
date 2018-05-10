#ifndef BASE_H
#define BASE_H
#include "../GameMain/Vector/CVector4.h"
#include "../GameMain/Matrix/CMatrix44.h"
#include <cassert>
#include "../GameMain/Task/CTask.h"
/*タンクのHP*/
#define HP_TANK 2.5f
/*荷物のHP*/
#define HP_BAGGAGE 2.0f


class CBase : public CTask{
public:

	CVector4 mPos;
	CVector4 mRot;
	CMatrix44 mMatrix;
	CVector4 mNormal;
	CVector4 mForward;

	float mRadius; ///半径
	CBase *mpParent;

	float mHp; //体力
	float mColRot; //当たったときの回転(てきのAIに使う)
	static bool mFlagEnemyFight; //誰か戦闘しているか判断
	static int mSumNum; //全員のナンバー合計
	int mNum; //製造番号
	bool mFlagSandwiching;//挟んでいる?判断用

	CVector4 mGoRot; //行き先指定

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
		TAG_HOLE_SMALL,//自分タンク用
		TAG_HOLE_BIG//荷物,敵タンク用
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
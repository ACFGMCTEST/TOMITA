/*
*タスクのプログラム
*担当者 冨田健斗
*/
#ifndef TASK_HPP
#define TASK_HPP
#include <stdio.h>
#include <assert.h>

class CColBase;

class  CTask
{
public:

	int mNumber;//自分の製造番号
	CTask *mpNext;
	CTask *mpPrev;

	bool mKillFlag;  //フラグが立っているものを消す
	bool mCharaFlag; //キャラクターのフラグがたっているものにはCol判定

	CTask *mpParent;//親 ここからタスク上のものにアクセスしていく
	float mValue; //現在ＨＰ


	//プレイヤーの状態値
	enum ESTATE {
		E_IDLING,		//立ち
		E_RUN,		//走る
		E_ATTACK,	//攻撃
		E_RUN_ATTACK,//移動攻撃
		E_JUMP,	    //ジャンプ
		E_DMGM,		//ダメージ
		E_STATE_ARRAY//ステータスの上限
	};
	ESTATE mState;	//プレイヤーの状態

	//何者か判断
	enum E_NAME{
		E_PLAYER,
		E_SLIME,
	};
	E_NAME eName;//ネーム

	/*当たり判定の属性*/
	enum EType {
		COL_TRIANGLE,	//三角形コライダ
		COL_BOX,//ボックス
		COL_SPHEPE,//球
		COL_CAPSULE		//カプセルコライダ
	};
	EType mType;


	CTask();
	virtual ~CTask();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void BillboardRender();//billboardするもの　処理手順で見えなくなるものがあるので分ける
	virtual bool Collision(CColBase* p1, CColBase* p2) { return false; };

};


#endif

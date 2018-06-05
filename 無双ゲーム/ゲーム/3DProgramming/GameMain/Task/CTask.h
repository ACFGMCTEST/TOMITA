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




	//何者か判断
	enum E_NAME{
		E_PLAYER,//プレイヤー
		E_SLIME,//スライム
		E_BILLBOARD,//ビルボード
	};
	E_NAME eName;//ネーム

	/*当たり判定の形*/
	enum EType {
		COL_BOX,//ボックス
		COL_SPHEPE,//球
		COL_CAPSULE,		//カプセルコライダ
		COL_TRIANGLE,	//三角形コライダ

	};
	EType mType;



	CTask();
	virtual ~CTask();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual bool Collision(CColBase* p1, CColBase* p2) { return false; };

};


#endif

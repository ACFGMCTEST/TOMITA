/*
*タスクのプログラム
*担当者 冨田健斗
*/
#ifndef TASK_HPP
#define TASK_HPP
#include <stdio.h>
#include <assert.h>

class  CTask
{
public:

	CTask *mpNext;
	CTask *mpPrev;

	bool mKillFlag;  //フラグが立っているものを消す
	bool mCharaFlag; //キャラクターのフラグがたっているものにはCol判定

	CTask *mpParent;//親 ここからタスク上のものにアクセスしていく
	float mValue; //現在ＨＰ

	int mCount; //製造番号

	//プレイヤーの状態値
	enum ESTATE {
		E_IDLING,		//立ち
		E_RUN,		//走る
		E_ATTACK_RUN,		//攻撃ためながら走る
		E_ATTACK_INIT,	//攻撃ために入る
		E_ATTACK,	//攻撃
		E_ATTACK_IDLING,	//攻撃ため
		E_JUMP,	    //ジャンプ
		E_ATTACK_JUMP,//アタックジャンプ
		E_DMGM,		//ダメージ
		E_STATE_ARRAY//ステータスの上限
	};
	ESTATE mState;	//プレイヤーの状態


	/*属性*/
	enum E_TAG{
		E_TAG_NO,				//初期値
		E_TAG_CAMERA,			//カメラ
		E_TAG_PLAYER,			//プレイヤー
		E_TAG_WEAPON,			//攻撃範囲
		E_TAG_ATTACK_INIT_RANGE,//攻撃準備範囲 エネミー用
		E_TAG_ATTACK_RANGE,		//攻撃範囲 エネミー用
		E_TAG_ENEMY,			//エネミー
		E_TAG_GROUND,			//地面

		E_TAG_WALL,				//ウォー
	};
	E_TAG eTag = E_TAG_NO;//当たり判定の順番
	/*順番*/
	enum E_PRIORITY{
		E_NO,				//初期値
		E_PLAYER,			//プレイヤー
		E_WEAPON,			//攻撃範囲
		E_ATTACK_INIT_RANGE,//攻撃準備範囲 エネミー用
		E_ATTACK_RANGE,		//攻撃範囲 エネミー用
		E_GROUND,			//地面
		E_ENEMY,			//エネミー
	};
	E_PRIORITY ePriority;//レンダーの順番

	/*当たり判定の形*/
	enum  E_COL_TAG
	{
		E_COL_NO,
		E_COL_WALL,//壁
		E_COL_BOX,//ボックス
		E_COL_SPHEPE,//球
	};
	E_COL_TAG eColTag;

	bool mUiFlag; //UIがあるか判断

	CTask();
	virtual ~CTask();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void BillboardRender();//billboardするもの　処理手順で見えなくなるものがあるので分ける

};
static CTask::ESTATE ReferenceState;	//アニメーション参照用 swich文で楽するために使う


#endif

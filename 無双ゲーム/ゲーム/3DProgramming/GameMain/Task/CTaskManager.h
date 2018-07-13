/*
*タスクのマネージャーのプログラム
*担当者　冨田健斗
*/
#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP
#include "CTask.h"
#include <assert.h> 

class  CTaskManager
{
protected:
	CTaskManager();
	CTask* Kill(CTask *t);
private:
	static CTaskManager *mTaskManager;
	void SwapTask(CTask **p, CTask **n);
public:
	CTask *mpRoot;
	CTask *mpTail;
	static CTaskManager *GetInstance(); 
	//デバック用　現在格納されている数を表示
	void PrintCount(char *str) {
		CTask *task;
		task = mpRoot;
		int i = 0;
		while (task != 0)
		{
			i++;
			task = task->mpNext;
		}
		printf("%sは%dです\n", str, i);
	}
	~CTaskManager();

	/*
	追加処理
	後ろに追加していく形
	処理手順
	root == 0 が　何もないとき
	root != 0 が  あるとき
	*/
	void Add(CTask  *t);

	/*
	使い方
	Absは昇順　
	RはRebder用
	UはUpdate用
	*/
	void AbsR();




	/*
	デリート処理

	※注意　Killのほうは " **t  なので使い方に注意が必要  "

	プログラムの順番

	Taskのアドレスが始まりの時
				↓
	Taskのアドレスが終わりの時
				↓
	Taskのアドレスが中間の時

	*/

	void Sort(CTask *t);
	
	void AllKill();
	void AllUpdate();
	void AllRender();
	void AllMiniMapRender();
	void AllInit();
	/*ほしいもの
	Num ほしい属性指定
	Count 製造番号
	*/
};

#endif

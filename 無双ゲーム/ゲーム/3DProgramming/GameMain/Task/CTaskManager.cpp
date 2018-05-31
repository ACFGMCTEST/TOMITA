#include "CTaskManager.h"
#include "../../Define/Define.h"

CTaskManager* CTaskManager::mTaskManager = 0;


//GetInstance
CTaskManager* CTaskManager::GetInstance() {
	if (mTaskManager == 0) {
		mTaskManager = new CTaskManager();
	}
	return mTaskManager;
}


void CTaskManager::SwapTask(CTask **p, CTask **n){ //入れ替え処理
	CTask *s = *n;
	*n = *p;
	*p = s;

}


CTaskManager::CTaskManager() :mpRoot(0), mpTail(0){}


CTaskManager::~CTaskManager(){

}
/*
追加処理
後ろに追加していく形
処理手順
root == 0 が　何もないとき
root != 0 が  あるとき
*/
void CTaskManager::Add(CTask  *t){
	/*何も設定していないとき*/
	if (mpRoot == 0){
		/*頭の設定*/
		mpRoot = t; 
		mpRoot->mpPrev = 0; 
		mpRoot->mpNext = 0;
		/*尻尾の設定*/
		mpTail = 0;
	}
	/*2番目の処理*/
	else if (mpTail == 0){
		/*現在のものが小さい場合*/
		if (mpRoot-> eName < t-> eName){
			/*尻尾の設定*/
			mpTail = t;
			mpTail->mpPrev = mpRoot;
			mpTail->mpNext = 0;
			/*頭の設定*/
			mpRoot->mpPrev = 0;
			mpRoot->mpNext = mpTail;
			
		}
		/*現在のものが大きい場合*/
		else{
			/*尻尾の設定*/
			mpTail = mpRoot;
			mpTail->mpPrev = t;
			mpTail->mpNext = 0;
			/*頭の設定*/
			mpRoot = t;
			mpRoot->mpPrev = 0;
			mpRoot->mpNext = mpTail;
		}
	}
	/*3番目以上*/
	else if(mpRoot->mpNext != 0 && mpTail->mpPrev != 0){
		CTask temp;
		CTask *moveTask = &temp;//探すタスク
		moveTask->mpNext = mpRoot;

		/*追加する場所を探す*/
		while (moveTask != mpTail)
		{
			moveTask = moveTask->mpNext;


			/*最初*/
			if (mpRoot-> eName > t-> eName){
				/*追加するもの設定*/
				t->mpPrev = 0;
				t->mpNext = mpRoot;
				/*頭のタスク設定*/
				mpRoot = t; 
				/*探すタスク設定*/
				moveTask->mpPrev = t;
				if (moveTask->mpNext == 0){
					mpTail = moveTask;
				}

				break;
			}
			/*最後*/
			else if (moveTask == mpTail){
				/*しっぽ設定*/
				t->mpPrev = mpTail;
				mpTail->mpNext = t;
				mpTail = t;
				mpTail->mpNext = 0;
				break;
			} 
			/*中間*/
			else if (moveTask-> eName <= t-> eName &&
					t-> eName <= moveTask->mpNext-> eName){
				/*追加するもの設定*/
				t->mpNext = moveTask->mpNext;
				t->mpPrev = moveTask;
				/*外側のタスク設定*/
				moveTask->mpNext->mpPrev = t;
				moveTask->mpNext = t;
				
				break;
			}

		}
	}
}

void CTaskManager::Sort(CTask **t){
	CTask *n = new CTask();
	n = *t;
	Add(n);
	Kill(t);
}


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

void CTaskManager::Kill(CTask **t){

	CTask temp; //仮に作るもの
	CTask *T = &temp; //順番を見る
	T->mpNext = mpRoot;

	/*順番に探す*/
	while (T != mpTail)
	{
		T = T->mpNext;
		if (*t == T){ //Tとあっているとき
			/*始まり*/
			if (T == mpRoot){ 

				mpRoot = mpRoot->mpNext;
				mpRoot->mpPrev = 0;

				P_DELETE(*t);
				/*引数の設定を変える*/
				*t = mpRoot;
				break;
			}
			/*終わり*/
			else if (T->mpNext == 0){
				mpTail = mpTail->mpPrev;
				mpTail->mpNext = 0;
				P_DELETE(*t);
				/*引数の設定を変える*/

				*t = mpTail;
				break;
			}
			/*中間*/
			else{ 
				CTask *save_T; //仮の保存場所

				T->mpPrev->mpNext = T->mpNext;
				T->mpNext->mpPrev = T->mpPrev;

				save_T = T->mpPrev;
				/*引数の設定を変える*/
				P_DELETE(*t);
				*t = save_T;
				break;
			}
		}

	}

}

void CTaskManager::AllKill(){
	CTask *task;
	task = mpRoot;
	while (task != 0)
	{
		Kill(&task);
		task = task->mpNext;
	}
	P_DELETE(mpRoot);
}


void CTaskManager::AllInit(){
	CTask *task;
	task = mpRoot;
	while (task != 0)
	{
		task->Init();
		task = task->mpNext;
	}
}

void CTaskManager::AllUpdate(){
	CTask *task;
	task = mpRoot;
	
	/*すべてのRender表示*/
	while (task != 0)
	{
		/*削除フラグが立つと消す*/
		if (task->mKillFlag){ Kill(&task); }
		task->Update();
		task = task->mpNext;

	}

}
/*バブルソート*/
void CTaskManager::AbsR(){
	/*バブルソート*/
	CTask temp;
	CTask *p = &temp;//後ろ用
	CTask *n = &temp;//前用

	p->mpNext = mpRoot;
	n->mpNext = mpRoot;


	while (p->mpNext != mpTail){ //後ろのタスク
		p = p->mpNext;
		n = p->mpNext;
		if (p-> eName > n-> eName){
			CTask sp, sn;
			SwapTask(&p, &n);

			/*保存*/
			sp.mpPrev = p->mpPrev;
			sp.mpNext = p->mpNext;
			sn.mpPrev = n->mpPrev;
			sn.mpNext = n->mpNext;
			/*左回りに順番を変える*/
			p->mpPrev = sn.mpPrev;
			p->mpNext = sp.mpPrev;
			n->mpNext = sp.mpNext;
			n->mpPrev = sn.mpNext;
			/*前後の順番を変える*/
			if (p->mpPrev == 0){
				mpRoot = p;
			}
			if (n->mpNext == 0){	//入れ替えが終わりに行われた時
				mpTail = n;
			}
			/*入れ替えが中間の時*/
			if (p->mpPrev != 0){
				p->mpPrev->mpNext = p;
			}
			if (p->mpNext != 0){
				p->mpNext->mpPrev = p;
			}
			if (n->mpPrev != 0){
				n->mpPrev->mpNext = n;
			}
			if (n->mpNext != 0){
				n->mpNext->mpPrev = n;
			}
			p = mpRoot;
		}
	}
}

void CTaskManager::AllRender(){

	CTask *task;
	task = mpRoot;

	/*すべてのRender表示*/
	while (task != 0)
	{

		//Sort(&task);
		task->Render();
		task = task->mpNext;

	}


}


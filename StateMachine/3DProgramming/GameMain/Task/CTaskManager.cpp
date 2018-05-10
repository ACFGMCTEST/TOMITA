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
		mpTail = t;
		return;
	}
	/*2番目以上*/
	else {
		CTask *moveTask = mpRoot;//探すタスク
		/*追加する場所を探す*/
		while (moveTask)
		{
			if (moveTask->ePriority > t->ePriority){
				/*最初*/
				if (moveTask->mpPrev == 0) {
					moveTask->mpPrev = t;
					t->mpNext = moveTask;
					t->mpPrev = 0;
					mpRoot = t;
					return;
				}
				/*途中*/
				else {
					moveTask->mpPrev->mpNext = t;
					t->mpPrev = moveTask->mpPrev;
					moveTask->mpPrev = t;
					t->mpNext = moveTask;
					return;
				}
			}
			moveTask = moveTask->mpNext;
		
		}
		/*最後*/
		mpTail->mpNext = t;
		t->mpPrev = mpTail;
		mpTail = t;
		mpTail->mpNext = 0;
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
	//CCollisionManager col;
	task = mpRoot;
	
	/*すべてのRender表示*/
	while (task != 0)
	{
		task->Update();
		if (task->mCharaFlag){
			//col.Update((CBase*)task);
		}
		//if (task->mKillFlag){
			//Kill(&task);
		//}


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
		if (p-> ePriority > n-> ePriority){
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

void CTaskManager::AllBillboardRender(){
	CTask *task;
	task = mpRoot;

	/*すべてのRender表示*/
	while (task != 0)
	{
		task->BillboardRender();
		task = task->mpNext;
	}
}
//
//
//CTask *CTaskManager::GetTask(CTask::EMyNumber Num, int Count){
//	CTask *task;
//	task = mpRoot;//先頭から探す
//	while (task != 0)
//	{
//		if (task->mCount == Count && task->mMyNumber == Num) //指定した条件なら
//		return task;//値を返す
//		task  =  task->mpNext;//次に進む
//	}
//	return nullptr;//何もないのでnullptrを返す
//}

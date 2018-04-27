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
void CTaskManager::SwapTask(CTask **p, CTask **n){ //����ւ�����
	CTask *s = *n;
	*n = *p;
	*p = s;

}


CTaskManager::CTaskManager() :mpRoot(0), mpTail(0){}


CTaskManager::~CTaskManager(){

}
/*
�ǉ�����
���ɒǉ����Ă����`
�����菇
root == 0 ���@�����Ȃ��Ƃ�
root != 0 ��  ����Ƃ�
*/
void CTaskManager::Add(CTask  *t){
	/*�����ݒ肵�Ă��Ȃ��Ƃ�*/
	if (mpRoot == 0){
		/*���̐ݒ�*/
		mpRoot = t; 
		mpRoot->mpPrev = 0; 
		mpRoot->mpNext = 0;
		/*�K���̐ݒ�*/
		mpTail = t;
		return;
	}
	/*2�Ԗڈȏ�*/
	else {
		CTask *moveTask = mpRoot;//�T���^�X�N
		/*�ǉ�����ꏊ��T��*/
		while (moveTask)
		{
			if (moveTask->ePriority > t->ePriority){
				/*�ŏ�*/
				if (moveTask->mpPrev == 0) {
					moveTask->mpPrev = t;
					t->mpNext = moveTask;
					t->mpPrev = 0;
					mpRoot = t;
					return;
				}
				/*�r��*/
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
		/*�Ō�*/
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
�f���[�g����

�����Ӂ@Kill�̂ق��� " **t  �Ȃ̂Ŏg�����ɒ��ӂ��K�v  "

�v���O�����̏���

Task�̃A�h���X���n�܂�̎�
��
Task�̃A�h���X���I���̎�
��
Task�̃A�h���X�����Ԃ̎�


*/

void CTaskManager::Kill(CTask **t){

	CTask temp; //���ɍ�����
	CTask *T = &temp; //���Ԃ�����
	T->mpNext = mpRoot;

	/*���ԂɒT��*/
	while (T != mpTail)
	{
		T = T->mpNext;
		if (*t == T){ //T�Ƃ����Ă���Ƃ�
			/*�n�܂�*/
			if (T == mpRoot){ 

				mpRoot = mpRoot->mpNext;
				mpRoot->mpPrev = 0;

				P_DELETE(*t);
				/*�����̐ݒ��ς���*/
				*t = mpRoot;
				break;
			}
			/*�I���*/
			else if (T->mpNext == 0){
				mpTail = mpTail->mpPrev;
				mpTail->mpNext = 0;
				P_DELETE(*t);
				/*�����̐ݒ��ς���*/

				*t = mpTail;
				break;
			}
			/*����*/
			else{ 
				CTask *save_T; //���̕ۑ��ꏊ

				T->mpPrev->mpNext = T->mpNext;
				T->mpNext->mpPrev = T->mpPrev;

				save_T = T->mpPrev;
				/*�����̐ݒ��ς���*/
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
	
	/*���ׂĂ�Render�\��*/
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
/*�o�u���\�[�g*/
void CTaskManager::AbsR(){
	/*�o�u���\�[�g*/
	CTask temp;
	CTask *p = &temp;//���p
	CTask *n = &temp;//�O�p

	p->mpNext = mpRoot;
	n->mpNext = mpRoot;


	while (p->mpNext != mpTail){ //���̃^�X�N
		p = p->mpNext;
		n = p->mpNext;
		if (p-> ePriority > n-> ePriority){
			CTask sp, sn;
			SwapTask(&p, &n);

			/*�ۑ�*/
			sp.mpPrev = p->mpPrev;
			sp.mpNext = p->mpNext;
			sn.mpPrev = n->mpPrev;
			sn.mpNext = n->mpNext;
			/*�����ɏ��Ԃ�ς���*/
			p->mpPrev = sn.mpPrev;
			p->mpNext = sp.mpPrev;
			n->mpNext = sp.mpNext;
			n->mpPrev = sn.mpNext;
			/*�O��̏��Ԃ�ς���*/
			if (p->mpPrev == 0){
				mpRoot = p;
			}
			if (n->mpNext == 0){	//����ւ����I���ɍs��ꂽ��
				mpTail = n;
			}
			/*����ւ������Ԃ̎�*/
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

	/*���ׂĂ�Render�\��*/
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

	/*���ׂĂ�Render�\��*/
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
//	task = mpRoot;//�擪����T��
//	while (task != 0)
//	{
//		if (task->mCount == Count && task->mMyNumber == Num) //�w�肵�������Ȃ�
//		return task;//�l��Ԃ�
//		task  =  task->mpNext;//���ɐi��
//	}
//	return nullptr;//�����Ȃ��̂�nullptr��Ԃ�
//}

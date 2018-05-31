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
		mpTail = 0;
	}
	/*2�Ԗڂ̏���*/
	else if (mpTail == 0){
		/*���݂̂��̂��������ꍇ*/
		if (mpRoot-> eName < t-> eName){
			/*�K���̐ݒ�*/
			mpTail = t;
			mpTail->mpPrev = mpRoot;
			mpTail->mpNext = 0;
			/*���̐ݒ�*/
			mpRoot->mpPrev = 0;
			mpRoot->mpNext = mpTail;
			
		}
		/*���݂̂��̂��傫���ꍇ*/
		else{
			/*�K���̐ݒ�*/
			mpTail = mpRoot;
			mpTail->mpPrev = t;
			mpTail->mpNext = 0;
			/*���̐ݒ�*/
			mpRoot = t;
			mpRoot->mpPrev = 0;
			mpRoot->mpNext = mpTail;
		}
	}
	/*3�Ԗڈȏ�*/
	else if(mpRoot->mpNext != 0 && mpTail->mpPrev != 0){
		CTask temp;
		CTask *moveTask = &temp;//�T���^�X�N
		moveTask->mpNext = mpRoot;

		/*�ǉ�����ꏊ��T��*/
		while (moveTask != mpTail)
		{
			moveTask = moveTask->mpNext;


			/*�ŏ�*/
			if (mpRoot-> eName > t-> eName){
				/*�ǉ�������̐ݒ�*/
				t->mpPrev = 0;
				t->mpNext = mpRoot;
				/*���̃^�X�N�ݒ�*/
				mpRoot = t; 
				/*�T���^�X�N�ݒ�*/
				moveTask->mpPrev = t;
				if (moveTask->mpNext == 0){
					mpTail = moveTask;
				}

				break;
			}
			/*�Ō�*/
			else if (moveTask == mpTail){
				/*�����ېݒ�*/
				t->mpPrev = mpTail;
				mpTail->mpNext = t;
				mpTail = t;
				mpTail->mpNext = 0;
				break;
			} 
			/*����*/
			else if (moveTask-> eName <= t-> eName &&
					t-> eName <= moveTask->mpNext-> eName){
				/*�ǉ�������̐ݒ�*/
				t->mpNext = moveTask->mpNext;
				t->mpPrev = moveTask;
				/*�O���̃^�X�N�ݒ�*/
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
	task = mpRoot;
	
	/*���ׂĂ�Render�\��*/
	while (task != 0)
	{
		/*�폜�t���O�����Ə���*/
		if (task->mKillFlag){ Kill(&task); }
		task->Update();
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
		if (p-> eName > n-> eName){
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


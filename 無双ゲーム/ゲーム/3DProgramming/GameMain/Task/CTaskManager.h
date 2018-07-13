/*
*�^�X�N�̃}�l�[�W���[�̃v���O����
*�S���ҁ@�y�c���l
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
	//�f�o�b�N�p�@���݊i�[����Ă��鐔��\��
	void PrintCount(char *str) {
		CTask *task;
		task = mpRoot;
		int i = 0;
		while (task != 0)
		{
			i++;
			task = task->mpNext;
		}
		printf("%s��%d�ł�\n", str, i);
	}
	~CTaskManager();

	/*
	�ǉ�����
	���ɒǉ����Ă����`
	�����菇
	root == 0 ���@�����Ȃ��Ƃ�
	root != 0 ��  ����Ƃ�
	*/
	void Add(CTask  *t);

	/*
	�g����
	Abs�͏����@
	R��Rebder�p
	U��Update�p
	*/
	void AbsR();




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

	void Sort(CTask *t);
	
	void AllKill();
	void AllUpdate();
	void AllRender();
	void AllMiniMapRender();
	void AllInit();
	/*�ق�������
	Num �ق��������w��
	Count �����ԍ�
	*/
};

#endif

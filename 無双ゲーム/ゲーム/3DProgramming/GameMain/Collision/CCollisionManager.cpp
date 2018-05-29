
#include "../Scene/GameScene/CharaDate/CSceneModel.h"
#include "../../GameMain/Scene/CSceneManager.h"
#include "CCollisionManager.h"
#include "CCollision.h"
#include "ColType\CColCapsule.h"
#include "ColType\CColSphere.h"
/*�R���X�g���N�^*/
CCollisionManager::CCollisionManager() {}
CCollisionManager* CCollisionManager::mCollisionManager = 0;

//GetInstance
CCollisionManager* CCollisionManager::GetInstance() {
	if (mCollisionManager == 0) {
		mCollisionManager = new CCollisionManager();
	}
	return mCollisionManager;
}
/*�ǉ�����*/
void CCollisionManager::Add(CColBase *t){
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
		if (mpRoot->mType < t->mType){
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
	else if (mpRoot->mpNext != 0 && mpTail->mpPrev != 0){
		CTask temp;
		CTask *moveTask = &temp;//�T���^�X�N
		moveTask->mpNext = mpRoot;

		/*�ǉ�����ꏊ��T��*/
		while (moveTask != mpTail)
		{
			moveTask = moveTask->mpNext;


			/*�ŏ�*/
			if (mpRoot->mType > t->mType){
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
			else if (moveTask->mType <= t->mType &&
				t->mType <= moveTask->mpNext->mType){
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
	//CTaskManager::Add(col);
}

/*�n�`�̓����蔻�肵�Ȃ����������߂�*/
bool CCollisionManager::FlagMap(const CColBase &task,const CColBase &map){
	CXCharPlayer *pl = dynamic_cast<CXCharPlayer*>(task.mpParent);
	/*�O�p�`�̃|���S���̏ꍇ�}�b�v*/
	if (map.mType == CTask::COL_TRIANGLE){
		/*�}�b�v�łȂ����̈ʒu���画�肷��}�b�v�̃|���S�����̕������߂�*/
		int taskNum;//�v���C���[�̍��W����ԍ�����肷��
		int mapPrev;//
		int mapTail;
		/*if (){
			return true;
		}*/
		//printf("�|�W�V����%f,%f,%f\n", pl->mPosition.x, pl->mPosition.y, pl->mPosition.z);
		//return false;
		//return true;
	}
	else{
		return true;
	}
}

/*�X�V����*/
void CCollisionManager::Update(){

	CColBase *task;
	task = (CColBase*)mpRoot;

	/*�T������*/
	while (task != 0)
	{
		//���g�̃R���C�_�^�C�v������
		switch (task->mType) {
		case CColBase::COL_CAPSULE:
			//�ω����Ȃ��R���C�_�͏Փ˔��肵�Ȃ�
			if (task->mpCombinedMatrix) {
				//�R���C�_���R�s�[���čX�V
				CColCapsule cc = (*(CColCapsule*)task).GetUpdate();
				//�R���C�_��擪����Փ˔��肵�Ă���
				CColBase *n = (CColBase*)mpRoot;
				while (n != NULL) {
					//�e�̃^�X�N�ŏՓ˔��肳����
					if (task->mpParent && task != n) {
						task->mpParent->Collision(&cc, n);
					}
					n = (CColBase*)n->mpNext;
				}
			}
			break;
		case CColBase::COL_BOX:
			break;
		case CColBase::COL_SPHEPE:
			//�ω����Ȃ��R���C�_�͏Փ˔��肵�Ȃ�
			if (task->mpCombinedMatrix) {
				//�R���C�_���R�s�[���čX�V
				CColSphere cc = (*(CColSphere*)task).GetUpdate();
				//�R���C�_��擪����Փ˔��肵�Ă���
				CColBase *n = (CColBase*)mpRoot;
				while (n != NULL) {
					//�e�̃^�X�N�ŏՓ˔��肳����
					if (task->mpParent && task != n) {
						task->mpParent->Collision(&cc, n);
					}
					n = (CColBase*)n->mpNext;
				}
			}
			break;
		}
		task = (CColBase*)task->mpNext;
	}

#ifdef _DEBUG 
	AllRender();
#endif
}

CCollisionManager::~CCollisionManager(){
	AllKill();
}

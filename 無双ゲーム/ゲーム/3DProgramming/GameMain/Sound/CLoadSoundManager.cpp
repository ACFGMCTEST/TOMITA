#include "CLoadSoundManager.h"


CLoadSoundManager *CLoadSoundManager::mpLoadSoundManager = 0;
//GetInstance
CLoadSoundManager* CLoadSoundManager::GetInstance() {
	if (mpLoadSoundManager == 0) {
		mpLoadSoundManager = new CLoadSoundManager();
	}
	return mpLoadSoundManager;
}

//�t�@�C���ǂݍ���
void CLoadSoundManager::Load(char *name) {
	mSound.push_back(new CSound(name));
	mName.push_back(name);
}

CLoadSoundManager::CLoadSoundManager() {
	Load(BGM_GAME_MAIN);//�Q�[�����C�������ŗ�������
	Load(SE_PUNCH);//�p���`��
	Load(SE_DAMAGE);//�_���[�W��
	Load(SE_PL_DAMAGE);//plaeyr�_���[�W��
	Load(SE_FALL);//�����_���[�W
	Load(SE_CURSOR_MOVE);//�J�[�\���ړ�
	Load(SE_DECISION);//���艹
	Load(SE_ENTER);//�G���^�[��
}

//�T�E���h�Ăяo��
CSound *CLoadSoundManager::Sound(char *name) {


#define CLASS CLoadSoundManager::GetInstance()
	for (int i = 0; i < CLASS->mSound.size(); i++)
	{
		//�l�[������v�����ꍇ
		if (CLASS->mName[i] == name) {
			return CLASS->mSound[i];
		}
	}

	printf("%s�͂���܂���\n", name);
	return nullptr;
}

CLoadSoundManager::~CLoadSoundManager() {}

#ifndef SOUND_LOAD_MANAGER_HPP
#define SOUND_LOAD_MANAGER_HPP

#include "CSound.h"
#include <string>
#include <vector>       // �w�b�_�t�@�C���C���N���[�h

#define BGM_GAME_MAIN   BGM_FILE"BGM.mp3"//BGM
#define SE_PUNCH		SE_FILE"PunchSwing.mp3"//�p���`��
#define SE_DAMAGE		SE_FILE"Damage.mp3"//�_���[�W��
#define SE_PL_DAMAGE	SE_FILE"PlayerDamage.mp3"//�_���[�W��
#define SE_FALL			SE_FILE"FallDamage.mp3"//������
#define SE_DECISION		SE_FILE"Decision.mp3"//���艹
#define SE_CURSOR_MOVE	SE_FILE"CursorMove.mp3"//�J�[�\���ړ���
#define SE_ENTER		SE_FILE"Enter.mp3"//�G���^�[��


//�T�E���h�̓�������N���X
class  CLoadSoundManager
{
private:
	//�T�E���h��ǉ����Ă���
	std::vector<CSound*> mSound;
	//���O���w�肷��Ƃ��Ɏg��
	std::vector<std::string> mName;
 
	//�t�@�C���ǂݍ���
	void Load(char *name);
	CLoadSoundManager();

	static CLoadSoundManager *mpLoadSoundManager;

public:
	
	static CLoadSoundManager *GetInstance(); //GetInstance

	//�����̖��O�̃T�E���h�t�@�C����Ԃ� .mp3
	static CSound *Sound(char*name);

	~ CLoadSoundManager();

};

#endif
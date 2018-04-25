#ifndef SOUND_HPP
#define SOUND_HPP
#include<Windows.h>
#include<mmsystem.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")


/*���y�t�@�C���ꏊ*/
#define SOUND_FILE "SoundFile"
#define BGM_FILE SOUND_FILE"\\Bgm.mp3" //BGM
#define SE_ATTACK_FILE SOUND_FILE"\\Attack.mp3" //�U����
#define SE_BUTTON_FILE SOUND_FILE"\\Button.mp3" //�{�^����
#define SE_DAMAGE_FILE SOUND_FILE"\\Damage.mp3" //�_���[�W��
#define SE_GOAL_FILE SOUND_FILE"\\Goal.mp3" //�S�[����
#define SE_REFLECT_FILE SOUND_FILE"\\Reflect.mp3" //���˕Ԃ艹
#define SE_CLEAR_FILE SOUND_FILE"\\SE_GameClear.mp3" //�N���A�[��
#define SE_OVER_FILE SOUND_FILE"\\SE_GameOver.mp3" //�I�[�o�[��
/*�J�n�ʒu(�b��)*/
#define SE_START_ATTACK_TIME 0.1
#define SE_START_CLEAR_TIME 0.2
#define SE_START_OVER_TIME 0.2
#define SE_START_GOAL_TIME 0

///*�T�E���h�N���X*/
class CSound{
private:
	/*�Z�b�g*/
	void Sendstring(char *w);
public:
	char	file[100];
	int result;
	float MaxTime; //����
	float Count;//���ԃJ�E���g

	CSound();

	/*�ǂݍ��݊֐�*/
	void Load(char *filename);
	/*���炷*/
	void Play();
	/*��񎞊Ԏw��炷
	float startTime = �Đ����Ԉʒu
	*/
	//void Play(float startTime);

	/*BGM�p���[�v*/
	void Repeat();
	/*�X�g�b�v�֐�*/
	void Stop();
	/*���y�����֐�*/
	void Close();

	~CSound();

};
#endif
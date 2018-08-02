#ifndef SOUND_HPP
#define SOUND_HPP
#include<Windows.h>
#include<mmsystem.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")
/*�T�E���h�t�@�C��*/
#define SOUND_FILE "../Sound\\"
#define SE_FILE SOUND_FILE"SE\\"//���ʉ��̃t�@�C��
#define BGM_FILE SOUND_FILE"BGM\\"//BGM�̃t�@�C��


class CSound{
private:
	char	file[100];
	int result;
	float MaxTime; //����
	float Count;//���ԃJ�E���g
	//�ϊ��p
	void Sendstring(char *w);
public:
	

	CSound();
	~CSound();
	CSound(char *fileName) { Load(fileName); }
	
	void Load(char *filename);
	
	//������Ăяo���Ă�pley���͖炳�Ȃ�
	void OnePlay();
	//�Ă΂�邽�я��߂���炵������
	void Play();
	//��������s�[�g����
	void Repeat();
	//�~�߂�
	void Stop();
	//����
	void Close();
	//�t�@�C�����擾
	char *File() { return file; }

};
#endif
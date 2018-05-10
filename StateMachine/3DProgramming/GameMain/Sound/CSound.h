#ifndef SOUND_HPP
#define SOUND_HPP
#include<Windows.h>
#include<mmsystem.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")


class CSound{
private:
public:
	char	file[100];
	int result;
	float MaxTime; //ŽžŠÔ
	float Count;//ŽžŠÔƒJƒEƒ“ƒg

	CSound();

	void Sendstring(char *w);

	void Load(char *filename);

	void Play();

	void Repeat();

	void Stop();

	void Close();

	~CSound();

};
#endif
#ifndef SOUND_HPP
#define SOUND_HPP
#include<Windows.h>
#include<mmsystem.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")
/*サウンドファイル*/
#define SOUND_FILE "../Sound\\"
#define SE_FILE SOUND_FILE"SE\\"//効果音のファイル
#define BGM_FILE SOUND_FILE"BGM\\"//BGMのファイル


class CSound{
private:
	char	file[100];
	int result;
	float MaxTime; //時間
	float Count;//時間カウント
	//変換用
	void Sendstring(char *w);
public:
	

	CSound();
	~CSound();
	CSound(char *fileName) { Load(fileName); }
	
	void Load(char *filename);
	
	//何回も呼び出してもpley中は鳴らさない
	void OnePlay();
	//呼ばれるたび初めから鳴らし続ける
	void Play();
	//何回もリピートする
	void Repeat();
	//止める
	void Stop();
	//閉じる
	void Close();
	//ファイル名取得
	char *File() { return file; }

};
#endif
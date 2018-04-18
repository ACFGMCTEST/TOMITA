#ifndef SOUND_HPP
#define SOUND_HPP
#include<Windows.h>
#include<mmsystem.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")


/*音楽ファイル場所*/
#define SOUND_FILE "SoundFile"
#define BGM_FILE SOUND_FILE"\\Bgm.mp3" //BGM
#define SE_ATTACK_FILE SOUND_FILE"\\Attack.mp3" //攻撃音
#define SE_BUTTON_FILE SOUND_FILE"\\Button.mp3" //ボタン音
#define SE_DAMAGE_FILE SOUND_FILE"\\Damage.mp3" //ダメージ音
#define SE_GOAL_FILE SOUND_FILE"\\Goal.mp3" //ゴール音
#define SE_REFLECT_FILE SOUND_FILE"\\Reflect.mp3" //跳ね返り音

///*サウンドクラス*/
class CSound{
private:
	/*セット*/
	void Sendstring(char *w);
public:
	char	file[100];
	int result;
	float MaxTime; //時間
	float Count;//時間カウント

	CSound();

	/*読み込み関数*/
	void Load(char *filename);
	/*一回鳴らす*/
	void Play();
	/*BGM用ループ*/
	void Repeat();
	/*ストップ関数*/
	void Stop();
	/*音楽を閉じる関数*/
	void Close();

	~CSound();

};
#endif
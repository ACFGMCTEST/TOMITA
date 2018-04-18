#include "CSound.h"
#include <string>

CSound::CSound()
{
	MaxTime = 0;
	Count = 0;
	result = 0;
}

void CSound::Sendstring(char *w){
	char buf[100];

	sprintf_s(buf, sizeof(buf), w, file);
	mciSendString((LPSTR)buf, NULL, sizeof(buf), NULL);
	
	//再生時間がすべて来たら
	//if (MaxTime == 0){
	//	char T[100];
	//	sprintf_s(buf, sizeof(buf), "status %s length", file);//時間取得
	//	mciSendString((LPSTR)buf, T, sizeof(T), NULL);
	//	MaxTime = atof(T) / 2000;
	//}

}

void CSound::Load(char *filename)
{
	//ファイルポインタの作成
	FILE *fp;
	//ファイルオープン
	fp = fopen(filename, "rb");
	//エラーのときはリターン
	if (!fp) {
		printf("file not found:%s\n", filename);
		return;
	}
	else{
		strcpy_s(file, filename);
		Sendstring("close %s");
		Sendstring("open %s");
	}
}
void CSound::Play()
{
	Sendstring("play %s from 0");
}
/*時間指定*/
void CSound::Play(float startTime)
{
	int time = startTime * 1000;//時間が1000単位なのでここで調整
	std::string s1 = "play %s from ";//鳴らす前部分
	std::string buf = s1 + std::to_string(time);//時間を後ろにつける
	char* cstr = new char[buf.size() + 1]; // メモリ確保
	std::char_traits<char>::copy(cstr, buf.c_str(), buf.size() + 1);//Charポインタに変換
	Sendstring(cstr);//プレイ
	delete[] cstr; // メモリ解放

}

void CSound::Repeat()
{
	Sendstring("play %s from 1 repeat");

}

void CSound::Stop()
{
	Sendstring("stop %s");
}

void CSound::Close()
{
	Sendstring("close %s");

}

CSound::~CSound()
{
	Stop();
	Close();
}
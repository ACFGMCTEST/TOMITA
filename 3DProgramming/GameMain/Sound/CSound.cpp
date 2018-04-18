#include "CSound.h"

CSound::CSound()
{
	MaxTime = 0;
	Count = 0;
	result = 0;
}

void CSound::Sendstring(char *w){
	char buf[100];

	sprintf_s(buf, sizeof(buf), w, file);
	mciSendString((LPCTSTR)buf, NULL, sizeof(buf), NULL);
	
	////再生時間がすべて来たら
	//if (MaxTime == 0){
	//	char T[100];
	//	sprintf_s(buf, sizeof(buf), "status %s length", file);//時間取得
	//	mciSendString((LPCTSTR)buf, (LPTSTR)T, sizeof(T), NULL);
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
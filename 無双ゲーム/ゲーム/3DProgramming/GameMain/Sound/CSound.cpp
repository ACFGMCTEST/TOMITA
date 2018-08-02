#include "CSound.h"

CSound::CSound()
{
	MaxTime = 0;
	Count = 0;
	result = 0;
}

void CSound::Sendstring(char *w){
	char buf[100];

	//wchar_t		buf[100];
	//wsprintf((LPSTR)buf, (LPCSTR)w, file);
	//if (Count == 0 || w != "play %s from 0"){
	sprintf_s(buf, sizeof(buf), w, file);
	mciSendString((LPCTSTR)buf, NULL, sizeof(buf), NULL);
	//}
	//
	//Ä¶ŠÔ‚ª‚·‚×‚Ä—ˆ‚½‚ç
	if (MaxTime == 0){
		char T[100];
		sprintf_s(buf, sizeof(buf), "status %s length", file);//ŠÔæ“¾
		mciSendString((LPCTSTR)buf, (LPTSTR)T, sizeof(T), NULL);
		MaxTime = atof(T) / 2000;
	}
}

void CSound::Load(char *filename)
{
	//wcscpy(file, filename);
	strcpy_s(file, filename);
	Sendstring("close %s");
	Sendstring("open %s");
}

void CSound::Play()
{
	Sendstring("play %s from 0");
}

void CSound::OnePlay()
{
	char buf[100];//•¶š—ñŠi”[
	char T[100];//play‚©”»’f
	sprintf_s(buf, sizeof(buf), "status %s mode", file);//ó‘ÔŠm”F
	mciSendString((LPCTSTR)buf, (LPTSTR)T, sizeof(T), NULL);
	//‚È‚Á‚Ä‚¢‚éó‘Ô‚¶‚á‚È‚¢‚É–Â‚ç‚·
	if (strcmp(T, "playing")) {
		Sendstring("play %s from 0");
		printf("%s\n", T);
	}
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
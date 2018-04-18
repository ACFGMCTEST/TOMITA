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
	
	//�Đ����Ԃ����ׂė�����
	//if (MaxTime == 0){
	//	char T[100];
	//	sprintf_s(buf, sizeof(buf), "status %s length", file);//���Ԏ擾
	//	mciSendString((LPSTR)buf, T, sizeof(T), NULL);
	//	MaxTime = atof(T) / 2000;
	//}

}

void CSound::Load(char *filename)
{
	//�t�@�C���|�C���^�̍쐬
	FILE *fp;
	//�t�@�C���I�[�v��
	fp = fopen(filename, "rb");
	//�G���[�̂Ƃ��̓��^�[��
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
/*���Ԏw��*/
void CSound::Play(float startTime)
{
	int time = startTime * 1000;//���Ԃ�1000�P�ʂȂ̂ł����Œ���
	std::string s1 = "play %s from ";//�炷�O����
	std::string buf = s1 + std::to_string(time);//���Ԃ����ɂ���
	char* cstr = new char[buf.size() + 1]; // �������m��
	std::char_traits<char>::copy(cstr, buf.c_str(), buf.size() + 1);//Char�|�C���^�ɕϊ�
	Sendstring(cstr);//�v���C
	delete[] cstr; // ���������

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
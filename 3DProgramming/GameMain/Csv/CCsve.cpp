#include "CCsv.h"
#include "../../Define/Define.h"
#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //�����X�g���[��

using namespace std;//C++�W�����C�u�����̖��O���


/*�R���X�g���N�^*/
CCsv::CCsv():mSize(0),mLine(0),mRow(0),mpData(0){}
/*�f�X�g���N�^*/
CCsv::~CCsv(){
	/*new�������̂�������*/
	for (int i = 0; i < mSize; i++){
		P_DELETE(mpData);
	}
	mLine = 0;
	mRow = 0;
	mSize = 0;
}
/*�ǂݍ��݊֐�*/
void CCsv::Load(char *filename){
	//�t�@�C���̓ǂݍ���
	ifstream ifs(filename);
	if (!ifs){
		printf("%c�͓ǂݍ��߂܂���\n", filename);
	}
	/*�i�[�f�[�^*/
	string get;
	//csv�t�@�C����1�s���ǂݍ���
	string str;
	while (getline(ifs, str)){

		string token;
		istringstream stream(str);


		//1�s�̂���,������ƃR���}�𕪊�����
		while (getline(stream, token, ',')){
			
			/*�ǉ����Ă���*/
			get += token;
			//}
			/*�s�����͂���Ă��Ȃ��ꍇ�͉����𑫂��Ă���*/
			if (mLine == 0)mRow++;
			/*�T�C�Y�𑫂��Ă���*/
			mSize++;

		}
		mLine++;//�s�𑫂��Ă���
	}



	/*�f�[�^�i�[���Ă���*/
	mpData = new char[mSize + 1];
	/*char�ϊ�*/
	strcpy(mpData, get.c_str());


	/*�f�o�b�N�p*/
	DataPrintf();
}

void CCsv::DataPrintf(){
	/*�f�o�b�N�p*/
#ifdef _DEBUG 
	for (int y = 0; y < mLine; y++)
	{
		for (int x = 0; x < mRow; x++)
		{
			printf("%c", mpData[x + (mRow*y)]);
		}
		printf("\n");
	}
#endif
}


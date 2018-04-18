#include "CCsv.h"
#include "../../Define/Define.h"
#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //文字ストリーム

using namespace std;//C++標準ライブラリの名前空間


/*コンストラクタ*/
CCsv::CCsv():mSize(0),mLine(0),mRow(0),mpData(0){}
/*デストラクタ*/
CCsv::~CCsv(){
	/*newしたものを初期化*/
	for (int i = 0; i < mSize; i++){
		P_DELETE(mpData);
	}
	mLine = 0;
	mRow = 0;
	mSize = 0;
}
/*読み込み関数*/
void CCsv::Load(char *filename){
	//ファイルの読み込み
	ifstream ifs(filename);
	if (!ifs){
		printf("%cは読み込めません\n", filename);
	}
	/*格納データ*/
	string get;
	//csvファイルを1行ずつ読み込む
	string str;
	while (getline(ifs, str)){

		string token;
		istringstream stream(str);


		//1行のうち,文字列とコンマを分割する
		while (getline(stream, token, ',')){
			
			/*追加していく*/
			get += token;
			//}
			/*行が入力されていない場合は横幅を足していく*/
			if (mLine == 0)mRow++;
			/*サイズを足していく*/
			mSize++;

		}
		mLine++;//行を足していく
	}



	/*データ格納していく*/
	mpData = new char[mSize + 1];
	/*char変換*/
	strcpy(mpData, get.c_str());


	/*デバック用*/
	DataPrintf();
}

void CCsv::DataPrintf(){
	/*デバック用*/
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


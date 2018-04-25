/*
担当者　冨田健斗
*/
#ifndef CSV_HPP
#define CSV_HPP

/*ファイル場所*/
#define CSV_FILE_MAP0	"MapData\\map0.csv"
#define CSV_FILE_MAP1	"MapData\\map1.csv"
#define CSV_FILE_MAP2	"MapData\\map2.csv"
#define CSV_FILE_MAP3	"MapData\\map3.csv"

/*CSV読み込みクラス*/
class CCsv{
public:

	char *mpData;//データ格納用
	int mSize;//サイズ格納
	int mLine, mRow;//二次元配列で使う 縦幅,横幅


	/*読み込み関数*/
	void Load(char *filename);
	/*デバック用*/
	void DataPrintf();

	CCsv();
	~CCsv();

};
#endif
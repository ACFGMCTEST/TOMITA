/*
�S���ҁ@�y�c���l
*/
#ifndef CSV_HPP
#define CSV_HPP

/*�t�@�C���ꏊ*/
#define CSV_FILE_MAP0	"MapData\\map0.csv"
#define CSV_FILE_MAP1	"MapData\\map1.csv"
#define CSV_FILE_MAP2	"MapData\\map2.csv"
#define CSV_FILE_MAP3	"MapData\\map3.csv"

/*CSV�ǂݍ��݃N���X*/
class CCsv{
public:

	char *mpData;//�f�[�^�i�[�p
	int mSize;//�T�C�Y�i�[
	int mLine, mRow;//�񎟌��z��Ŏg�� �c��,����


	/*�ǂݍ��݊֐�*/
	void Load(char *filename);
	/*�f�o�b�N�p*/
	void DataPrintf();

	CCsv();
	~CCsv();

};
#endif
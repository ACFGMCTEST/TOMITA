/*
いろいろ便利な関数
math.hにない機能をここに追加していく

時間計測など
*/
#ifndef CONVIENIENT_HPP
#define CONVIENIENT_HPP
#include "../Define/Define.h"


class CConvenient
{
private:
	
	CConvenient(){}
	~CConvenient(){}
public:
	/*
	max,minを超えるものは最大値にする
	max = 最大値
	min  =最小値
	equal = equalするもの
	*num = 変更する数
	*/
	static  void LimitEqual(float *num,float equal,float max,float min);

	/*
	簡易時間計測関数
	countは 各自のクラス内であらかじめ定義しないといけない
	sizeは 時間設定
	*/
	static bool Time(float *count, float size);

	/*プラスマイナス判断関数
	f　がminusだと -1を返す
	f　がplusだと 1を返す
	f  が0だと1を返す
	*/
	static float plmi(float const &f);

	/*最大を越したら最初からから足していく　
	最小を越したら最大から引いていく関数
	
	num = 足されるもの

	add = 足すもの

	limitMax = 最大値

	limitMinus = 最小値

	*/
	static void LoopPlus(float *num, float add, float limitMax,float limitMinus);


};
#endif
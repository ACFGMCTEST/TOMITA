#include "CConvenient.h"


/*
最大を超えるものは最大値にする
limit = 最大値
*num = 変更する数
*/
void CConvenient::LimitEqual(float *num, float equal, float max,float min){
	*num = equal;
	/*最大値を超えると最大値にする*/
	if (*num >= max){
		*num = max;
	}
	/*最小値より下になると最小値に*/
	if (*num <= min){
		*num = min;
	}
}

bool CConvenient::Time(float *count, float size){
	*count += 1.0f / FPS;
	if (*count >= size){
		return true;
	}
	else{
		return false;
	}
}

float CConvenient::plmi(float const &f){
	if (f < 0){ //fがminus場合
		return -1;
	}
	else if (f > 0){//plusのばあい
		return 1;
	}
	else{//0の場合
		return 0;
	}
}

/*最大を越したら最初からから足していく　
最小を越したら最大から引いていく関数*/
void CConvenient::LoopPlus(float *num, float add, float limitMax, float limitMinus){

	*num += add;//足す
	/*多い場合*/
	if (limitMax <= *num){
		*num = (*num - limitMax) + limitMinus;
		return;
	}
	/*少ない場合*/
	if (limitMinus > *num){
		*num = (limitMax + *num) + limitMinus;
		
	}
}

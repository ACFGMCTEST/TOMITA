#include "CConvenient.h"


/*
�ő�𒴂�����͍̂ő�l�ɂ���
limit = �ő�l
*num = �ύX���鐔
*/
void CConvenient::LimitEqual(float *num, float equal, float max,float min){
	*num = equal;
	/*�ő�l�𒴂���ƍő�l�ɂ���*/
	if (*num >= max){
		*num = max;
	}
	/*�ŏ��l��艺�ɂȂ�ƍŏ��l��*/
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
	if (f < 0){ //f��minus�ꍇ
		return -1;
	}
	else if (f > 0){//plus�̂΂���
		return 1;
	}
	else{//0�̏ꍇ
		return 0;
	}
}

/*�ő���z������ŏ����炩�瑫���Ă����@
�ŏ����z������ő傩������Ă����֐�*/
void CConvenient::LoopPlus(float *num, float add, float limitMax, float limitMinus){

	*num += add;//����
	/*�����ꍇ*/
	if (limitMax <= *num){
		*num = (*num - limitMax) + limitMinus;
		return;
	}
	/*���Ȃ��ꍇ*/
	if (limitMinus > *num){
		*num = (limitMax + *num) + limitMinus;
		
	}
}

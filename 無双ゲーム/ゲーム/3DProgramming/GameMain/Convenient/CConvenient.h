/*
���낢��֗��Ȋ֐�
math.h�ɂȂ��@�\�������ɒǉ����Ă���

���Ԍv���Ȃ�
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
	max,min�𒴂�����͍̂ő�l�ɂ���
	max = �ő�l
	min  =�ŏ��l
	equal = equal�������
	*num = �ύX���鐔
	*/
	static  void LimitEqual(float *num,float equal,float max,float min);

	/*
	�ȈՎ��Ԍv���֐�
	count�� �e���̃N���X���ł��炩���ߒ�`���Ȃ��Ƃ����Ȃ�
	size�� ���Ԑݒ�
	*/
	static bool Time(float *count, float size);

	/*�v���X�}�C�i�X���f�֐�
	f�@��minus���� -1��Ԃ�
	f�@��plus���� 1��Ԃ�
	f  ��0����1��Ԃ�
	*/
	static float plmi(float const &f);

	/*�ő���z������ŏ����炩�瑫���Ă����@
	�ŏ����z������ő傩������Ă����֐�
	
	num = ����������

	add = ��������

	limitMax = �ő�l

	limitMinus = �ŏ��l

	*/
	static void LoopPlus(float *num, float add, float limitMax,float limitMinus);


};
#endif
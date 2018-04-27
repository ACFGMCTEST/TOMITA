/*�쐬�ҁ@�y�c���l*/
#ifndef CINPUT_H
#define CINPUT_H

#include "GLFW/glfw3.h"

class CInput {
private:
	static int mButtonNum;
	static int mAxisNum;
	static const unsigned char* mpButtons;
	static const float* mpPositions;
public:
	CInput();
	 void Update();
	/*�L�[�̊���U��*/
	 /*���f�p*/
	 /*�ς���悤*/
	enum  eChangeKey
	{
		E_ENTER = 1,
		E_ATTACK = 5,
		E_PAUSE = 9,
		
		E_STICK1_LEFT = 0,
		E_STICK1_UP = 1,
		E_STICK1_RIGHT = 0,
		E_STICK1_DOWN = 1,

		E_STICK2_LEFT = 2,
		E_STICK2_UP = 3,
		E_STICK2_RIGHT = 2,
		E_STICK2_DOWN = 3,
	};
	/*�L�[����ϊ��֐�
	Input�Ɠ����Ɏg��
	CKey �Ŏg��
	*/
	static char ChangeInputKey(char k);
	static bool InputButton(int i);//�{�^��
	/*
	int i���ǂ��܂�
	float max�� �͂̓���
	�}�C�i�X��,���Ə�
	�v���X��  ,�E�Ɖ�
	*/
	static bool InputStick(int i,float max);//�X�e�B�b�N

};


#endif

/*作成者　冨田健斗*/
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
	/*キーの割り振り*/
	 /*判断用*/
	 /*変えるよう*/
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
	/*キー操作変換関数
	Inputと同時に使う
	CKey で使う
	*/
	static char ChangeInputKey(char k);
	static bool InputButton(int i);//ボタン
	/*
	int iがどこまで
	float maxが 力の入れ具合
	マイナスが,左と上
	プラスが  ,右と下
	*/
	static bool InputStick(int i,float max);//スティック

};


#endif

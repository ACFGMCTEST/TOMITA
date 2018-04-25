/*作成者　冨田健斗*/
#ifndef KEY_HPP
#define KEY_HPP
#include <windows.h>
#include "CInput.h"
#define KEY(c)  GetKeyState(c) & 0x8000	//キーボードが押されているか判定するマクロ関数


class CKey {
private:
	static bool flg[256];
	bool OnceFlag[256];
public:

	static CInput Input; //コントローラーの奴
	static bool push(char k);
	static bool once(char k);
	/*
	一度のボタンに複数の機能を入れるため
	
	インスタンス変数を作成して使う
	*/
	bool Onces(char k);
	bool Pushs(char k);
	
	
};


#endif

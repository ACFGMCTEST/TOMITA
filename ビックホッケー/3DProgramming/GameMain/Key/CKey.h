/*�쐬�ҁ@�y�c���l*/
#ifndef KEY_HPP
#define KEY_HPP
#include <windows.h>
#include "CInput.h"
#define KEY(c)  GetKeyState(c) & 0x8000	//�L�[�{�[�h��������Ă��邩���肷��}�N���֐�


class CKey {
private:
	static bool flg[256];
	bool OnceFlag[256];
public:

	static CInput Input; //�R���g���[���[�̓z
	static bool push(char k);
	static bool once(char k);
	/*
	��x�̃{�^���ɕ����̋@�\�����邽��
	
	�C���X�^���X�ϐ����쐬���Ďg��
	*/
	bool Onces(char k);
	bool Pushs(char k);
	
	
};


#endif

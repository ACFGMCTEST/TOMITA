/*�쐬�ҁ@�y�c���l*/
#ifndef MOUSE_HPP
#define MOUSE_HPP
#include "../Vector/CVector2.h"
#include "../Graphic/CRectangle2.h"

#include "GLFW/glfw3.h"
#include <Windows.h>

class CMouse
{
private:
	static CMouse *mpMouse;
public:
	static CMouse *GetInstance();

	CVector2 mPos;
	bool mLeftFlag; //�����ƍ��N���b�N
	bool mOneLeftFlag; //��񂾂����N���b�N
	
	CRectangle2 mRect;//�l�p�`
	bool CMouse::mClipFlag; //��ʓ��ɂƂǂ߂邩�ۂ��@true���ƂƂǂ߂�
	
	CMouse();
	~CMouse();
	void Update();

	void Render();
	
	void SetMousePos(float x, float y);

};

#endif
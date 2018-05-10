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
	static GLFWwindow* window;//�A�N�Z�X�p
public:

	static CVector2 mPos;
	static bool mLeftFlag; //�����ƍ��N���b�N
	static bool mOneLeftFlag; //��񂾂����N���b�N
	static CRectangle2 mRect;//�l�p�`
	static bool CMouse::mClipFlag; //��ʓ��ɂƂǂ߂邩�ۂ��@true���ƂƂǂ߂�
	static float mDirection;
	
	CMouse();
	~CMouse();
	static void Update();

	static void Render();
	static void SetMousePos(float x, float y);

	static void Access(GLFWwindow *win);

	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void SetWindow(GLFWwindow* window);
	static void Update(GLFWwindow* window);

};

#endif
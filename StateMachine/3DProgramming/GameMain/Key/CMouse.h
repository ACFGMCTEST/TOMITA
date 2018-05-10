/*作成者　冨田健斗*/
#ifndef MOUSE_HPP
#define MOUSE_HPP
#include "../Vector/CVector2.h"
#include "../Graphic/CRectangle2.h"

#include "GLFW/glfw3.h"
#include <Windows.h>

class CMouse
{
private:
	static GLFWwindow* window;//アクセス用
public:

	static CVector2 mPos;
	static bool mLeftFlag; //ずっと左クリック
	static bool mOneLeftFlag; //一回だけ左クリック
	static CRectangle2 mRect;//四角形
	static bool CMouse::mClipFlag; //画面内にとどめるか否か　trueだととどめる
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
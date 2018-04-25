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
	static CMouse *mpMouse;
public:
	static CMouse *GetInstance();

	CVector2 mPos;
	bool mLeftFlag; //ずっと左クリック
	bool mOneLeftFlag; //一回だけ左クリック
	
	CRectangle2 mRect;//四角形
	bool CMouse::mClipFlag; //画面内にとどめるか否か　trueだととどめる
	
	CMouse();
	~CMouse();
	void Update();

	void Render();
	
	void SetMousePos(float x, float y);

};

#endif
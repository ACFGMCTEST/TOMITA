//タイトルのプログラミング
//担当者　高橋弘樹 && 冨田健斗

#ifndef TITLESCENE_HPP
#define TITLESCENE_HPP

#include "../Define/define.h"
#include "CTitle.h"
#include "../../Scene/CScene.h"


class CTitleScene :public CScene{
private:
	CTitle mTitle;

	~CTitleScene();
	void Update();
public:
	CTitleScene();
};
#endif
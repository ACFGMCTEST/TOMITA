#ifndef TITLESCENE_HPP
#define TITLESCENE_HPP

#include "../Define/define.h"
#include "CTitle.h"
#include"../../Sound/CSound.h"
#include"../CScene.h"

//タイトルシーンのプログラミング
class CTitleScene :public CScene{
private:
	CSound SE_Enter;//エンターボタン鳴らす
	CTitle mTitle;//タイトル 
public:
	void Update();

	CTitleScene();
	~CTitleScene();
};
#endif
//ホームのプログラミング

#ifndef HOMESCENE_HPP
#define HOMEESCENE_HPP

#include "../Define/define.h"
#include "../../Scene/CScene.h"
#include "CHome.h"
#include"../../Sound/CSound.h"

class CHomeScene :public CScene{
private:
	CHome mHome;
	~CHomeScene();
	void Update();
public:
	CHomeScene();
};
#endif
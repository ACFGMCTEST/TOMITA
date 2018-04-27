//アイテムのプログラミング

#ifndef OptionSCENE_HPP
#define OptionSCENE_HPP

#include "../Define/define.h"
#include "../../Scene/CScene.h"
#include "COption.h"
#include"../../Sound/CSound.h"

class COptionScene :public CScene{
private:
	COption mOption;
	~COptionScene();
	void Update();
public:
	COptionScene();
};
#endif
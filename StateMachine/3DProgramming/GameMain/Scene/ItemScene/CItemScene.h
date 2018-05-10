//アイテムのプログラミング

#ifndef ItemSCENE_HPP
#define ItemESCENE_HPP

#include "../Define/define.h"
#include "../../Scene/CScene.h"
#include "CItem.h"
#include"../../Sound/CSound.h"

class CItemScene :public CScene{
private:
	CItem mItem;
	~CItemScene();
	void Update();
public:
	CItemScene();
};
#endif
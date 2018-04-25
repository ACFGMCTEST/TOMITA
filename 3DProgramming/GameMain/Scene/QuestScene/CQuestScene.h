//クエストのプログラミング

#ifndef QUEST_SCENE_HPP
#define QUEST_SCENE_HPP

#include "../Define/define.h"
#include "../../Scene/CScene.h"
#include "CQuest.h"

class CQuestScene :public CScene{
private:
	CQuest *mpQuest;

	~CQuestScene();

	void Update();
public:
	CQuestScene();
};
#endif
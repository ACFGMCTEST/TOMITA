#ifndef MAIN_HPP
#define MAIN_HPP

#include "CharaDate/CSceneModel.h"
#include "Map/CMap.h"
#include "../CScene.h"
#include "Pause/CPause.h"
#include "Tutorial\CTutorial.h"

class CGameScene : public CScene{
public:
 	static bool mPauseFlag;//true�ŃA�b�v�f�[�g��~,

	/*���*/
	enum E_STATE{
		E_INIT,
		E_MAIN,
		E_END
	};
	static E_STATE eState;


	CGameScene();
	~CGameScene();
	/*�X�V*/
	void Update();
	/*�~�j�}�b�v����ɕ\���������*/
	void MiniMapRender();
};

#endif
